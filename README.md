# Project `pipex`

`pipex` is a program that aims to replicate the functionality of a shell pipeline, i.e., `cmd1 | cmd2`.

## Structure:

The project mainly consists of these files:
- `main.c`: Contains the main function and initializes the pipeline.
- `child.c`: Contains logic for each child process to execute commands.
- `error_print.c`: Contains the error function for printing out errors.
- `free.c`: Contains functions to free allocated memory.
- `helper_functions_1.c` and `helper_functions_2.c`: Contain helper functions to facilitate the main program.
- `pipex.h`: Header file which contains macro definitions and the function prototypes.

## Compilation:

The project comes with a Makefile that is responsible for compiling the code. The commands in the Makefile are as follows:

1. **Compiling**:
   ```
   make
   ```
   This will produce the executable named `pipex`.

2. **Clean**:
   ```
   make clean
   ```
   This command will remove the object files that were created during the compilation process.

3. **Full Clean**:
   ```
   make fclean
   ```
   This command will not only remove the object files but also the compiled `pipex` binary.

4. **Re-compiling**:
   ```
   make re
   ```
   This command is a shortcut for running `fclean` followed by `make`, essentially re-compiling the whole project.

## How It Works:

1. **Setting up the pipeline**:
   - Two pipes are created to facilitate communication between the two commands.
   - `child1` function corresponds to the first command's execution. It reads data from the input file and writes the processed data to the write-end of the first pipe.
   - `child2` function corresponds to the second command's execution. It reads the data from the read-end of the first pipe, processes it, and writes the final output to the output file.

2. **Executing commands**:
   - Each command is executed in its child process.
   - The program uses `execve` to replace the current process image with a new process image based on the command and its arguments.

3. **Error Handling**:
   - Errors such as invalid arguments, failed file operations, or failed command executions are handled and appropriate error messages are displayed.

4. **Memory Management**:
   - All allocated memory spaces are properly freed before the program's termination to avoid memory leaks.

## How To Use:

1. **Compiling the code**:
   ```
   make
   ```

2. **Running the program**:
   ```
   ./pipex infile "cmd1" "cmd2" outfile
   ```
   Where `infile` is the input file, `cmd1` and `cmd2` are the two commands you want to execute in a pipeline, and `outfile` is the output file.

For example, to simulate the shell command `cat infile | grep "some_text" > outfile`, you would run:

```
./pipex infile "cat" "grep 'some_text'" outfile
```

## Contribution:

Developed by `atoof` at Hive Helsinki.

## Note:

This is just a basic overview of the `pipex` project. For a deeper understanding, diving into the code and understanding each function in detail is recommended. You can view this project on my [GitHub repository](https://github.com/abbastoof/Pipex/)https://github.com/abbastoof/Pipex/).
