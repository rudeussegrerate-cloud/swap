*This project has been created as part of the 42 curriculum by hrandri2*

# libft - My First C Library

## Description

**libft** is a comprehensive custom C library created as part of the 42 school curriculum that re-implements essential POSIX standard library functions, along with additional utility functions useful for subsequent 42 projects. This project serves as the foundational library for all future programming assignments within the curriculum.

### Purpose & Goals

The primary goal of **libft** is to gain deep mastery of low-level C programming concepts through practical implementation:
- **Memory Management**: Understanding dynamic allocation, deallocation, and memory safety through `malloc`, `free`, and related functions
- **String Manipulation**: Implementing various string operations while respecting size boundaries and handling edge cases
- **Data Structures**: Building and manipulating linked lists with custom function pointers
- **System-Level Programming**: Working directly with memory, file descriptors, and low-level data representations
- **Code Quality**: Writing efficient, well-tested code that compiles without warnings using strict compilation flags

### Architecture

**libft** is built as a **static library archive** (`libft.a`) compiled from individual function source files:
- **Single unified archive**: All functions compiled into one linkable library file for easy distribution and linking
- **Modular design**: Each function implemented in its own `.c` source file following the naming convention `ft_<function_name>.c`
- **Strict compilation**: All code compiled with `-Wall -Wextra -Werror` flags to catch potential bugs early
- **Public interface**: Single header file [libft.h](libft.h) declaring all 43 implemented functions
- **No external dependencies**: Pure C implementation using only standard library headers (`stdlib.h`, `unistd.h`, `stddef.h`)

### Foundation for Future Projects

This library serves as the essential foundation for all subsequent 42 curriculum projects, providing:
- Reliable, tested implementations of commonly used utility functions
- Custom implementations that deepen understanding of standard library behavior
- Building blocks for more complex projects (printf, get_next_line, parsing, and game development)

## Library Overview

### Functions Included

The library is organized into several categories:

#### Character Classification & Conversion
| Function     | Description                         |
|--------------|-------------------------------------|
| `ft_isalpha` | Checks if character is alphabetic   |
| `ft_isdigit` | Checks if character is a digit      |
| `ft_isalnum` | Checks if character is alphanumeric |
| `ft_isascii` | Checks if character is ASCII        |
| `ft_isprint` | Checks if character is printable    |
| `ft_toupper` | Converts character to uppercase     |
| `ft_tolower` | Converts character to lowercase     |

#### String Functions
| Function      | Description                                            |
|---------------|--------------------------------------------------------|
| `ft_strlen`   | Calculates string length                               |
| `ft_strchr`   | Locates first occurrence of character in string        |
| `ft_strrchr`  | Locates last occurrence of character in string         |
| `ft_strncmp`  | Compares two strings up to n characters                |
| `ft_strnstr`  | Locates substring in string (size-bounded)             |
| `ft_strlcpy`  | Size-bounded string copy                               |
| `ft_strlcat`  | Size-bounded string concatenation                      |
| `ft_strdup`   | Duplicates a string                                    |
| `ft_substr`   | Extracts substring from string                         |
| `ft_strjoin`  | Concatenates two strings into new allocation           |
| `ft_strtrim`  | Trims characters from both ends of string              |
| `ft_split`    | Splits string by delimiter into array                  |
| `ft_strmapi`  | Applies function to each character (returns new string)|
| `ft_striteri` | Applies function to each character (in place)          |

#### Memory Functions
| Function     | Description                          |
|--------------|--------------------------------------|
| `ft_memset`  | Fills memory with constant byte      |
| `ft_bzero`   | Zeros out memory                     |
| `ft_memcpy`  | Copies memory area                   |
| `ft_memmove` | Copies memory area (handles overlap) |
| `ft_memchr`  | Scans memory for character           |
| `ft_memcmp`  | Compares memory areas                |
| `ft_calloc`  | Allocates and zeros memory           |

#### Conversion Functions
| Function  | Description                |
|-----------|----------------------------|
| `ft_atoi` | Converts string to integer |
| `ft_itoa` | Converts integer to string |

#### File Descriptor Output
| Function        | Description                                    |
|-----------------|------------------------------------------------|
| `ft_putchar_fd` | Outputs character to file descriptor           |
| `ft_putstr_fd`  | Outputs string to file descriptor              |
| `ft_putendl_fd` | Outputs string with newline to file descriptor |
| `ft_putnbr_fd`  | Outputs integer to file descriptor             |

#### Linked List Functions
| Function          | Description                                        |
|-------------------|----------------------------------------------------|
| `ft_lstnew`       | Creates new list node                              |
| `ft_lstadd_front` | Adds node at beginning of list                     |
| `ft_lstadd_back`  | Adds node at end of list                           |
| `ft_lstsize`      | Counts nodes in list                               |
| `ft_lstlast`      | Returns last node of list                          |
| `ft_lstdelone`    | Deletes single node                                |
| `ft_lstclear`     | Deletes and frees entire list                      |
| `ft_lstiter`      | Applies function to each node's content            |
| `ft_lstmap`       | Creates new list by applying function to each node |

#### The Structure We Used for Linked Lists
```c
typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}	t_list;
```

## Instructions

### Prerequisites
- GCC or CC compiler
- Make utility
- Linux/macOS/Windows environment

### Compilation

Build the library:
```bash
make              # Compiles libft.a
make all          # Compiles libft.a (equivalent to make)
make clean        # Removes object files (.o)
make fclean       # Removes object files and library (libft.a)
make re           # Clean rebuild (fclean + make)
```

### What is libft.a?

`libft.a` is a **static library archive** file generated by compiling the libft project. It contains compiled object code of all library functions and can be linked with C programs to provide the implemented functionality. When you run `make`, the project compiles all `.c` source files into `.o` object files, then archives them into a single `libft.a` file using the `ar` tool. This allows you to easily link your programs against the entire library with just one file, rather than having to compile each function individually.

### Usage

1. Include the header in your source file:
```c
#include "libft.h"
```

2. Compile your program with the library:
```bash
cc -Wall -Wextra -Werror your_program.c -L. -lft -o your_program
```

## Resources

### Documentation & Tutorials
- [Developpez.com - Linked Lists in C](https://chgi.developpez.com/liste/): Comprehensive guide on linked lists and structures
- [Alphorm Blog - Linked Lists](https://blog.alphorm.com/listes-chainees-en-c-concepts-et-applications): Understanding linked list concepts and applications
- **YouTube Channels**: Codeur Sage, Bro Code, Neso Academy - Helpful tutorials on linked lists and C structures
- [GNU C Library Manual](https://www.gnu.org/software/libc/manual/): Official documentation for standard C library functions
- `man` pages: Referenced for understanding the exact behavior of standard functions (`man strlen`,  `man memcpy`, etc.)

### AI Usage
AI assistance (GitHub Copilot) was used for:
- Improving this README documentation
- Ideas to test some functions
- Optimization of a function such as ft_split so as not to exceed 25 lines

## Technical Notes

- All functions are compiled with strict flags: `-Wall -Wextra -Werror` and `cc` compilator
- Memory allocations are systematically checked for failure
- The library handles edge cases such as NULL pointers and empty strings
- All memory-allocating functions document their allocation behavior in comments