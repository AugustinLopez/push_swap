# push_swap
This is the push_swap project from 42.

The goal of the exercise is to optimize the list of instruction printed in STDOUT.

## Algorithm

Three algorithms are used in total. For each methods, specifics series of operations are combined or removed once the algorithm has run.
The best series of instruction is then selected and printed to STDOUT.

Quicksort tends to perform better on huge stacks. Insertion based sorts perform better on middle-sized or almost-sorted stacks.
If more than 500 valid parameters are given, only quicksort will be performed.

### 1/ Quicksort
- Elements lower than the pivot are pushed or stay in stack B. 
- Elements higher than the pivot are pushed or stay in stack A.
- Higher values are sorted first.
- Solution of size < 3 have been manually inputted (< 4 in stack A).
- Recursive method.

### 2/ Insertion in Sorted Array - "Greater than" Method
- One sorted stack is created in A by pushing specific element to B. 
- LOOP: The best element from B is inserted back in A, at the right place.
- When B is empty, the lowest value from A is pushed to the top.
- Iterative method.

### 3/Insertion in Sorted Array - "Index Increment" Method
- Compared to previous algorithm, the only difference is the way the sorted stack in A is created.

## Relevant Data

###  Order of time
- 1000 parameters or less : less than a second
- 2000 parameters : a few seconds
- 5000 parameters : a dozen of seconds
- 10000 parameters : a few minutes

Performance would dramatically improve by reworking the pivot calculation. As of 10/04/2019 the quicksort's pivot is calculated at each step (by sorting a temporary array representing the state of the stack). All pivots could be calculated at the start and kept in memory using a binary tree: only one temporary array would be needed during the process.

### 0/ Array of 5
Grading: Worst case < 12
- Average: 5
- Worst: 9

### 1/ Array of 100
Grading: **700** | 900 | 1100 | 1300 | 1500
- Sample size: 100 000
- Average: 555
- Worst: 639

### 2/ Array of 500
Grading: **5500** | 7000 | 8500 | 10000 | 11500
- Sample size: 10 000
- Average: 4996
- Worst: 5161

### 3/ Array of 2000
- Sample size : 100
- Average: 25959
- Worst: 26132

## Checker options
- v: Visualize
- c: Color Visualize
- d: Data - show the number of operation and list of argument.
- s: Slow visualisation
- f: Fast visualisation
- i: Instant visualisation (ASAP)
- h: Help

TBD:
Use those options to chose specific sorting algorithms.
- Q: Quicksort
- G: "Greater than" Method
- I: "Index increment" Method
