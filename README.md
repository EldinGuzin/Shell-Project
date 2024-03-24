# TERMINUS

*a Shell Project written in c*

## Group Members
- [Alejna Hasanagic](https://github.com/alejnaH)
- [Eldin Guzin](https://github.com/EldinGuzin)

## Submission Contents
- `terminus.c`: The shell




## Assignment Outline
- Our aim is to make an interactive, fun and easy to use shell application

## Compilation Instructions
- Our shell is easy to compile and run :)
just compile it by using `cpp -o terminus terminus.c` then run it with `./terminus`

## Challenges Encountered
Most difficult part at this moment is piping

## Sources and Tutorials
- These 2 were the main sources used :
- [Source 1](https://medium.com/@winfrednginakilonzo/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd)
- [Source 2](https://www.geeksforgeeks.org/making-linux-shell-c/)

## Known Issues
it crashes when you enter `as`, I know it makes no sense but it is how it is

## Code Comments
Currently our shell is not well documented but we aim for it to be in the future



## Assignment Questions

### Question 1: What does the mmap() function do?

- The mmap() function in Unix-like systems maps files or devices into memory, allowing direct access to their contents as if they were part of the process's memory. It's used for efficient file I/O operations and for creating shared memory regions between processes.
- It essentially creates a mapping between a file or device and the virtual memory of a process. This mapping allows the process to treat the mapped region as if it were regular memory, enabling efficient reading from and writing to files or devices.

- With mmap(), you can map files into memory, which is particularly useful for large files where loading the entire content into memory might not be practical. It provides a way to access portions of a file directly from memory, facilitating random access operations without the need for explicit I/O operations like read() and write().

- One of the significant advantages of using mmap() is its ability to leverage the operating system's memory management mechanisms, such as paging and caching, to optimize memory usage and I/O performance. Additionally, memory mapped files can be shared between processes, providing a mechanism for efficient data sharing and communication.

### Question 2: What happens during a context switch? Do we want the OS to perform many or few context switches? Explain.

During a context switch, the operating system switches the CPU from executing one process to another. Here's what happens:

  - Saving State: The OS saves the current state of the CPU, including things like the values of registers and the program counter, for the process that's currently running.

  - Loading State: Then, it loads the saved state of another process that needs to run next. This includes restoring the register values and program counter to where the new process left off.

  - Switching Memory Context: If necessary, the OS may also update the memory mappings so that the new process can access its required memory areas.

  - Resuming Execution: Once the new process's state is loaded, the CPU starts executing instructions from where that process was interrupted.

As for whether we want many or few context switches, ideally, we want to minimize them. Here's why:
  - Overhead: Context switches take time and resources to perform, which can slow down the system.

  - Cache Effects: Switching between processes can cause the CPU cache to be less effective, leading to slower performance due to more cache misses.
  
  - Scheduling Latency: Too many context switches can introduce delays in scheduling processes, which can make the system less responsive.
  
  - Resource Contentions: Excessive context switching can lead to inefficiencies in how system resources are used, potentially slowing down overall performance.

However, some context switches are necessary for multitasking. So, while we want to minimize them to improve performance, we can't eliminate them entirely. It's about finding a balance between having enough context switches to allow multitasking and keeping them low enough to avoid performance problems.

### Question 3: What is the output of the following code snippet? You are given that the exec system call in the child does not succeed

``` 
int ret = fork();
if(ret==0){
  exec(some_binary_that_does_not_exec);
  printf("child\n");
}
  else{
  wait();
  printf("parent\n");
}

```

- The output will be **parent**

` ret==0` is a child process, and the parent process waits for the child process to finish with the `wait()` command.
The exec() system call is invoked to replace the current process image with a new one. However, it is stated that the exec() call does not succeed. This means the child process fails to execute the specified binary and does not continue beyond this point.After the child process terminates (or if the child process does not terminate due to the failed exec()), the parent process proceeds to execute.
Therefore, the printf("parent\n") statement will be executed.


