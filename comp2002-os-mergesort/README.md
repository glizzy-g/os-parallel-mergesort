README.template

## Assignment 2: Programming Task

* Authors: Elliot Shine, Tyler Milhench, Christian Galloni
* Group name: Group 28

## Overview

The program takes an input of an array size, thread count, and rng seed
from cmd line args. It then generates an array of the given size of random
numbers, and executes a parallel mergesort algorithm on them. It prints out
the time to execute the sort.

## Manifest

README.md: Project information.
mergesort.h: Declares mergesort method signatures.
mergesort.c: Implements mergesort functions.
test-mergesort.c: Hosts main to generate the random array and execute the mergesort.
Makefile: Defines build instructions for make.

## Building the project

To clone:
```
git clone https://github.com/glizzy-g/os-parallel-mergesort
```
To build:
```
cd os-parallel-mergesort
cd comp2002-os-mergesort
make
```

## Features and usage

To execute:
```
./test-mergesort <input size> <cutoff level> <seed>
```

## Testing

This section should detail how you tested your code. Simply stating "I ran
it a few times and it seems to work" is not sufficient. Your testing needs
to be detailed here.

## Known Bugs

List known bugs that you weren't able to fix (or ran out of time to fix).

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

Fix compiler error regarding for loop declaration:
    https://stackoverflow.com/questions/29338206/error-for-loop-initial-declarations-are-only-allowed-in-c99-mode

General implementation details/pseudocode:
    https://en.wikipedia.org/wiki/Merge_sort
    
Project specification and some function use (i.e. buildArgs, memcpy):
    https://learn.adelaide.edu.au/courses/30365/assignments/86221