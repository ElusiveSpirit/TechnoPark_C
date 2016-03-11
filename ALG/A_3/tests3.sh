#!/bin/bash
file="main"
tests="maketest"
inputTest="inputTest"
if test -f $file; then rm $file; fi
if test -f $tests; then rm $tests; fi
gcc -o $file "$file.c"
gcc -o $tests "$tests.c"

if test -f $tests ; then
    ./$tests
fi

if test -f $file
then

    totalWrong=0
    launch="./$file"
    i=0
    while read line
    do

        if [[ $i -eq 0 ]]; then
            testOut=$line
            ((i++))
        else
            testIn=$line
            factOut=`echo -e $testIn | $launch`

            if [ "$testOut" != "$factOut" ]
            then
                ((totalWrong++))
                echo "---------------------------------"
                echo -e "Input   < \"$testIn\""
                echo -e "Output  > \"$factOut\""
                echo "testOut > \"$testOut\""
                echo -e "\e[1;31mfalse\e[0m"
                echo "---------------------------------"

            fi
            i=0
        fi
    done < $inputTest

    echo "Error in test: $totalWrong"
else
    echo "error in compiling file"
fi
