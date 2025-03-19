# Philosophers - Philosophers' Problem

The **philosophers** project is an implementation of the classic dining philosophers problem, which addresses synchronization and concurrency in computer systems. This problem is a good example to learn about thread usage and shared resource management.

## Objective

The goal is to simulate a group of philosophers sitting at a table, where each alternates between thinking and eating. To eat, a philosopher needs two forks (one on their left and one on their right). The challenge is to avoid race conditions and ensure that all philosophers can eat without falling into a state of starvation.

## Requirements

- Knowledge of **C** programming.
- Familiarity with thread programming (pthreads).

## Compilation

To compile the project, run the following command in the root directory:

```bash
make
```

## Execution

```bash
./philo <number of philosophers> <time to die> <time to eat> <time to think> [number of meals]
```
