#!/bin/bash

gmax=50;
tmax=50;
max=100000;
counter=0;
echo "test 500 iterations."
for i in {1..500}
do
	    
	    group=$(( RANDOM % ${gmax} +1));
		if [ $((group%2)) -ne 1 ]; then
			group=$((group+1));
		fi
	    tour=$(( $(( RANDOM % ${tmax} +1)) * ${group} ));
	    seed=$(( RANDOM % ${max} +1));
	    
	    echo "${tour} ${group} ${seed}" >> input;
	
	./vote ${tour} ${group} ${seed} > expect.output ;
	if [ $? -ne 0 ]; then
		echo "# ${i} test failed, please see expect.out" >& 2;
		exit 1;
	fi
	x=`egrep -ci "All tours started" expect.output`;
    y=`egrep -ci "deadlock" expect.output`;
    if [ ${x} -eq 0 ] || [ ${y} -ne 0 ]; then
        echo "test failed with input ${group} ${tour} ${seed}" >& 2
        #echo "and output: " >& 2
        #cat out.temp;
        exit 1;
    fi
	
	if [ $((${i} % 50)) -eq 0 ]; then
		echo "${i} tests passed."
	fi
	#echo "${i} tests passed."
	rm expect.output;
done
exit 0;

