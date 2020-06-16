#!/bin/bash

make clean
make

regex=".\/\tests.*\.in"

tests=$(find . -regex "$regex")
# echo "$tests"

for i in 0 1 2 3
do
    for test in $tests
    do
        out=$(./straights $i < $test)
        out_return=$?
        size=${#test}
        substr_len=$(expr ${size} - 3)
        regress_file="${test:0:$substr_len}_seed_$i.out"
        echo $regress_file
        diff=$(diff <(echo "$out") <(cat $regress_file))
        valgrind=$(valgrind --leak-check=full --error-exitcode=1 ./straights < $test 2>&1) 
		is_mem_leak=$?
        if [ "$diff" != "" ] || [ $is_mem_leak == 1 ] || [ $out_return == 139 ]
        then
            printf "Failed!"
            if [ $is_mem_leak == 1 ]
            then
                printf " memleak"
            fi
            if [ $out_return == 139 ]
            then
                printf " segfault"
            fi
            printf '\n'
        fi
    done
done