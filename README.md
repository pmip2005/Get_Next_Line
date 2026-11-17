*This project has been created as part of the 42 curriculum by ppoco.*

# Get Next Line

## Table of contents

- [Description](#description)
- [Instructions](#instructions)
- [Algorithm and justification](#algorithm-and-justification)
- [Bonus](#bonus)
- [Known limitation: stack overflow](#known-limitation-stack-overflow)
- [Tests passed](#tests-passed)
- [Resources](#resources)
- [AI usage](#ai-usage)

## Description

I built a C function that reads one line per call from a file descriptor. Through this project, I explored static storage, buffered input, string manipulation, and memory ownership.

```c
char    *get_next_line(int fd);
```

The function returns an allocated, null-terminated line, including its newline when present. The final line may have no newline. End of input with no remaining characters, or an error, returns `NULL`. The caller must free each returned line.

The project includes the mandatory implementation and the bonus, which maintains independent reading state for multiple file descriptors.

## Instructions

Use a Unix-like environment with a C compiler, such as campus Linux or WSL. Run these commands from the project directory.

To compile the sources into object files:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line.c get_next_line_utils.c
```

To run the function, supply your own `main.c`. Include `get_next_line.h`, open a file, call `get_next_line(fd)` until it returns `NULL`, free every returned line, and close the descriptor.

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
./gnl
```

Arguments depend on your test program. The function is compiled with a test program rather than used as a standalone executable. Without the `-D BUFFER_SIZE` flag, the header supplies a default buffer size.

Compile the bonus with a caller-provided `main_bonus.c`:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
./gnl_bonus
```

Compile mandatory and bonus implementations separately; both export `get_next_line`.

## Algorithm and justification

The algorithm accumulates chunks from `read()`, extracts the prefix through the first newline (or remaining text at EOF), and saves the suffix for the next call. Saved text is checked before reading additional input, so a line already buffered can be returned directly.

Helper functions handle newline detection, string concatenation, line extraction, and preservation of the remaining text. Separating these responsibilities keeps the reading logic easier to follow.

A static array of pointers preserves one remainder per descriptor in the bonus implementation. The array is one static variable, and indexing it by `fd` lets interleaved calls retain independent state. The array’s capacity is an implementation bound, not a universal operating-system limit.

This representation makes persistent state straightforward to manage. Repeated concatenation can take quadratic time for a long line because accumulated text is repeatedly copied. Memory use depends on saved remainders, temporary buffers, and the returned line.

## Bonus

The bonus supports interleaved reads from multiple descriptors using one static variable. It is provided in:

```text
get_next_line_bonus.c
get_next_line_bonus.h
get_next_line_utils_bonus.c
```

For example, calls can alternate between two open files without mixing their lines or losing either file’s saved remainder. A fully working mandatory part is required for bonus evaluation.

## Known limitation: stack overflow

My implementation uses a local read buffer sized from `BUFFER_SIZE`. An excessively large value can exhaust the available stack and crash the program. This is a stack overflow risk, rather than a buffer overflow caused by writing past the end of an array.

After comparing my implementation with other people’s projects that had passed, I decided to keep this tradeoff. Addressing it would mean refactoring how I allocate and manage the read buffer, and I chose not to be too pedantic about it given the effort involved. That comparison doesn’t remove the limitation: very large buffer sizes can still break this implementation.

As my favorite joke goes: “Sounds like a caller Issue to me”

Jokes aside, `BUFFER_SIZE` is a compile-time setting, and handling the buffer safely is still my implementation’s responsibility.

## Tests passed

My implementation passes tests covering:

- Empty files and consecutive newlines.
- A final line without a trailing newline.
- Lines longer than the read buffer.
- Reading from standard input.
- Invalid file descriptors.
- Interleaved reads from multiple file descriptors in the bonus.

The large-buffer limitation described above still applies.

## Resources

- The subject assigned on [42 Intra](https://intra.42.fr/) is authoritative for evaluation.
- [POSIX read()](https://pubs.opengroup.org/onlinepubs/9799919799/functions/read.html), [malloc()](https://pubs.opengroup.org/onlinepubs/9799919799/functions/malloc.html), and [free()](https://pubs.opengroup.org/onlinepubs/9799919799/functions/free.html).
- [42 Norminette](https://github.com/42School/norminette).
- [junbuan/get_next_line](https://github.com/junbuan/get_next_line): I used this bonus-inclusive project’s README as a reference for the structure of my documentation.

### AI usage

I used Codex to find documentation references and help draft and edit this README.
