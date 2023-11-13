# pipex
This project aims to deepen your understanding of UNIX mechanisms (Redirections and Pipes).

### What is a Process?

First, a program is a file containing a range of information describing how to construct a process at run time.

A process is an instance of an executing program. When a program
is executed, the kernel loads the code of the program into virtual memory, allocates space for program variables, and sets up kernel bookkeeping data structures
to record various information (such as process ID, termination status, user IDs, and
group IDs) about the process.

if 16 users are running *vi* at once, there are 16 separate processes (although they can share
the same executable code). Processes are often called *tasks* or *threads* in the Linux
source code.

When a process is created, it is almost identical to its parent. It receives a (logical)
copy of the parent’s address space and executes the same code as the parent, beginning at the next instruction following the process creation system call. Although the
parent and child may share the pages containing the program code (text), they have

separate copies of the data (stack and heap), so that changes by the child to a memory location are invisible to the parent (and vice versa).

### The init process

When booting the system, the kernel creates a special process called init, the “parent
of all processes,” which is derived from the program file /sbin/init. All processes
on the system are created (using fork()) either by init or by one of its descendants.
The init process always has the process ID 1 and runs with superuser privileges. The
init process can’t be killed (not even by the superuser), and it terminates only when
the system is shut down. The main task of init is to create and monitor a range of
processes required by a running system. (For details, see the init(8) manual page.)

### **Monitoring processes in the system**

At any given time there may be a couple hundred or fewer processes running. Sometimes it is useful to see detailed information about them, especially if your computer is running slow: as certain processes may be hogging the computer’s memory or the CPU. Being able to pinpoint and subsequently destroy them is very handy indeed and can be achieved fairly easily.

```
ps aux // This will display a list of processes
top // detailed information about all processes, threads, memory hoggers, and network packets
```

### **How does the operating system manage processes**

![](https://miro.medium.com/max/1304/1*LdafsmbCdfR882Vtd1Kp0g.jpeg)

A process can be in a particular state at any given time. It may have just been created, waiting to run, waiting for access to some I/O device, interrupted by some other process, etc. To ensure maximal productivity, the operating system needs to understand the state of all of these processes and be able to intelligently create new ones, switch between them, pause them, suspend them, etc. at the right times.

To do this effectively, the operating system maintains what’s known as a Process Control Block for each process. It contains useful information such as the current process state, the next instruction to perform, and currently allocated devices to the process.

This enables the operating system to manage different processes effectively, by saving the current state in the PCB, switching between them, and reloading certain processes later on.

A process control block:

![](https://miro.medium.com/max/350/1*kAg0WimV_ZBEPqR97hj2WA.jpeg)

## Usage:
### Mandatory part:
The program `pipex` should have the same behavior as shell commands.
```bash
$> < file1 cmd1 | cmd2 > file2
```
and looks like this:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```
### Bonus part:
The program need handle multiple pipes

```bash
$> < file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2

$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
```
Support `<<` and `>>`, when instead of `file1` is`here_doc`.
```bash
$> cmd1 << LIMITER | cmd2 >> file2

$> ./pipex here_doc LIMITER cmd1 cmd2 file2
```
