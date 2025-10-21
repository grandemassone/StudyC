# C Programming Exercises

This repository collects a series of exercises and programs written in **C** language.
The exercises were developed mainly in **Xcode** as a working environment, with the aim of practicing system programming. 

The main focus is on **POSIX system calls**, such as:
- process management (`fork`, `exec`, `wait`, `kill`, signals)
- file management (`open`, `read`, `write`, `close`, `lseek`)
- directory management (`opendir`, `readdir`, `closedir`, `stat`)
- other syscalls related to the operation of operating systems

---

## Project structure
Each `.c` file represents an independent exercise or small program.  
There is no single main program: each source can be compiled and run individually.

---

## Requirements
- Compiler **GCC** or compatible  
- **Linux/Unix** environment (some exercises use POSIX system calls not available on Windows without WSL or Cygwin)
- **Xcode** as IDE used for development and testing

---

## Notes
These exercises are designed as a personal/academic practice, useful for better understanding low-level programming in C and the functioning of operating systems. 

If you find errors or want to suggest improvements, feel free to open an issue or pull request!
Author:
Salvador Davide Passarelli
