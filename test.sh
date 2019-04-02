ARG=`ruby -e "puts (1..$1).to_a.shuffle.join(' ')"`
./ps $ARG | ./checker $2 $ARG
