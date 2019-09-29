# push_swap

The **push_swap** program is the second project of the *Algorithm* branch from the [42](https://www.42.fr) curriculum. 
The goal is to print an optimized set of instruction to order a stack. We can *theorically* use as much memory and perform as many operations as we want: but the final list of instruction needs to work under the conditions of the exercice. 

## Useful links
- The [Push_swap PDF subject](https://github.com/AugustinLopez/push_swap/blob/master/rcs/push_swap.pdf)
- An [example of quicksort on stacks (video)](https://www.youtube.com/watch?v=e_l77X9P1H4)

### Credit
I checked a lot of other implementation on GitHub. You may find similarities between their code and mine:
- [Solid implementation of the Quicksort recursion](https://github.com/rodionvolovik/push_swap)
- [Great Wiki on the implementation of the 2nd algorithm, pertinent use of function pointer](https://github.com/VBrazhnik/Push_swap)
- [Solid visualisation, another implementation of Quicksort](https://github.com/rizkyario/42-push_swap)

## Download & Launch

```
git clone https://github.com/AugustinLopez/push_swap.git
cd push_swap
make
```
### Usage:
- Executable: 
```
./push_swap [int ...]
./checker [-vcdsfih] [int ...]
```
- Scripts:
1. basic.sh is a simple combination of the 2 executables with visualisation activated. It receives the same int argument.
2. All benchmarkXXX.sh receives a number of test to perform for their specific range.
3. debug.sh and valgrind_XXX.sh are debug tools.
4. random.sh quickly launch a test with a random array of value. It receives a range and the same options as checker.
```
sh basic.sh [int ...]
sh benchmarkXXX.sh [unsigned int]
sh debug.sh
sh valgrind_XXX.sh
sh random.sh [unsigned int] [-vcdsfih]
```

## Checker options
- h: Help
- v: Visualize
- c: Color Visualize
- d: Data - show the number of operation and list of argument.
- s: Slow visualisation
- f: Fast visualisation
- i: Instant visualisation (ASAP)

## Algorithm

I use 3 algorithms in total: one quicksort and two insertion sorts. 
Once an algorithm has been calculated, the result is run through a function to combine and remove specific sets of operations.
The best series of instruction is then selected and printed to STDOUT. The best serie is the one with the least amount of instruction.

Quicksort performs better on bigger stacks. Insertion based sorts perform better on smaller and almost-sorted stacks.
If more than 500 valid parameters are given only quicksort is performed as performance starts to become an issue. If a memory error occurs after at least one algorithm has succeeded, the result will be printed.

### 1/ Quicksort
- Elements lower than the pivot are pushed or stay in stack B. 
- Elements higher than the pivot are pushed or stay in stack A.
- The pivot stays in its stack.
- Higher values are sorted first.
- Recursive method.
- The recursion returns if the size of the "working part of the" stack in less than 3. Those part are treated with another function.

### 2/ Insertion in Sorted Array - "Greater than" Method
- The biggest possible sorted stack is created in A by pushing specific element to the temporary stack. 
- LOOP: The best element from the temporary stack is inserted back in A, at the right place.
- When the temporary stack is empty, the stack A is rotated until its lowest element is pushed to the top.
- Iterative method.

### 3/Insertion in Sorted Array - "Index Increment" Method
- Compared to previous algorithm, the only difference is the way the biggest sorted stack in A is created.

## Relevant Data

###  Order of time
- 1000 parameters or less : less than a second
- 2000 parameters : a few seconds
- 5000 parameters : a dozen of seconds
- 10000 parameters : a few minutes

Performance would dramatically improve by reworking the pivot calculation. As of 10/04/2019 the quicksort's pivot is calculated at each step (by sorting a temporary array representing the state of the stack). All pivots could theorically be calculated right from the start.

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
