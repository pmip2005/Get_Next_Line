#!/bin/sh
set -eu
cd /mnt/c/Users/crazy/Documents/Code/Test/get_next_line
for size in 1 2 42 122 4096; do
    for variant in mandatory bonus; do
        suffix=
        define=
        if [ "$variant" = bonus ]; then
            suffix=_bonus
            define=-DBONUS
        fi
        cc -Wall -Wextra -Werror -g -fsanitize=address,undefined -DBUFFER_SIZE=$size $define -I. tests/regression.c get_next_line${suffix}.c get_next_line_utils${suffix}.c -Wl,--wrap=malloc -Wl,--wrap=free -o /tmp/gnl-regression
        /tmp/gnl-regression
        /tmp/gnl-regression once
        echo "$variant BUFFER_SIZE=$size passed"
    done
done
