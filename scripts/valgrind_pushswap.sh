ARG=`ruby -e "puts (1..$1).to_a.shuffle.join(' ')"`
valgrind ../push_swap $ARG
