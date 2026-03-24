*This project has been created as part of the 42 curriculum by hrandri2.*

# ft_printf

## Description
This project is a reimplementation of a subset of the C standard library function `printf`. The goal is to handle formatted output without using the libc implementation, focusing on core format specifiers and output behavior. It builds a custom, minimal formatting engine that parses a format string and prints values accordingly.

Supported specifiers in this implementation include:
- `%c` character
- `%s` string
- `%p` pointer (hexadecimal, `0x` prefix)
- `%d` / `%i` signed decimal
- `%u` unsigned decimal
- `%x` lowercase hexadecimal
- `%X` uppercase hexadecimal
- `%f` floating-point number (with precision control)
- `%%` percent sign

## Instructions
### Compilation
Build the library with:
- `make`

This produces `libftprintf.a`.

### Usage
Include the header and link the library in your project:
- Include [ft_printf.h](ft_printf.h)
- Link with `-L. -lftprintf`

Example compile command:
- `cc -Wall -Wextra -Werror main.c -L. -lftprintf`

## Algorithm and Data Structure Explanation
The implementation is centered around a linear scan of the format string. For each character:
1. If it is not `%`, it is printed directly.
2. If it is `%`, the next character determines the specifier and dispatches to the proper handler.

This is effectively a single-pass parser with constant-time dispatch per specifier. The data structure choice is minimal by design: the format string is treated as a sequence of characters and read using an index. This keeps memory usage constant, avoids dynamic allocation, and matches the behavior of the original `printf` for the supported specifiers.

Justification:
- **Time complexity:** $O(n)$ in the length of the format string, plus the cost of printing each argument’s digits/characters. Each specifier is processed in constant time.
- **Space complexity:** $O(1)$ auxiliary memory, since output is written directly and numbers are printed using recursive or iterative digit emission.- **Float precision:** The `%f` implementation supports precision control (e.g., `%.2f`) by parsing the format string and limiting decimal places accordingly.- **Simplicity and correctness:** A direct scan and dispatch mirrors `printf`’s contract and is easy to verify for the required subset.

## Resources
Classic references:
- https://velog.io/@ljiwoo59/ftprintf
- https://42-cursus.gitbook.io/guide/1-rank-01/ft_printf#format-specifiers
- https://www.youtube.com/watch?v=oz5xT5Pej8A
-  Peer learning (discussions with fellow students)

## AI usage:
- Improved this README’s structure and wording.
- Clarified differences between `%x` and `%X`, and `%d` and `%i`.
- Helped answer questions about test cases for some functions.
