#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a basics=(
"VAR test_case_cat.txt"
"VAR one_letter.txt"
"VAR empty.txt"
"VAR one_newline_character.txt"
"VAR help_s21_cat.txt"
"VAR s_squeeze_blank_flags_test.txt"
"VAR TE_te_show_tabs_ends_test.txt"
"VAR two_newline_character.txt"
"VAR v_test.txt"
)

declare -a combi=(
"-s test_1_cat.txt"
"-b -e -n -s -t -v test_1_cat.txt"
"-t test_3_cat.txt"
"-n test_2_cat.txt"
"no_file.txt"
"-n -b test_1_cat.txt"
"-s -n -e test_4_cat.txt"
"test_1_cat.txt -n"
"-n test_1_cat.txt"
"-n test_1_cat.txt test_2_cat.txt"
"-v test_5_cat.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    (( COUNTER++ ))
    #if [ "$DIFF_RES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    if [ "$DIFF_RES" == "Файлы test_s21_cat.log и test_sys_cat.log идентичны" ]
    then
      (( SUCCESS++ ))
        printf "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $t\n"
    else
      (( FAIL++ ))
        printf "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $t\n"
    fi
    rm test_s21_cat.log test_sys_cat.log
}

# combi tests
for i in "${combi[@]}"
do
    var="-"
    testing $i
done

# 1 key
for var1 in A b E e n s T t v
do
    for i in "${basics[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 keys
for var1 in A b E e n s T t v
do
    for var2 in A b E e n s T t v
    do
        if [ $var1 != $var2 ]
        then
            for i in "${basics[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# 3 keys 
for var1 in A b E e n s T t v
do
    for var2 in A b E e n s T t v
    do
        for var3 in A b E e n s T t v
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${basics[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

# 4 keys
for var1 in A b E e n s T t v
do
    for var2 in A b E e n s T t v
    do
        for var3 in A b E e n s T t v
        do
            for var4 in A b E e n s T t v
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${basics[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

printf "\033[31mFAIL: $FAIL\033[0m\n"
printf "\033[32mSUCCESS: $SUCCESS\033[0m\n"
printf "ALL: $COUNTER\n"
