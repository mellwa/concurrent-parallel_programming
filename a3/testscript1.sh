#!/bin/bash

SOLN=./bufferBUSY_64 # correct soln
MYFUN=./buffer # my solution
fail=0
cons=50;
prods=50;
produce=5;
buffersize=10;
delays=10;
for (( i=2; i<= 1000; i +=1 ));do
cons=$((RANDOM%50))
prods=$((RANDOM%55))
buffersize=$((RANDOM%50))
$SOLN ${cons} ${prods} $i ${buffersize} 10 > out.out
$MYFUN ${cons} ${prods} $i ${buffersize} 10  > soln.out
diff out.out soln.out > /dev/null
if [ ${?} -ne 0 ]; then
echo “Test failed:” $CONFIG $i
diff out.out soln.out > $i.out
fail=1
else
echo "test pass"
rm out.out
rm soln.out
fi
done
if [ $fail -ne 1 ]; then
echo “ALL TESTS PASSED”
fi