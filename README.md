*This project has been created as part of the 42 curriculum by henirako.*

## Description

**get_next_line** is a function that reads and returns one line at a time from a file descriptor.
The goal is to implement efficient file reading using a static buffer and variadic memory management.
This project improves understanding of file descriptors, static variables, and buffer management.
It also strengthens knowledge of low-level I/O functions like `read()` and memory allocation with `malloc` and `free`.
It is part of the curriculum at **42**

### Supported Features

- Reading from any valid file descriptor
- Returns one complete line per function call
- Handles newline characters (`\n`)
- Supports EOF detection
- Configurable buffer size via `BUFFER_SIZE` macro
- Dynamic memory allocation based on actual content
- Efficient handling of multiple consecutive calls
- Proper error handling and memory cleanup

## Instructions

### Installation and Setup

Clone the repository:
```bash
git clone git@vogsphere.42antananarivo.mg:vogsphere/intra-uuid-c8fd0bca-f52a-40cd-8fd2-aa7cf928bd67-7269378-henirako GET_NEXT_LINE
```
```bash
cd GET_NEXT_LINE
```

Compile the project with the required flags:
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o program
```

The `BUFFER_SIZE` macro defines how many bytes are read per `read()` call:
- Smaller values (e.g., 1): More system calls but minimal memory
- Default (e.g., 42): Balanced performance
- Larger values (e.g., 1024): Fewer system calls but more memory

`Clean object files`
```bash
rm -f *.o
```

`Remove all generated files`
```bash
rm -f program *.o
```

### Example Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

`Compile with:`
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o my_program
```

`Execute with:`
```bash
./my_program
```

## Resources

**References:**  
- [Linux man page - read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux man page - malloc(3)](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [Linux man page - free(3)](https://man7.org/linux/man-pages/man3/free.3.html)
- [GeeksforGeeks - File I/O in C](https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/)
- [Openclassrooms - C Programming](https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c)

**Tutorials (Youtube) and articles on:**
- Memory management in C and avoiding memory leaks
- File descriptors and low-level I/O
- Static variables and their persistence
- Buffer management and string manipulation

### Data Structure

The main structures used are:

- `static char *storage` – maintains the buffer between function calls
- `char *temp` – temporary buffer for `read()` system call
- `char *line` – the extracted line to return
- `int i` – position counter for finding newlines

### Key Functions

- **`read_and_stock()`** – Handles I/O and buffer accumulation
- **`extract_line()`** – Handles line parsing and memory management

### Justification

- **Static variable storage :** Persists between calls, allowing seamless line-by-line reading without losing position in the file.

- **Modular functions :** Separating I/O from line extraction makes the code easier to debug and understand.

- **Recursive number-free approach :** No need for complex data structures; simple string operations suffice.

- **Safe NULL handling :** Checks for NULL pointers before dereferencing to prevent segmentation faults.

- **Configurable buffer size :** The `BUFFER_SIZE` macro allows tuning for different use cases.

This approach ensures the function is **efficient, readable, and fully compliant** with the 42 `get_next_line` subject requirements.

## Bonus

### Bonus features

- Simultaneous support for multiple file descriptors: the bonus version allows calling `get_next_line` on several different `fd` without losing state.
- Provided files: `get_next_line_bonus.c` and `get_next_line_utils_bonus.c` (in addition to `get_next_line.c` and `get_next_line_utils.c`).


### Usage example (bonus version)

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int    fd1, fd2;
    char   *line;

    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);

    line = get_next_line(fd1);
    printf("FD %d (Fichier 1) : %s", fd1, line);
    free(line);

    line = get_next_line(fd2);
    printf("FD %d (Fichier 2) : %s", fd2, line);
    free(line);

    line = get_next_line(fd1);
    printf("FD %d (Fichier 1) : %s", fd1, line);
    free(line);

    line = get_next_line(fd2);
    printf("FD %d (Fichier 2) : %s", fd2, line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

`Compile with:`
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=12 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o my_program_bonus
```

`Execute with:`
```bash
./my_program_bonus
```
### Notes

- Remember to free each line returned by `get_next_line` with `free()`.
- The behavior of `BUFFER_SIZE` remains the same for the bonus version.
- The files `get_next_line_bonus.c` and `get_next_line_utils_bonus.c` implement per-`fd` storage logic to keep separate buffers per descriptor.

