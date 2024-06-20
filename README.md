# CPU-Scheduler_ACM
An implementation of various CPU scheduling algorithms in C++. The algorithms included are First Come First Serve (FCFS), Round Robin (RR), Shortest Job Next (SJN) and priority

## Table of Contents
Files Included
1. main.cpp: Contains the main program logic where processes are input by the user and scheduling algorithms are invoked.

2.README.md: This document, providing an overview of the program and instructions.

3.ProcessScheduling.cpp:
  . Defines the Process class representing individual processes with attributes like arrival time, burst time, priority, etc.
  . Defines the Scheduler class which handles scheduling algorithms and computes statistics.
  . Contains comparator classes (ArrivalTimeComparator and PriorityComparator) used for sorting processes.

4.ProcessScheduling.h: Header file declaring classes and methods used in ProcessScheduling.cpp.

5.Makefile: Optional, for compiling the program using make.

## Algorithms

### First Come First Serve (FCFS)
- First Come First Served (FCFS) is a scheduling algorithm in which the process that arrives first is executed first. It is a simple and easy-to-understand algorithm, but it can lead to poor performance if there are processes with long burst times. This algorithm does not have any mechanism for prioritizing processes, so it is considered a non-preemptive algorithm. In FCFS scheduling, the process that arrives first is executed first, regardless of its burst time or priority. This can lead to poor performance, as longer running processes will block shorter ones from being executed. It is commonly used in batch systems where the order of the processes is important.

### Round Robin with varying time quantum (RR)
- Round Robin (RR) with variable quantum is a scheduling algorithm that uses a time-sharing approach to divide CPU time among processes. In this version of RR, the quantum (time slice) is not fixed and can be adjusted depending on the requirements of the processes. This allows processes with shorter burst times to be given smaller quanta and vice versa.

- The algorithm works by maintaining a queue of processes, where each process is given a quantum of time to execute on the CPU. When a process's quantum expires, it is moved to the back of the queue, and the next process in the queue is given a quantum of time to execute.

- The variable quantum allows the algorithm to be more efficient as it allows the CPU to spend more time on shorter processes and less time on longer ones. This can help to minimize the average waiting time for processes. Additionally, it also helps to avoid the issue of starvation, which occurs when a process with a long burst time prevents other processes from executing.

### Shortest Remaining Time (SRT)
- Shortest Process Next (SPN) is a scheduling algorithm that prioritizes the execution of processes based on their burst time, or the amount of time they need to complete their task. It is a preemptive algorithm. This means that once a process starts executing, it can be interrupted by a new process with a shorter remaining time.

- The algorithm maintains a queue of processes, where each process is given a burst time when it arrives. The process with the shortest remaining time is executed first, and as new processes arrive, they are added to the queue and sorted based on their remaining time. The process with the shortest remaining time will always be at the front of the queue, and thus will always be executed next.

- This algorithm can be beneficial in situations where the objective is to minimize the average waiting time for processes, since shorter processes will be executed first, and thus will spend less time waiting in the queue. Additionally, it can be useful in situations where the burst time of processes is not known in advance, since the algorithm can adapt to changes in the remaining time as the process is executing.

- In summary, SRT is a scheduling algorithm that prioritizes the execution of processes based on their remaining time, it's a preemptive algorithm, which means that it can interrupt a process that's already executing if a new process with a shorter remaining time arrives and it's commonly used in situations where the objective is to minimize the average waiting time for processes and burst time is not known in advance.

## Installation
1- Clone the repository

2- Install g++ compiler and make
```bash
sudo apt-get install g++ make
```
3- Compile the code using `make` command

4- Run the executable file

##Usage Instructions
  
  . Input Format:

Enter the number of processes.
For each process, input the ID, arrival time, burst time, and priority.
  
  . Scheduling Algorithms:

Priority Scheduling: Prioritizes processes based on priority value.
Round Robin Scheduling: Allocates a fixed time quantum to each process.
FCFS Scheduling: Executes processes based on their arrival times, in the order they appear.
SJF Scheduling: Executes the shortest job first, considering burst times.
  
  . Statistics:

After scheduling each algorithm, average turnaround time and average waiting time are displayed.

- **Note:** 
The program assumes integer inputs for simplicity and handles a single CPU environment.
Error handling for invalid inputs (negative values, non-integer inputs) is not implemented in this version.
Each scheduling function sorts processes by arrival time before applying the respective algorithm.

##input demo
![input](https://github.com/Piyushgoyal-09/CPU-Scheduler_ACM/assets/173268130/706ca02e-8a11-4cf4-b502-f313d6524a00)

##output
![output](https://github.com/Piyushgoyal-09/CPU-Scheduler_ACM/assets/173268130/4b738f48-c82d-43e7-8e2b-042d871d2dfb)


