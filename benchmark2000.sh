#!/bin/bash

MAX=0
ITERATIONS=0
LIMIT=40000
FILE=problem_2000
SUM=0
i=1
while [ "$i" -lt 101 ]
do
		ARG=`ruby -e "puts (1..2000).to_a.shuffle.join(' ')"`
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
		echo $i ":" $NUMBER "-" $MAX
		SUM=$(($SUM + $NUMBER))
		ITERATIONS=$(($ITERATIONS + 1))
		i=$((i + 1))
done

echo "AVG: $(($SUM / $ITERATIONS))"
echo "MAX: " $MAX
echo "ARG: " $ARG
