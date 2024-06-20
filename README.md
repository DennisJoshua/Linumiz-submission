# Pushd and Popd with Shared Memory

This project implements `pushd` and `popd` commands in C to manage directory stacks using shared memory. The program allows users to push directories onto a stack and pop directories from the stack, preserving the state across different executions. This implementation does not rely on pre-built Linux applications or functions such as `ls`, `mkdir`, etc or `system()` and `popen()`.

## Requirements

To use this program, you will need:

- A Unix-like operating system (Linux)
- GCC (GNU Compiler Collection)


Check the [installation notes](#installation) for more details on how to install the project.

## Installation

1. Clone the repository or download the source code.

2. Compile the program using GCC:
    ```sh
    gcc -o pushpopd_shm pushpopd_shm.c
    ```

3. Run the program with appropriate arguments:
    ```sh
    ./pushpopd_shm pushd /path/to/directory
    ./pushpopd_shm popd
    ```

## Usage

- To push a directory onto the stack and change to that directory:
    ```sh
    ./pushpopd_shm pushd /path/to/directory
    ```
    This command changes the current directory to `/path/to/directory` and pushes it onto the stack.

- To pop the top directory from the stack and change to that directory:
    ```sh
    ./pushpopd_shm popd
    ```
    This command pops the top directory from the stack and changes to that directory.

For more details, check the [getting started guide](#useful-resources).

## Configuration

The program does not require any special configuration. It uses shared memory to maintain the directory stack, which allows the stack to persist between different executions of the program.

### Command-line Arguments

- `pushd <directory>`: Changes the current directory to `<directory>` and pushes it onto the stack.
- `popd`: Pops the top directory from the stack and changes to that directory.

### Useful `ipcs` Commands

- `ipcs -m`: Displays information about active shared memory segments.
- `ipcs -a`: Displays all information about active inter-process communication (IPC) facilities.
- `ipcs -t`: Displays the time information for the IPC facilities.

### Common Errors

- `shmget: Invalid argument`: Ensure the shared memory key and size are correctly specified.
- `shmat: Permission denied`: Check if the correct permissions are set for the shared memory segment.

### FAQ

- **Q:** What does `Stackoverflow!` mean?
  - **A:** It means that the stack is full and no more directories can be pushed onto it.

- **Q:** What does `Underflow!` mean?
  - **A:** It means that the stack is empty and there are no directories to pop from it.

## References

- [Shared Memory Documentation](https://man7.org/linux/man-pages/man7/sysvipc.7.html)(https://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html)
- [GCC Documentation](https://gcc.gnu.org/onlinedocs/)
- [POSIX API Documentation](https://pubs.opengroup.org/onlinepubs/9699919799/)

## Constraints

- It is a partial solution or an attempt to understand and implement the working of the pushd and popd functionalities. It has its own limitations such as 
- Size of the buffer, Maximum size is 4 and the byte length for each element is 1024. 
- To cross verify it run the `ipcs -a` command and get to know the total byte size the shared memory permits. In my case it shows 4100, So totally I have used 4096 from the shared memory
- Unlike pushd it can't push the current working directory when the stack is accessed for the first time other than that it    works well 




Contributions and feedback are always welcome.
