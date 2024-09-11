# Makefile for C Project with Profiling

# Project Configuration
BIN_NAME = ez80op
X86_PROJECT_NAME = ez80op_linux_x86_64
ARMHF_PROJECT_NAME = ez80op_linux_armhf
ARM64_PROJECT_NAME = ez80op_linux_aarch64
Z80_PROJECT_NAME = ez80op_agon_z80
GIT_INFO := "$(shell git describe --always --tags)"

# Architecture-Specific Compilers and Flags
X86_CC = gcc
ARM64_CC = aarch64-linux-gnu-gcc
ARMHF_CC = arm-linux-gnueabi-gcc
Z80_CC = ez80-clang
Z80_CL = ez80-link
Z80_ASM = fasmg
AGDEV_BASE = $(shell echo $$AGDEV_BASE)
COMMON_FLAGS = -DGIT_INFO=\"$(GIT_INFO)\"
X86_CFLAGS = -Wall -g $(COMMON_FLAGS)
ARM64_CFLAGS = -static $(COMMON_FLAGS)
ARMHF_CFLAGS = -static $(COMMON_FLAGS)
Z80_CFLAGS = -Werror -Wall -Wextra -Oz -DCEDEV $(COMMON_FLAGS)
                           
EZLLVMFLAGS = -mllvm -profile-guided-section-prefix=false
EZCOMMONFLAGS = -emit-llvm -nostdinc -isystem $(AGDEV_BASE)/include -I$(SRC_DIR) -fno-threadsafe-statics -Xclang -fforce-mangle-main-argc-argv $(EZLLVMFLAGS) -DNDEBUG  -g0 $(Z80_CFLAGS)
EZCFLAGS = $(EZCOMMONFLAGS)
EZCXXFLAGS = $(EZCOMMONFLAGS) -isystem $(AGDEV_BASE)/include/c++ -fno-exceptions -fno-use-cxa-atexit $(CXXFLAGS)
EZAGONFLAGS = $(EZCOMMONFLAGS) -isystem $(AGDEV_BASE)/include/agon -fno-exceptions -fno-use-cxa-atexit $(AGONFLAGS)
EZLTOFLAGS = $(EZLLVMFLAGS) $(LTOFLAGS)

BSSHEAP_LOW ?= 080000
BSSHEAP_HIGH ?= 09FFFF
STACK_HIGH ?= 0AFFFF
INIT_LOC ?= 040000

# Directories
SRC_DIR = src
OBJ_DIR = obj
OBJ_X86_DIR = x86
OBJ_ARM64_DIR = arm64
OBJ_ARMHF_DIR = armhf
OBJ_Z80_DIR = z80
BIN_DIR = bin
TEST_DIR = tests
RELEASE_DIR = release

# Source and Object Files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
X86_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(OBJ_X86_DIR)/%.o, $(SOURCES))
ARM64_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(OBJ_ARM64_DIR)/%.o, $(SOURCES))
ARMHF_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(OBJ_ARMHF_DIR)/%.o, $(SOURCES))
Z80_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(OBJ_Z80_DIR)/%.o, $(SOURCES))

# Test Files and Object Files (if using Unity, adjust accordingly)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SOURCES))

# Include Directories
INCLUDES = -Iinclude # Adjust if you have additional include directories

# Unity Library (if using Unity for testing)
UNITY_DIR = path/to/unity # Update with the actual path
UNITY_LIB = $(UNITY_DIR)/unity.c

# Targets

all: x86 arm64 armhf z80

x86: CFLAGS += $(X86_CFLAGS) 
x86: CC = $(X86_CC)
x86: $(X86_PROJECT_NAME)

$(X86_PROJECT_NAME): $(BIN_DIR) $(OBJ_DIR)/$(OBJ_X86_DIR) $(X86_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(X86_OBJECTS) -o $(BIN_DIR)/$@ $(LDFLAGS)

# Architecture-Specific Targets

arm64: CFLAGS += $(ARM64_CFLAGS)
arm64: CC = $(ARM64_CC)
arm64: $(ARM64_PROJECT_NAME)

$(ARM64_PROJECT_NAME): $(BIN_DIR) $(OBJ_DIR)/$(OBJ_ARM64_DIR) $(ARM64_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(ARM64_OBJECTS) -o $(BIN_DIR)/$@ $(LDFLAGS)

armhf: CFLAGS += $(ARMHF_CFLAGS)
armhf: CC = $(ARMHF_CC)
armhf: $(ARMHF_PROJECT_NAME)

$(ARMHF_PROJECT_NAME): $(BIN_DIR) $(OBJ_DIR)/$(OBJ_ARMHF_DIR) $(ARMHF_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(ARMHF_OBJECTS) -o $(BIN_DIR)/$@ $(LDFLAGS)

z80: CFLAGS += $(EZCFLAGS)
z80: CC = $(Z80_CC)
z80: CL = $(Z80_CL)
z80: $(Z80_PROJECT_NAME)

$(Z80_PROJECT_NAME): $(BIN_DIR) $(OBJ_DIR)/$(OBJ_Z80_DIR) $(Z80_OBJECTS)
	$(CL) $(Z80_OBJECTS) -o $(OBJ_DIR)/$(OBJ_Z80_DIR)/lto.bc $(LDFLAGS)
	$(CC) -S $(EZLLVMFLAGS) $(Z80_CFLAGS) $(OBJ_DIR)/$(OBJ_Z80_DIR)/lto.bc -o $(OBJ_DIR)/$(OBJ_Z80_DIR)/lto.src
	$(Z80_ASM) -n '$(AGDEV_BASE)/meta/ld.alm' -i 'DEBUG := 0' -i 'PROG_NAME := '\''$(Z80_PROJECT_NAME)'\''' -i 'HAS_LIBC := 1' -i 'HAS_LIBCXX := 1' -i 'HAS_AGON := 1' -i 'PREFER_OS_CRT := 0' -i 'PREFER_OS_LIBC := 0' -i 'HAS_EXIT_HANDLER := 1' -i 'HAS_ARG_PROCESSING := 0' -i 'include "$(AGDEV_BASE)/meta/linker_script"' -i 'range .bss $$080000 : $$09FFFF' -i 'provide __stack = $$0AFFFF' -i 'locate .header at $$040000' -i 'source "$(AGDEV_BASE)/lib/crt/crt0.src", "obj/z80/lto.src"' -i 'library "$(AGDEV_BASE)/lib/libload/fatdrvce.lib", "$(AGDEV_BASE)/lib/libload/fileioc.lib", "$(AGDEV_BASE)/lib/libload/fontlibc.lib", "$(AGDEV_BASE)/lib/libload/graphx.lib", "$(AGDEV_BASE)/lib/libload/keypadc.lib", "$(AGDEV_BASE)/lib/libload/msddrvce.lib", "$(AGDEV_BASE)/lib/libload/srldrvce.lib", "$(AGDEV_BASE)/lib/libload/usbdrvce.lib"'  $(BIN_DIR)/$(Z80_PROJECT_NAME).bin
	
# Testing Target (adjust if using a different testing framework)

test: $(TEST_OBJECTS) $(OBJECTS) $(UNITY_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Release Target (optimize for performance)

release_x86: CFLAGS += -O2 -DNDEBUG
release_x86: $(RELEASE_DIR) x86

release_arm64: CFLAGS += -O2 -DNDEBUG
release_arm64: $(RELEASE_DIR) arm64

release_armhf: CFLAGS += -O2 -DNDEBUG
release_armhf: $(RELEASE_DIR) armhf

release_z80: CFLAGS += -O2 -DNDEBUG
release_z80: $(RELEASE_DIR) z80

# Profiling Target (compile with profiling flags)

profile: CFLAGS += -pg
profile: $(X86_PROJECT_NAME)
	./$(X86_PROJECT_NAME) # Run the executable to generate profiling data
	gprof $(X86_PROJECT_NAME) gmon.out > analysis.txt # Analyze the profiling data

# Packaging Target (customize as needed)

package: package_x86 package_arm64 package_armhf package_z80

package_x86: release_x86
	tar -zcvf $(RELEASE_DIR)/$(X86_PROJECT_NAME).tar.gz --transform 's/bin\/$(X86_PROJECT_NAME)/$(BIN_NAME)/' $(BIN_DIR)/$(X86_PROJECT_NAME)

package_arm64: release_arm64
	tar -zcvf $(RELEASE_DIR)/$(ARM64_PROJECT_NAME).tar.gz --transform 's/bin\/$(ARM64_PROJECT_NAME)/$(BIN_NAME)/' $(BIN_DIR)/$(ARM64_PROJECT_NAME)

package_armhf: release_armhf
	tar -zcvf $(RELEASE_DIR)/$(ARMHF_PROJECT_NAME).tar.gz --transform 's/bin\/$(ARMHF_PROJECT_NAME)/$(BIN_NAME)/' $(BIN_DIR)/$(ARMHF_PROJECT_NAME)

package_z80: release_z80
	tar -zcvf $(RELEASE_DIR)/$(Z80_PROJECT_NAME).tar.gz --transform 's/bin\/$(Z80_PROJECT_NAME)/$(BIN_NAME)/' $(BIN_DIR)/$(Z80_PROJECT_NAME).bin

# Cleanup Target

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_DIR) $(RELEASE_DIR) $(X86_PROJECT_NAME) $(ARM64_PROJECT_NAME) $(ARMHF_PROJECT_NAME) $(Z80_PROJECT_NAME) $(TEST_EXECUTABLE) analysis.txt gmon.out

# Create directories

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/$(OBJ_X86_DIR):
	mkdir -p $@

$(OBJ_DIR)/$(OBJ_ARM64_DIR):
	mkdir -p $@

$(OBJ_DIR)/$(OBJ_ARMHF_DIR):
	mkdir -p $@

$(OBJ_DIR)/$(OBJ_Z80_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(TEST_DIR):
	mkdir -p $@

$(RELEASE_DIR):
	mkdir -p $@

# Object File Compilation Rules

$(OBJ_DIR)/$(OBJ_X86_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/$(OBJ_ARM64_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/$(OBJ_ARMHF_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/$(OBJ_Z80_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -MD $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@