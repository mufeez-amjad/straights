#!/bin/bash

make clean
make

regex=".\/\tests.*\.in"

tests=$(find . -regex "$regex")
# echo "$tests"

function run_test() {
    test=$1
    test_name=$2
    regress_file=$3
    seed=$4
    tmpfile=$(mktemp "$test_name".XXXXXX)
    echo $regress_file
    ./straights $seed < $test > $tmpfile
    out_return=$?
    diff=$(diff $tmpfile $regress_file)
    different=$?
    valgrind=$(valgrind --leak-check=full --error-exitcode=1 ./straights < $test 2>&1)
    is_mem_leak=$?
    if [ $different != 0 ] || [ $is_mem_leak == 1 ] || [ $out_return == 139 ]
    then
        printf "Failed!"
        echo "$diff"
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
    rm "$tmpfile"
}

for test in $tests
do
    size=${#test}
    substr_len=$(expr ${size} - 3)
    test_name="${test:0:$substr_len}"
    if [[ $test == *"seed"* ]];
    then
        for i in 0 1 2 3
        do
            regress_file="${test_name}_$i.out"
            run_test $test $test_name $regress_file $i
        done
    else
        regress_file="${test_name}.out"
        seed="${test_name: -1}"
        run_test $test $test_name $regress_file $seed
    fi
done