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

All of the following tests were conducted on the same machine with seed=1234.

### Test 1:
- n=2
- cutoff=0..17
#### Justification
n=2 is the minimum array size that the program accepts by default.
17 was the practical limit for a cutoff in this test as described in results.
#### Results
The timer on the program only prints to 1/100th of a second precision.
Therefore there was no measurable difference between runs where 0<=cutoff<=7,
as all results returned 0.00 seconds. At cutoff=8, the output was 0.01s, and for
every increment of cutoff after that the execution time approximately doubled, until
cutoff=17 where the execution time was consistently between 5.0 and 6.0 seconds.
At cutoff=18, the program would stall indefinitely, instead of giving the expected
output of ~10s. This led me to find the systems default cap on the number of threads
to be the culprit. The consistency of the doubling in time also revealed a missed
base case in the program that caused it to split off threads even if there was only
one element.

### Test 2:
- cutoff=0..17
- n=2^cutoff
#### Justification
n=2^cutoff means that there is an equal number of elements and threads, which could
reveal unexpected behaviour.
#### Results
Again, the timer only became visible at cutoff=8, and all values up to cutoff=17
executed with nearly identical results to their equivalent in Test 1. Trying to
execute with cutoff>17 reintroduced the system thread limit, as there was no
longer the case of there being more threads than elements, so no thread would be
skipped. Resolving this is beyond the scope of this project however, as it is a
system-bound limitation rather than a flaw in the program's logic.

### Test 3:
- cutoff=0..17
- n=(2^cutoff)*1000
#### Justification
n=(2^cutoff)*1000 lets us easily compare the performance of 1 element/thread
(as in Test 2) to 1000 elements/thread, to compare how increased element count
impacts performance compared to increased thread count.
#### Results
For each value of cutoff (from 8), the results of this test were largely comparable
to those of Test 2. No value of cutoff for n=(2^cutoff)*1000 exhibited an execution
time of greater than 2x that of n=2^cutoff. This suggests that the performance impact of adding an additional level of multi-threaded recursion should be
approximately equivalent to increasing the size of the array by some thousands.

### Test 4:
- cutoff=0..17
- n=100000000
#### Justification
Project specifications suggest testing against a high n, and 100000000 is a specific
example given.
#### Results
For cutoff=0..2, each increase in cutoff approximately halved the execution time from
the previous cutoff value. At cutoff=3, there was only ~25-30% decrease in execution
time, likely due to running on a 6-core processor and therefore saturating every
core (with 8 threads at cutoff=3). At cutoff=4 there was ~20% decrease, and for
cutoff=5 there was only ~10% decrease. At cutoff=6..9 there was roughly equivalent
performance compared to cutoff=5, and for cutoff=10..17 there was a slow but
accelerating increase in execution time, although cutoff=17 never exceeded
single-threaded execution time.

### Additional Tests
In addition to the previous tests, Tests 1, 2, and 4 were all conducted again, except
with n=n+1 (i.e. executing with odd numbers). No bugs were detected, and each test
showed no measurable difference in performance compared to their original execution.

## Known Bugs

- Excessive level cutoff causes indefinite execution duration.
    This is a system limitation on the number of threads that can be
        created rather than an implementation bug.
        The max cutoff on a linux device is log2(n),
        where n = cat /proc/sys/kernel/threads-max

## Reflection and Self Assessment

A difficulty for me was the syntax of C for threading, struct passing, etc,
    which I have not encountered before, requiring some trial and error and
    documentation research.

As the test file does not produce much output, and produces no output during
    the main execution, it was a bit of extra work to add debug output for testing,
    however this wasn't particularly difficult.

Overall this project wasn't too challenging in terms of programming as the actual
    breadth of the codebase was quite small, so it was viable to simply proofread
    over and over to identify bugs.

## Sources Used

Fix compiler error regarding for loop declaration:
    https://stackoverflow.com/questions/29338206/error-for-loop-initial-declarations-are-only-allowed-in-c99-mode

General implementation details/pseudocode:
    https://en.wikipedia.org/wiki/Merge_sort

Project specification and some function use (i.e. buildArgs, memcpy):
    https://learn.adelaide.edu.au/courses/30365/assignments/86221

Identifying cutoff limit bug:
    https://stackoverflow.com/questions/344203/maximum-number-of-threads-per-process-in-linux