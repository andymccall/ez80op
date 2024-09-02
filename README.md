### ez80op

This program gives information on eZ80 opcodes.

#### Building

Perform the following commands to compile the project:

```

username@host:~$ cd agon-development/ez80op/c
username@host:~$ make
[compiling] src/main.c
[lto opt] obj/lto.bc
[linking] bin/ez80op.bin
```

#### Running the program

The newly built program can be run within the Fab Emulator using the following commands:

```
username@host:~$ make run
```

This will launch the Fab emulator.  Once the emulator has started check the binary is accessible to the emulator by using the dir command:

```
/ *dir
Volume: hostfs
Directory: /

ez80op.bin ez80op.map
```

Then run the binary using by loading it and issuing the run command:

```
/ * load ez80op.bin
/ * run
```
