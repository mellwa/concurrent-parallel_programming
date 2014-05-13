#!/bin/bash
echo "Soda Tests Start"
make clean &> /dev/null
make &> /dev/null
RUN=./soda # my solution
g++ -o gen gen.cc
generate=./gen
for (( i=1; i <= 10000; i +=1 ));do
    ${generate} > tmpSoda.config
    $RUN tmpSoda.config $i &> my.out
    echo $i >> seed.txt
    if [ ${?} -ne 0 ]; then
        echo "Test failed:" $CONFIG $i
    fi
    runtimeWarning=`egrep -ci "warning" my.out`;
    runtimeError=`egrep -ci "error" my.out`;
    finish=`egrep -ci "***********************" my.out`;
    deadlock=`egrep -ci "deadlock" my.out`;
    assertion=`egrep -ci "Assertion" my.out`;
    if [ ${finish} -eq 0 ] || [ ${deadlock} -ne 0 ] || 
       [ ${assertion} -ne 0 ] || [ ${runtimeWarning} -ne 0 ] || 
       [ ${runtimeError} -ne 0 ]; then
        echo "test failed! Please see my.out" >& 2
        exit 1;
    fi
    rm my.out
    if [ $(($i%10)) -eq 0 ]; then
        echo "${i} tests passed"
    fi

done

echo "***************************************"
