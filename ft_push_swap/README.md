*This project has been created as part of the 42 curriculum by hrandri2, tusandri.*

# ft_push_swap

## Description

`ft_push_swap` is a sorting program developed for the 42 curriculum. Its goal is to sort a stack of integers using a limited set of operations while minimizing the number of moves. The project demonstrates algorithm selection, stack manipulation, and optimization for small, medium, and large input sets.

The program reads integer arguments from the command line and produces a sequence of operations that transforms the initial stack into a sorted ascending stack.

## Contribution parts

## tusandri

- Implemented command-line flag handling for `--simple`, `--medium`, `--complex`, `--adaptive`, and `--bench`.
- Built the core push_swap command flow and stack setup logic for parsing input values (`sa`, `sb`, `pa`, `pb`, ...).
- Developed the simple sorting strategy using insertion-sort-like stack operations in `simple_sort.c`.
- Implemented the disorder measurement function `compute_disorder()` to evaluate initial stack disorder.
- Implemented the complex sorting strategy with LSD radix sort and rank assignment.

## hrandri2

- Developed bench mode reporting, including disorder percent, strategy, and total operation counts.
- Added error handling for invalid input, duplicate values, syntax errors, and memory leak prevention.
- Implemented the medium sorting strategy using bucket partitioning and controlled stack rotations.
- Added operation counting logic in `t_count` to track and report stack operation totals.
- Created the project build system in `Makefile` for `push_swap`, `libft`, and `ft_fprintf`.
- Wrote and structured the README documentation.

## tusandri and hrandri2

- Designed number parsing and stack initialization for command-line input values.
- Ensured code style and formatting compliance with Norminette requirements.
- Refactored functions to improve modularity, readability, and maintainability.
- Defined the shared header file `ft_push_swap.h` with data structures and prototypes.

## Instructions

### Compilation

1. Open a terminal in the project root directory.
2. Run `make`.

This builds the `push_swap` executable and the required helper libraries as in `libft` and `ft_fprintf`.

### Execution

Run the program with a list of integers:

```sh
./push_swap 3 2 1 5 4
```

The program prints the operations required to sort the stack.

### Cleaning

- `make clean`: remove object files and library archives
- `make fclean`: remove object files, library archives, and the `push_swap` executable
- `make re`: rebuild the entire project from scratch

## Algorithms

The project uses different sorting strategies depending on the input size:

- `simple_sort`: insertion sort
  - Chosen for small input sizes because it performs well on nearly sorted data and has low overhead.
  - It inserts elements into the correct position using the allowed stack operations.

- `medium_sort`: bucket sort
  - Selected for medium-sized inputs to reduce the number of comparisons and operations.
  - The stack is partitioned into chunks (buckets), and elements are moved between stacks in a controlled order to reduce total moves.

- `complex_sort`: LSD radix sort
  - Used for large inputs because it runs in O(n log n) time — linear in n per bit pass, with O(log n) passes total.
  - Nodes are first ranked by sorted order, then sorted least-significant bit first (LSD); values whose current bit is 0 are pushed to b, values whose bit is 1 stay in a via rotation, and b is flushed back to a after each pass.

These algorithm choices balance operational constraints with performance requirements for different input sizes.

| Strategy | Flag | Complexity | Typical input size |
|---|---|---|---|
| `simple_sort` (insertion) | `--simple` | O(n²) | ≤ ~20 elements |
| `medium_sort` (bucket) | `--medium` | O(n√n) | ~20 – 200 elements |
| `complex_sort` (LSD radix) | `--complex` | O(n log n) | 200+ elements |

## Detailed Algorithm Walkthroughs

### How `--simple` works (O(n²))

The `--simple` flag runs `push_swap()` in `simple_sort.c`.

**Key steps:**
1. Pushes all but 3 values from stack a to stack b with repeated `pb`.
2. Sorts the remaining 3 values in a with `tiny_sort()`.
3. Re-inserts values from b back into a one by one:
   - `find_cheapest_limited()` scans candidates in b
   - Computes the best insertion position in a with `find_insert_position()`
   - Rotates a and b to bring those nodes to top
   - Pushes with `pa`
4. Does a final rotation so the smallest element is on top.

**Why O(n²)?**
Each reinsertion from b scans parts of a and b to calculate cost. There are O(n) reinserts and each cost computation is O(n), so total is quadratic.

---

### How `--medium` works (O(n√n))

The `--medium` flag runs `medium_sort()` in `medium_sort.c`.

**Key steps:**
1. `assign_final_index()` converts every node to its rank in the sorted order.
2. `push_buckets()` moves values from a to b in bucket ranges of ranked indices:
   - Finds the next bucket target in a
   - Rotates a to that item
   - Pushes it to b
   - Optionally rotates b to keep smaller bucket values nearer the top
3. After only 3 remain in a, `tiny_sort()` sorts them.
4. Then it moves values back from b to a:
   - `move_back_fast()` computes the best b node to return
   - Uses combined rotations `rr` / `rrr` when possible
   - Pushes the cheapest item back to a

**Why O(n√n)?**
`get_bucket_size()` chooses bucket size based on len. Splitting into buckets reduces the number of expensive shifts. Overall work is less than quadratic and is intended to behave like O(n√n) for medium-sized input.

---

### How `--complex` works — LSD radix sort (O(n log n))

The `--complex` flag runs `radix_sort()` in `complex_sort.c`, implementing an LSD (Least Significant Digit) radix sort.

**Key steps:**
1. `assign_final_index()` ranks each node by sorted order.
2. Computes `max_bits` from the largest final index.
3. For each bit from least significant to most:
   - Scans all of a
   - Pushes values whose bit is 0 to b
   - Rotates values whose bit is 1 within a
   - Then pushes all b back to a
4. Special-case small sizes:
   - Len 2, 3, or 5 use direct small-sort helpers instead of radix loops

**Why O(n log n)?**
It is LSD radix sorting on the rank indices. There are O(log n) bit passes and each pass processes O(n) elements. So overall complexity is O(n · bits) = O(n log n).

### Resources

- Peer learning (discussions with fellow students)
- 42 school project instructions and push_swap subject PDF
- Stack operation sorting concepts
- Insertion sort, bucket sort, and radix sort references
- Algorithm complexity fundamentals:
  - [OpenClassrooms — Calculez la complexité algorithmique](https://openclassrooms.com/fr/courses/7527306-decouvrez-le-fonctionnement-des-algorithmes/7760669-calculez-la-complexite-algorithmique)
  - [Blaise Pascal NSI — Complexité d'un algorithme](https://info.blaisepascal.fr/nsi-complexite-dun-algorithme/)
- Push_swap implementation guides:
  - [ayogun — Push Swap](https://medium.com/@ayogun/push-swap-c1f5d2d41e97)
  - [Jamie Dawson — The least amount of moves with two stacks](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)
  - [julien-ctx — An easy and efficient algorithm to sort numbers](https://medium.com/@julien-ctx/push-swap-an-easy-and-efficient-algorithm-to-sort-numbers-4b7049c2639a)
  - [dansylvain84 — My implementation of the 42 push_swap project](https://medium.com/@dansylvain84/my-implementation-of-the-42-push-swap-project-2706fd8c2e9b)
  - [beatrizbazaglia — Push Swap](https://medium.com/@beatrizbazaglia/push-swap-3390f2b33428)
- Official 42 subject PDF:
  - [push_swap subject — 42 Intra](https://cdn.intra.42.fr/pdf/pdf/201834/en.subject.pdf)

### AI usage

AI assistance was used for the following tasks:
- Drafting and structuring this `README.md` file.
- Analyzing **algorithm complexity** (time and space complexity evaluation).
- Creating test suite
