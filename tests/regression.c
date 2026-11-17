#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifdef BONUS
# include "get_next_line_bonus.h"
#else
# include "get_next_line.h"
#endif

void *__real_malloc(size_t size);
void __real_free(void *ptr);
static int live;
static int fail_at = -1;
static int calls;
void *__wrap_malloc(size_t size)
{
    void *ptr;
    if (calls++ == fail_at)
        return (NULL);
    ptr = __real_malloc(size);
    if (ptr)
        live++;
    return (ptr);
}
void __wrap_free(void *ptr)
{
    if (ptr)
        live--;
    __real_free(ptr);
}
static int input(const char *text)
{
    char path[] = "/tmp/gnl-test-XXXXXX";
    int fd = mkstemp(path);
    assert(fd >= 0);
    unlink(path);
    assert(write(fd, text, strlen(text)) == (ssize_t)strlen(text));
    assert(lseek(fd, 0, SEEK_SET) == 0);
    return (fd);
}
static void check(const char *text)
{
    int fd = input(text);
    const char *end;
    size_t len;
    char *line;
    while (*text)
    {
        end = strchr(text, '\n');
        len = end ? (size_t)(end - text + 1) : strlen(text);
        line = get_next_line(fd);
        assert(line && strlen(line) == len && !memcmp(line, text, len));
        free(line);
        assert(live == 0);
        text += len;
    }
    assert(get_next_line(fd) == NULL);
    assert(get_next_line(fd) == NULL);
    assert(live == 0);
    close(fd);
}
int main(int argc, char **argv)
{
    char *line;
    char long_line[10003];
    int fd;
    int n;
#ifdef BONUS
    int other;
#endif
    (void)argv;
    if (argc > 1)
    {
        fd = input("first\nsecond\nthird");
        line = get_next_line(fd);
        assert(line && !strcmp(line, "first\n"));
        free(line);
        close(fd);
        assert(live == 0);
        return (0);
    }
    check("");
    check("\n");
    check("\n\n\n");
    check("one\ntwo\nthree");
    check("one\ntwo\nthree\n");
    check("no newline");
    memset(long_line, 'x', 10000);
    memcpy(long_line + 10000, "\ny", 3);
    check(long_line);
    assert(get_next_line(-1) == NULL);
    assert(get_next_line(1000000) == NULL);
    fd = open("/tmp", O_RDONLY);
    assert(fd >= 0 && get_next_line(fd) == NULL);
    close(fd);
    fd = input("a\nb\nc");
    line = get_next_line(fd);
    assert(line);
    free(line);
    close(fd);
    /* Drain cached lines, then observe the failed read. */
    while ((line = get_next_line(fd)))
        free(line);
    assert(live == 0);
#ifdef BONUS
    fd = input("a\nb\n");
    other = input("x\ny");
    line = get_next_line(fd);
    assert(line && !strcmp(line, "a\n"));
    free(line);
    line = get_next_line(other);
    assert(line && !strcmp(line, "x\n"));
    free(line);
    line = get_next_line(fd);
    assert(line && !strcmp(line, "b\n"));
    free(line);
    line = get_next_line(other);
    assert(line && !strcmp(line, "y"));
    free(line);
    assert(!get_next_line(fd) && !get_next_line(other));
    close(fd);
    close(other);
#endif
    for (n = 0; n < 60; n++)
    {
        fd = input("abcdefghijklmnop\nsecond\nthird");
        calls = 0;
        fail_at = n;
        while ((line = get_next_line(fd)))
            free(line);
        fail_at = -1;
        assert(live == 0);
        close(fd);
    }
    return (0);
}
