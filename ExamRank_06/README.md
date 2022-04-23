![checker](https://github.com/busshi/exam_rank06/actions/workflows/checker.yml/badge.svg)

# MINI_SERV
## EXAM RANK_06
[![aldubar's 42 Exam Rank 06 Score](https://badge42.vercel.app/api/v2/cl1p4dvqu002109k1x3fvx39n/project/2464142)](https://github.com/JaeSeoKim/badge42)

Train yourself to the exam_rank06 and test your own code:
- mini_serv.c

The goal of this evaluation is to write a program that will listen for clients to connect on a certain port on localhost (127.0.0.1) and will let clients to speak with each other...

```
clang -Wall -Wextra -Werror mini_serv.c -o mini_serv && ./mini_serv 8080	# First terminal (server)

nc localhost 8080		# Second terminal (first client)
nc localhost 8080		# Third terminal (second client)
```

```
/bin/bash grademe.sh		# Run a few tests on your mini_serv
```


### Note:
- Sometimes, the tester is not working as expected due to binding problems, so just re running the script should fix this issue.
Do more tests manually on your own to be sure ;)
- Works only on macos (bug with echo | nc in Linux)
