#include "Includes/Dino.h"

#include "../dinoServer/src/Includes/Server.h"

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <termio.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#include <string.h>

#include <signal.h>

pid_t parent_pid = 0;

static void enable_raw_mode_(FILE *file)
{

    int fd = fileno(file);
    struct termios tty;

    tcgetattr(fd, &tty);

    tty.c_lflag &= ~(ICANON | ECHO);

    tty.c_cc[VMIN] = 1;

    tty.c_cc[VTIME] = 0;

    tcsetattr(fd, TCSANOW, &tty);

    fcntl(fd, F_SETFL, O_NONBLOCK);
}

void disable_raw_mode_(FILE *file)
{
    int fd = fileno(file);
    struct termios tty;

    tcgetattr(fd, &tty);

    tty.c_lflag |= (ICANON | ECHO);
    tcsetattr(fd, TCSANOW, &tty);
}

bool start_dino(struct Setup *setup)
{
    printf("Hello!");
    if (!setup)
        return false;

    int fd[2] = {-1, -1};
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t p; 
    p = fork(); 


    if(p < 0) 
    { 
        perror("fork fail"); 
        exit(1); 
    }
    
    else if (p == 0)
    {
        struct Display  display = {
            .rows = setup->display_rows,
            .cols = setup->display_cols,
            .ground_height = setup->display_ground_height
        };

        struct Server server =
        {
            .display = &display,
            .in = setup->in_,
            .out = setup->server_out,
            .time_between_frame_ns = setup->time_between_frame_ns * 100000000L,
            .chance = setup->chance,
            .min_chance = setup->min_chance,
            .jump_height = setup->dino_jump_height
        };

        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        init_server(&server);
    
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[0]);

        enable_raw_mode_(setup->in_);
        
        while (1)
        {
            char buffer[] = " ";
            ssize_t size = fread(buffer, sizeof(char), 1, setup->in_);
            if (size && buffer[0] == 'q')
            {
                kill(p, SIGTERM);
                waitpid(p, 0, 0);
                break;
            }
            if (size > 0)
            {
                write(fd[1], buffer, 1);
            }
            
        }
        disable_raw_mode_(setup->in_);
        exit(EXIT_SUCCESS);

    }
    return true;
}