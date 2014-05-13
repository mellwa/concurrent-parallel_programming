#!/bin/bash
MYFUN=./vote # my solution

for (( i=1; i<= 1000; i +=1 ));do
    G=$((RANDOM%100 + 1))
    if [ $((G%2)) -ne 1 ]; then
    G=$((G+1));
    fi
    V=$(( $((RANDOM%10 + 1))*${G} ))
    $MYFUN ${V} ${G} ${i} > my.out

	if [ ${?} -ne 0 ]; then
		echo “Test failed:” $CONFIG $i
        exit 1;
	fi
    finish=`egrep -ci "All tours started" my.out`;
    deadlock=`egrep -ci "deadlock" my.out`;
    assertion=`egrep -ci "Assertion" my.out`;
if [ ${finish} -eq 0 ] || [ ${deadlock} -ne 0 ] || [ ${assertion} -ne 0 ]; then
    echo "test failed --- arguments: ${V} ${G} ${i}" >& 2
    exit 1;
    fi
    rm my.out

done

echo "Test passed."

