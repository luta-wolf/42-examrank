Запускаем программу
```
clang -Wall -Wextra -Werror mini_serv.c -o mini_serv && ./mini_serv 8080	# First terminal (server)
```
Открывает два дополнительных терминала
```
nc localhost 8080		# Second terminal (first client)
nc localhost 8080		# Third terminal (second client)
```
<img width="1070" alt="image" src="https://user-images.githubusercontent.com/58044383/204136683-34119db9-c4ec-446e-b1b8-73ac2ea7c2d5.png">
