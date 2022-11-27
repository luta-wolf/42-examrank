Запускаем программу
```
clang -Wall -Wextra -Werror mini_serv.c -o mini_serv && ./mini_serv 8080	# First terminal (server)
```
Открывает два дополнительных терминала
```
nc localhost 8080		# Second terminal (first client)
nc localhost 8080		# Third terminal (second client)
```
