#!/bin/bash

ARGS="Wrong number of arguments"
FATAL="Fatal error"
err=0
port=0
while [ $port -lt 1024 -o $port -gt 10000 ]; do
	port=$RANDOM
done
echo "Running tests on port $port..."

check()
{
[ $? -eq 1 ] && echo -e "✅\c" || { echo -e "❌\c"; err=$(( $err + 1 )); }
[ "$(cat log.txt)" = "$1" ] && echo -e "\033[70G✅" || { echo -e "\033[70G❌"; err=$(( $err + 1 )); }
}


check_diff()
{
INDENT=50

case "$1" in
	5 | 7)
		INDENT=55
		;;
esac

diff "log$1.txt" "assets/test$1" &> /dev/null
[ $? -eq 0 ] &&	echo -e "\033[${INDENT}G✅\c" || { echo -e "\033[${INDENT}G❌\c"; err=$(( $err + 1 )); }
}


### COMPIL
echo -e "\033[36m[+] Checking compilation...\033[0m\033[50G\c"
clang -Wall -Wextra -Werror mini_serv.c -o mini_serv &> log.txt
[ "$(cat log.txt)" = "" ] && echo "✅"|| { echo -e "\033[31mCompilation error...\033[0m"; cat log.txt; rm log.txt; exit 1; }


### HANDLE ERRORS
echo -e "\n\033[36m[+] Checking errors\033[0m\033[50GExit status\033[70GDiff Output"
echo -e "\033[33m[+] Checking no arguments output...\033[0m\033[50G\c"
./mini_serv &> log.txt
check "$ARGS"

echo -e "\033[33m[+] Checking two many arguments output...\033[0m\033[50G\c"
./mini_serv 1 2 &> log.txt
check "$ARGS"

echo -e "\033[33m[+] Checking syscall error output...\033[0m\033[50G\c"
./mini_serv "$port" & > log.txt
./mini_serv "$port" &> log.txt
check "$FATAL"
echo "[+] Killing mini_serv..."
killall -q mini_serv


### DIFF OUTPUT
echo -e "\n\033[36m[+] Checking output...\033[0m\033[50G"
echo -e "\033[33m[+] 1 client and 1 message...\033[0m\033[50G\c"
./mini_serv "$port" & > log1.txt
r=$(nc localhost "$port" > log1.txt) &
sleep 1
echo "coucou" | nc localhost "$port"
check_diff 1
echo -e "\n[+] Killing mini_serv..."
killall -q mini_serv


echo -e "\n\033[33m[+] 1 client and many messages...\033[0m\033[50G\c"
port=$(( $port - 5 ))
./mini_serv "$port" & > log2.txt
r=$(nc localhost "$port" > log2.txt) &
sleep 1
echo "coucou" | nc localhost "$port"
echo "good morning" | nc localhost "$port"
echo "holà que tal?" | nc localhost "$port"
echo -e "\033[32mGREEN\n\t\033[31mRED" | nc localhost "$port"
echo "" | nc localhost "$port"
echo -e "\033[0mhello\t\tbonjour" | nc localhost "$port"
echo "last one" | nc localhost "$port"
echo "✅" | nc localhost "$port"
check_diff 2
echo -e "\n[+] Killing mini_serv..."
killall -q mini_serv


echo -e "\n\033[33m[+] 1 client and multi lines...\033[0m\033[50G\c"
./mini_serv "$(( $port + 1 ))" & > log3.txt
r=$(nc localhost "$(( $port + 1 ))" > log3.txt) &
sleep 1
cat assets/lorem | nc localhost "$(( $port + 1 ))"
check_diff 3
echo -e "\n[+] Killing mini_serv..."
killall -q mini_serv


echo -e "\n\033[33m[+] 2 clients and a simple message...\033[0m\033[50G\c"
./mini_serv "$(( $port + 2 ))" & > log4.txt
r=$(nc localhost "$(( $port + 2 ))" > log4.txt) &
sleep 1
r2=$(nc localhost "$(( $port + 2 ))" > log5.txt) &
sleep 1
echo "hello" | nc localhost "$(( $port + 2 ))"
check_diff 4
check_diff 5
echo -e "\n[+] Killing mini_serv..."
killall -q mini_serv


echo -e "\n\033[33m[+] 2 clients and multi ligne message...\033[0m\033[50G\c"
./mini_serv "$(( $port - 1 ))" & > log6.txt
r=$(nc localhost "$(( $port - 1 ))" > log6.txt) &
sleep 1
r2=$(nc localhost "$(( $port - 1 ))" > log7.txt) &
sleep 1
cat assets/lorem | nc localhost "$(( $port - 1 ))"
check_diff 6
check_diff 7
echo -e "\n[+] Killing mini_serv..."
killall -q mini_serv



### SUMMARY
[ $err -eq 0 ] && echo -e "\n\033[32mAll tests passed :)\033[0m" || echo -e "\033[31m$err test(s) failed :(\033[0m"


### CLEAN

rm -rf mini_serv log*.txt

exit $err
