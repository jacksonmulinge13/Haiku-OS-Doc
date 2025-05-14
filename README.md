# Haiku-OS-Documentation
## 1. OS Installation (Haiku in VMware)
This section provides a brief overview of setting up the Haiku operating system using VMware.  
It highlights the use of a virtual machine environment for testing and development.  
The goal is to create a stable platform to explore Haiku’s features.  
VMware offers flexibility and ease of use for running Haiku without affecting the host system.

## 2. System Call: fork (Simulated)
This section explains how process creation is handled in Haiku.  
Since Haiku does not support the traditional fork() system call, alternatives are discussed.  
The focus is on using posix_spawn() to simulate fork() behavior.  
It helps developers understand how to write portable code for Haiku.
