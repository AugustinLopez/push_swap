ARG=`ruby -e "puts (1..$1).to_a.shuffle.join(' ')"`
./push_swap $ARG
./push_swap $ARG | ./checker -v $ARG
./push_swap $ARG | wc -l
echo $ARG
