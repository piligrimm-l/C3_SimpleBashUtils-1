#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a basics=(
"s test_0_grep.txt VAR"
"for s21_grep.c s21_grep.h Makefile VAR"
"for s21_grep.c VAR"
"-e for -e ^int s21_grep.c s21_grep.h Makefile VAR"
"-e for -e ^int s21_grep.c VAR"
"-e regex -e ^print s21_grep.c VAR -f test_ptrn_grep.txt"
"-e while -e void s21_grep.c Makefile VAR -f test_ptrn_grep.txt"
)

declare -a combi=(
"-n for test_1_grep.txt test_2_grep.txt"
"-n for test_1_grep.txt"
"-n -e ^\} test_1_grep.txt"
"-c -e PR test_1_grep.txt"
"-ce ^int test_1_grep.txt test_2_grep.txt"
"-e ^int test_1_grep.txt"
"-nivh = test_1_grep.txt test_2_grep.txt"
"-e"
"-ie INT test_5_grep.txt"
"-echar test_1_grep.txt test_2_grep.txt"
"-ne = -e out test_5_grep.txt"
"-iv int test_5_grep.txt"
"-in int test_5_grep.txt"
"-c -l aboba test_1_grep.txt test_5_grep.txt"
"-v test_1_grep.txt -e ank"
"-noe ) test_5_grep.txt"
"-l for test_1_grep.txt test_2_grep.txt"
"-o -e int test_4_grep.txt"
"-e = -e out test_5_grep.txt"
"-noe ing -e as -e the -e not -e is test_6_grep.txt"
"-e ing -e as -e the -e not -e is test_6_grep.txt"
"-c -e . test_1_grep.txt -e '.'"
"-l for no_file.txt test_2_grep.txt"
"-f test_3_grep.txt test_5_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    #if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    if [ "$DIFF_RES" == "Файлы test_s21_grep.log и test_sys_grep.log идентичны" ]
    then
      (( SUCCESS++ ))
      printf "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t\n"
    else
      (( FAIL++ ))
      printf "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t\n"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

for index in "${combi[@]}"
do
    var="-"
    testing $index
done

# one key
for var1 in v c l n h o i H y E
do
    for index in "${basics[@]}"
    do
        var="-$var1"
        testing $index
    done
done

# two keys
for var1 in v c l n h o i H y E
do
    for var2 in v c l n h o i H y E
    do
        if [ $var1 != $var2 ]
        then
            for index in "${basics[@]}"
            do
                var="-$var1 -$var2"
                testing $index
            done
        fi
    done
done

# three keys
for var1 in v c l n h o i H y E
do
    for var2 in v c l n h o i H y E
    do
        for var3 in v c l n h o i H y E
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for index in "${basics[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $index
                done
            fi
        done
    done
done

# two double keys
for var1 in v c l n h o i H y E
do
    for var2 in v c l n h o i H y E
    do
        if [ $var1 != $var2 ]
        then
            for index in "${basics[@]}"
            do
                var="-$var1$var2"
                testing $index
            done
        fi
    done
done

# three triple keys
for var1 in v c l n h o i H y E
do
    for var2 in v c l n h o i H y E
    do
        for var3 in v c l n h o i H y E
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for index in "${basics[@]}"
                do
                    var="-$var1$var2$var3"
                    testing $index
                done
            fi
        done
    done
done

printf "\033[31mFAIL: $FAIL\033[0m\n"
printf "\033[32mSUCCESS: $SUCCESS\033[0m\n"
printf "ALL: $COUNTER\n"
