# Holberton School Simple Shell

## Overview

This project implements a simple UNIX command line interpreter (shell) as part of the Holberton School curriculum. The shell mimics basic functionality of `/bin/sh` with specific constraints and requirements.

## Features

- Displays a prompt (`($) `) and waits for user input
- Executes simple commands (one word, no arguments initially)
- Handles "end of file" condition (Ctrl+D)
- Prints error messages for non-existent executables
- Works in both interactive and non-interactive modes
- Passes Betty style checks
- No memory leaks
- Limited to allowed functions and system calls

## Compilation

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
$
```

### Non-Interactive Mode

```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
```

## Requirements

- Ubuntu 20.04 LTS
- GCC with specified flags
- Betty style compliance
- No more than 5 functions per file
- Include guards on header files
- Exact output matching `/bin/sh`

## Files

- `main.c`: Entry point
- `shell.c`: Core shell logic
- `README.md`: This file
- `man_1_simple_shell`: Manual page
- `AUTHORS`: Contributors

## Authors

See AUTHORS file.

## License

This project is part of Holberton School curriculum.
