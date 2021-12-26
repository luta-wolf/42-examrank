#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_cmd{
    char **args;
    int     pipe[2];
    int     type[2];
    int     prev_pipe;
}   t_cmd;

int ft_strlen(char *str)
{
    int i;
    i = 0;
    while (str[i])
        i++;
    return(i);
}

int len_list(t_cmd *list, int start, char **argv)
{
    int end;
    int len;
    
    end = start;
    while(argv[end] && strcmp(argv[end], "|") && strcmp(argv[end], ";"))
        end++;
    len = end - start;
    if (len > 0)
    {
        list->args = &argv[start];
        list->type[0] = list->type[1];
        if (argv[end] && !strcmp(argv[end], "|"))
            list->type[1] = 1;
        else if (argv[end] && !strcmp(argv[end], ";"))
            list->type[1] = 2;
        else
            list->type[1] = 0;
        argv[end] = NULL;
        list->prev_pipe= list->pipe[0];
    }
    return (end);
}

void    fatal(void)
{
    write(2, "error: fatal\n", ft_strlen("error: fatal\n"));
    exit (24);
}

void    exec_cmd(t_cmd *list, char **envm)
{
    pid_t pid;
    int ex;
    
    if ((list->type[1] == 1 || list->type[0] == 1) && pipe(list->pipe))
        fatal();
    if ((pid = fork()) < 0)
        fatal();
    if (pid == 0)
    {
        if (list->type[1] == 1 && dup2(list->pipe[1], 1) < 0)
             fatal();
        if (list->type[0] == 1 && dup2(list->prev_pipe, 0) < 0)
             fatal();
        if ((ex = execve(list->args[0], list->args, envm)) < 0)
        {
            write(2, "error: cannot execute ", ft_strlen("error: cannot execute "));
             write(2, list->args[0], ft_strlen(list->args[0]));
            write(2, "\n", 1);
        }
        exit(ex);
    }
    else
    {
        waitpid(pid, 0, 0 );
        if (list->type[0] == 1 || list->type[1] == 1)
        {
            close(list->pipe[1]);
            if (list->type[1] != 1)
                close(list->pipe[0]);
        }
        if (list->type[0] == 1)
            close(list->prev_pipe);
    }
}

int main (int argc, char **argv, char **envm)
{
    int i;
    int start;
    t_cmd list;

    i = 1;
    while(i < argc)
    {
        start = i;
        i = len_list(&list, start, argv);
        if (!strcmp(argv[start], "cd"))
        {
            if (i - start != 2)
                write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
            else if(chdir(argv[start+1]) == -1)
            {
                write(2, "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
                write(2, argv[start+1], ft_strlen(argv[start+1]));
                write(2, "\n", 1);
            }
        }
        else if (i > start)
            exec_cmd(&list, envm);
        i++;
      
    }
    return (0);;
}
