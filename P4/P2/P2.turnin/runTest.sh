#!/bin/bash -f

./test_primes 4 13 100 1059251 3293201 2>test_primes_stderr
if [ -s test_primes_stderr ]; then
    cat test_primes_stderr
    exit 1
else
    exit 0
fi

