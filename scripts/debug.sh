# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    checker.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 13:36:20 by aulopez           #+#    #+#              #
#    Updated: 2019/04/11 14:04:39 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

echo "Dont' forget to test for memory leaks too !"

echo "\n======== Basic Test ========"
echo "1. Expect OK         : \\c" ; echo "\c" | ../checker 1
echo "2. Expect OK         : \\c" ; echo "\c" | ../checker -1
echo "3. Expect OK         : \\c" ; echo "\c" | ../checker 0
echo "4. Expect OK         : \\c" ; echo "sa" | ../checker 2 1
echo "5. Expect OK         : \\c" ; echo "\c" | ../checker 1 2
echo "6. Expect OK         : \\c" ; echo "\c" | ../checker -1 1
echo "7. Expect OK         : \\c" ; echo "pb\npa" | ../checker 1
echo "8. Expect OK         : \\c" ; echo "\c" | ../checker -2147483648 0 2147483647
echo "9. Expect OK (*)     : \\c" ; echo "\c" | ../checker 01 002
echo "10.Expect OK (*)     : \\c" ; echo "\c" | ../checker +1 +02
echo "14.Expect KO         : \\c" ; echo "\c" | ../checker 2 1
echo "15.Expect KO         : \\c" ; echo "sa" | ../checker 1 2
echo "16.Expect KO         : \\c" ; echo "pb" | ../checker 1
echo "14.Expect Nothing    : \\c" ; echo "\c" | ../checker ; echo


echo "\n\n======== Error Arg ========"
echo "1. Expect Error      : \\c" ; echo "\c" | ../checker A
echo "2. Expect Error (*)  : \\c" ; echo "\c" | ../checker -
echo "3. Expect Error      : \\c" ; echo "\c" | ../checker 0 0
echo "4. Expect Error      : \\c" ; echo "\c" | ../checker 1 0 1
echo "5. Expect Error      : \\c" ; echo "\c" | ../checker -1 -1
echo "6. Expect Error      : \\c" ; echo "\c" | ../checker 2147483648
echo "7. Expect Error      : \\c" ; echo "\c" | ../checker -2147483649
echo "8. Expect Error      : \\c" ; echo "\c" | ../checker 100000000000000
echo "9. Expect Error      : \\c" ; echo "\c" | ../checker 1a
echo "10.Expect Error      : \\c" ; echo "\c" | ../checker a0
echo "11.Expect Error  (*) : \\c" ; echo "\c" | ../checker "\01"
echo "12.Expect Error  (*) : \\c" ; echo "\c" | ../checker "1\01"
echo "13.Expect Error  (*) : \\c" ; echo "\c" | ../checker "1\0"
echo "14.Expect Error      : \\c" ; echo "\c" | ../checker 1-
echo "15.Expect Error      : \\c" ; echo "\c" | ../checker 1+

echo "\n\n======== Error Cmd ========"
echo "1. Expect Error      : \\c" ; echo "sas" | ../checker 1 2
echo "2. Expect Error      : \\c" ; echo "s" | ../checker 1 2
echo "3. Expect Error      : \\c" ; echo "\0" | ../checker 1 2
echo "4. Expect Error      : \\c" ; echo "\0sa" | ../checker 1 2
echo "5. Expect Error      : \\c" ; echo "sa\0" | ../checker 1 2
echo "6. Expect Error      : \\c" ; echo "sas ls" | ../checker 1 2
echo "7. Expect Error      : \\c" ; echo "sas ls" | ../checker 1 2
echo "8. Expect Error      : \\c" ; echo "      ss" | ../checker 2 1
echo "9. Expect Error      : \\c" ; echo "ss      " | ../checker 2 1
echo "10.Expect Error      : \\c" ; echo "      ss      " | ../checker 2 1
echo "11.Expect Error      : \\c" ; echo "	ss" | ../checker 2 1
echo "12.Expect Error      : \\c" ; echo "ss " | ../checker 2 1
echo "13.Expect Error      : \\c" ; echo "rra\\c" | ../checker 2 1
echo "14.Expect Error      : \\c" ; echo "rra\nrra\\c" | ../checker 1 2
echo "15.Expect Error      : \\c" ; echo "sa\nrra\\c" | ../checker 1 2
echo "16.Expect Error      : \\c" ; echo "ra\nrra\\c" | ../checker 1 2
echo "17.Expect Error      : \\c" ; echo "sa\nrra\nls" | ../checker 1 2
echo "18.Expect Error      : \\c" ; echo "" | ../checker 1 2
echo "19.Expect Error      : \\c" ; echo "ss\nls" | ../checker 2 1

echo "\n\n======== Useless Cmd ======"
echo "1. Expect OK         : \\c" ; echo "pa\nsb\nsa\nss\nra\nrb\nrr\nrra\nrrb\nrrr" | ../checker 1
echo "2. Expect OK         : \\c" ; echo "pb\nsb\nsa\nss\nra\nrb\nrr\nrra\nrrb\nrrr\npa" | ../checker 1 2
echo "3. Expect OK         : \\c" ; echo "pb\npb\npa\npa\npa\npa\npa\npa" | ../checker 1 2

echo "\n\n======= Args Space ========"
echo "In my opinion, this is a bonus."
echo "1. Expect Nothing/Err: \\c" ; ../checker ""
echo "2. Expect Nothing/Err: \\c" ; ../checker "        "
echo "3. Expect OK/Err     : \\c" ; ../checker "" 1
echo "4. Expect OK/Err     : \\c" ; ../checker "        " 1
echo "5. Expect OK/Err     : \\c" ; ../checker 1 ""
echo "6. Expect OK/Err     : \\c" ; ../checker 1 "        "
echo "7. Expect OK         : \\c" ; echo "\c" | ../checker "1       "
echo "8. Expect OK         : \\c" ; echo "\c" | ../checker "       1"
echo "9. Expect OK         : \\c" ; echo "\c" | ../checker "       1      "
echo "10.Expect OK         : \\c" ; echo "sa" | ../checker "2 1" 22
echo "11.Expect OK         : \\c" ; echo "sa" | ../checker "2 "1 22
echo "12.Expect OK         : \\c" ; echo "sa" | ../checker 2 " 1" 22
echo "13.Expect OK         : \\c" ; echo "ra" | ../checker 2"1" 3 4
echo "14.Expect OK         : \\c" ; echo "ra" | ../checker "1"2 3 4
echo "15.Expect OK         : \\c" ; echo "sa" | ../checker 2" 1" 22
echo "16.Expect OK         : \\c" ; echo "sa" | ../checker "2 "1 22
echo "17.Expect OK         : \\c" ; echo "ra" | ../checker 1"2  " 3 4
echo "18.Expect OK         : \\c" ; echo "ra" | ../checker "   1"2 3 4
echo "19.Expect OK         : \\c" ; echo "sa" | ../checker 1"     "
echo "20.Expect OK         : \\c" ; echo "\c" | ../checker "      "1
echo "21.Expect OK         : \\c" ; echo "\c" | ../checker ""1
echo "22.Expect OK         : \\c" ; echo "\c" | ../checker 1""
