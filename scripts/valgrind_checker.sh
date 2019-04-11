# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    checker.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 13:36:20 by aulopez           #+#    #+#              #
#    Updated: 2019/04/11 13:52:40 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

echo "Dont' forget to test for memory leaks too !"

echo "\n======== Basic Test ========"
echo "1. Expect OK         : \\c" ; echo "\c" | valgrind ../checker 1
echo "2. Expect OK         : \\c" ; echo "\c" | valgrind ../checker -1
echo "3. Expect OK         : \\c" ; echo "\c" | valgrind ../checker 0
echo "4. Expect OK         : \\c" ; echo "sa" | valgrind ../checker 2 1
echo "5. Expect OK         : \\c" ; echo "\c" | valgrind ../checker 1 2
echo "6. Expect OK         : \\c" ; echo "\c" | valgrind ../checker -1 1
echo "7. Expect OK         : \\c" ; echo "pb\npa" | valgrind ../checker 1
echo "8. Expect OK         : \\c" ; echo "\c" | valgrind ../checker -2147483648 0 2147483647
echo "9. Expect OK (*)     : \\c" ; echo "\c" | valgrind ../checker 01 002
echo "10.Expect OK (*)     : \\c" ; echo "\c" | valgrind ../checker +1 +02
echo "14.Expect KO         : \\c" ; echo "\c" | valgrind ../checker 2 1
echo "15.Expect KO         : \\c" ; echo "sa" | valgrind ../checker 1 2
echo "16.Expect KO         : \\c" ; echo "pb" | valgrind ../checker 1
echo "14.Expect Nothing    : \\c" ; echo "\c" | valgrind ../checker ; echo


echo "\n\n======== Error Arg ========"
echo "1. Expect Error      : \\c" ; echo "\c" | valgrind ../checker A
echo "2. Expect Error (*)  : \\c" ; echo "\c" | valgrind ../checker -
echo "3. Expect Error      : \\c" ; echo "\c" | valgrind ../checker 0 0
echo "4. Expect Error      : \\c" ; echo "\c" | valgrind ../checker 1 0 1
echo "5. Expect Error      : \\c" ; echo "\c" | valgrind ../checker -1 -1
echo "6. Expect Error      : \\c" ; echo "\c" | valgrind ../checker 2147483648
echo "7. Expect Error      : \\c" ; echo "\c" | valgrind ../checker -2147483649
echo "8. Expect Error      : \\c" ; echo "\c" | valgrind ../checker 100000000000000
echo "9. Expect Error      : \\c" ; echo "\c" | valgrind ../checker 1a
echo "10.Expect Error      : \\c" ; echo "\c" | valgrind ../checker a0
echo "11.Expect Error  (*) : \\c" ; echo "\c" | valgrind ../checker "\01"
echo "12.Expect Error  (*) : \\c" ; echo "\c" | valgrind ../checker "1\01"
echo "13.Expect Error  (*) : \\c" ; echo "\c" | valgrind ../checker "1\0"
echo "14.Expect Error      : \\c" ; echo "\c" | valgrind ../checker 1-
echo "15.Expect Error      : \\c" ; echo "\c" | valgrind ../checker 1+

echo "\n\n======== Error Cmd ========"
echo "1. Expect Error      : \\c" ; echo "sas" | valgrind ../checker 1 2
echo "2. Expect Error      : \\c" ; echo "s" | valgrind ../checker 1 2
echo "3. Expect Error      : \\c" ; echo "\0" | valgrind ../checker 1 2
echo "4. Expect Error      : \\c" ; echo "\0sa" | valgrind ../checker 1 2
echo "5. Expect Error      : \\c" ; echo "sa\0" | valgrind ../checker 1 2
echo "6. Expect Error      : \\c" ; echo "sas ls" | valgrind ../checker 1 2
echo "7. Expect Error      : \\c" ; echo "sas ls" | valgrind ../checker 1 2
echo "8. Expect Error      : \\c" ; echo "      ss" | valgrind ../checker 2 1
echo "9. Expect Error      : \\c" ; echo "ss      " | valgrind ../checker 2 1
echo "10.Expect Error      : \\c" ; echo "      ss      " | valgrind ../checker 2 1
echo "11.Expect Error      : \\c" ; echo "	ss" | valgrind ../checker 2 1
echo "12.Expect Error      : \\c" ; echo "ss " | valgrind ../checker 2 1
echo "13.Expect Error      : \\c" ; echo "rra\\c" | valgrind ../checker 2 1
echo "14.Expect Error      : \\c" ; echo "rra\nrra\\c" | valgrind ../checker 1 2
echo "15.Expect Error      : \\c" ; echo "sa\nrra\\c" | valgrind ../checker 1 2
echo "16.Expect Error      : \\c" ; echo "ra\nrra\\c" | valgrind ../checker 1 2
echo "17.Expect Error      : \\c" ; echo "sa\nrra\nls" | valgrind ../checker 1 2
echo "18.Expect Error      : \\c" ; echo "" | valgrind ../checker 1 2
echo "19.Expect Error      : \\c" ; echo "ss\nls" | valgrind ../checker 2 1

echo "\n\n======== Useless Cmd ======"
echo "1. Expect OK         : \\c" ; echo "pa\nsb\nsa\nss\nra\nrb\nrr\nrra\nrrb\nrrr" | valgrind ../checker 1
echo "2. Expect OK         : \\c" ; echo "pb\nsb\nsa\nss\nra\nrb\nrr\nrra\nrrb\nrrr\npa" | valgrind ../checker 1 2
echo "3. Expect OK         : \\c" ; echo "pb\npb\npa\npa\npa\npa\npa\npa" | valgrind ../checker 1 2

echo "\n\n======= Args Space ========"
echo "In my opinion, this is a bonus."
echo "1. Expect Nothing/Err: \\c" ; valgrind ../checker ""
echo "2. Expect Nothing/Err: \\c" ; valgrind ../checker "        "
echo "3. Expect OK/Err     : \\c" ; valgrind ../checker "" 1
echo "4. Expect OK/Err     : \\c" ; valgrind ../checker "        " 1
echo "5. Expect OK/Err     : \\c" ; valgrind ../checker 1 ""
echo "6. Expect OK/Err     : \\c" ; valgrind ../checker 1 "        "
echo "7. Expect OK         : \\c" ; echo "\c" | valgrind ../checker "1       "
echo "8. Expect OK         : \\c" ; echo "\c" | valgrind ../checker "       1"
echo "9. Expect OK         : \\c" ; echo "\c" | valgrind ../checker "       1      "
echo "10.Expect OK         : \\c" ; echo "sa" | valgrind ../checker "2 1" 22
echo "11.Expect OK         : \\c" ; echo "sa" | valgrind ../checker "2 "1 22
echo "12.Expect OK         : \\c" ; echo "sa" | valgrind ../checker 2 " 1" 22
echo "13.Expect OK         : \\c" ; echo "ra" | valgrind ../checker 2"1" 3 4
echo "14.Expect OK         : \\c" ; echo "ra" | valgrind ../checker "1"2 3 4
echo "15.Expect OK         : \\c" ; echo "sa" | valgrind ../checker 2" 1" 22
echo "16.Expect OK         : \\c" ; echo "sa" | valgrind ../checker "2 "1 22
echo "17.Expect OK         : \\c" ; echo "ra" | valgrind ../checker 1"2  " 3 4
echo "18.Expect OK         : \\c" ; echo "ra" | valgrind ../checker "   1"2 3 4
echo "19.Expect OK         : \\c" ; echo "sa" | valgrind ../checker 1"     "
echo "20.Expect OK         : \\c" ; echo "\c" | valgrind ../checker "      "1
echo "21.Expect OK         : \\c" ; echo "\c" | valgrind ../checker ""1
echo "22.Expect OK         : \\c" ; echo "\c" | valgrind ../checker 1""
