#!/bin/bash
echo "SEM Phil Tests Start"
make clean &> /dev/null
make phil$ TYPE=SEM &> /dev/null
for p in {2..51}; do
for n in {1..20}; do
for i in {1..30}; do
    seed=$((RANDOM%10000+1))
    ./phil ${p} ${n} ${seed} > output1
    success=`egrep -ci "Philosophers terminated" output1`;
    deadlock=`egrep -ci "deadlock" output1`;
    fail=`egrep -ci "assertion" output1`;
    if [ ${success} -eq 0 ] || [ ${deadlock} -ne 0 ] || [ ${fail} -ne 0 ]; then
        echo "SEM Test Failed! phil ${p} ${n} ${seed}" >& 2
        echo "Please check output1"
        exit 1;
    fi
    rm output1
done
done
if [ $((${p}%10)) -eq 1 ];then
echo "$(((${p}-1)*600000)) SEM tests passed"
fi
done
echo "***************************************"

echo "INT Phil Tests Start"
make clean &> /dev/null
make phil TYPE=INT &> /dev/null
for p in {2..51}; do
for n in {1..20}; do
for i in {1..30}; do
    seed=$((RANDOM%10000+1))
    ./phil ${p} ${n} ${seed} > output2
    success=`egrep -ci "Philosophers terminated" output2`;
    deadlock=`egrep -ci "deadlock" output2`;
    fail=`egrep -ci "assertion" output2`;
    if [ ${success} -eq 0 ] || [ ${deadlock} -ne 0 ] || [ ${fail} -ne 0 ]; then
        echo "INT Test Failed! phil ${p} ${n} ${seed}" >& 2
        echo "Please check output2"
        exit 1;
    fi
    rm output2
done
done
if [ $((${p}%10)) -eq 1 ];then
echo "$(((${p}-1)*600000)) INT tests passed"
fi
done
echo "***************************************"

echo "INTB Phil Tests Start"
make clean &> /dev/null
make phil TYPE=INTB &> /dev/null
for p in {2..51}; do
for n in {1..20}; do
for i in {1..30}; do
    seed=$((RANDOM%10000+1))
    ./phil ${p} ${n} ${seed} > output3
    success=`egrep -ci "Philosophers terminated" output3`;
    deadlock=`egrep -ci "deadlock" output3`;
    fail=`egrep -ci "assertion" output3`;
    if [ ${success} -eq 0 ] || [ ${deadlock} -ne 0 ] || [ ${fail} -ne 0 ]; then
        echo "INTB Test Failed! phil ${p} ${n} ${seed}" >& 2
        echo "Please check output3"
        exit 1;
    fi
    rm output3
done
done
if [ $((${p}%10)) -eq 1 ];then
echo "$(((${p}-1)*600000)) INTB tests passed"
fi
done
echo "***************************************"
echo "All Tests Passed"
exit 0;

