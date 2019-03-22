ARG=`ruby -e "puts (1..$1).to_a.shuffle.join(' ')"`
./push_swap $ARG
./push_swap $ARG | ./checker $2 $ARG
printf "\n\nInstruction : "
./push_swap $ARG | wc -l | column -t
printf "Feed : "
echo $ARG
