#!/bin/bash

MAX=0
ITERATIONS=0
LIMIT=700
FILE=problem_100
SUM=0

for i in {1..1000}
do
		ARG=`ruby -e "puts (1..100).to_a.shuffle.join(' ')"`
		if ./push_swap $ARG | ./checker $ARG | grep -q KO
		then
			echo "Error!"
			echo $ARG
			break
		fi
		NUMBER="$(./push_swap $ARG | wc -l | sed 's/ //g')"
		if [ "$NUMBER" -gt "$LIMIT" ]
			then
			echo $NUMBER >> $FILE
			echo $ARG >> $FILE
		fi
		if [ "$NUMBER" -gt "$MAX" ]
			then
			MAX=$NUMBER;
		fi
		echo $i ":" $NUMBER
		$SUM= $SUM + $NUMBER;
		$ITERATIONS= $ITERATIONS + 1
done

echo "AVG: $(($SUM / $ITERATIONS))"
echo "MAX: " $MAX