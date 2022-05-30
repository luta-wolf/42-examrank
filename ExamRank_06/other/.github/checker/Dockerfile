# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/18 11:02:19 by aldubar           #+#    #+#              #
#    Updated: 2022/01/16 19:24:03 by aldubar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM		ubuntu:latest

RUN			apt update && apt install -y clang make psmisc netcat

WORKDIR		/.github/checker

#ENTRYPOINT	[ "/bin/bash", "grademe.sh" ]
ENTRYPOINT	[ "clang", "-Wall", "-Wextra", "-Werror", "mini_serv.c" ]
