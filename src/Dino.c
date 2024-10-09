#include "Includes/Dino.h"

#include "../dinoBackend/src/Includes/Server.h"

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
    if (!setup)
        return false;

    int fd[2] = {-1, -1};
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t p; 
    p = fork(); 

    FILE *file_server_out = fdopen(setup->server_out, "w");
    FILE *file_in_ = fdopen(setup->in_, "r");

    if(p < 0) 
    { 
        perror("fork fail"); 
        exit(1); 
    }
    
    else if (p == 0)
    {
        close(fd[0]);

        enable_raw_mode_(file_in_);
        
        FILE *pipe_ = fdopen(fd[1], "w");

        while (1)
        {
            char buffer[] = " ";
            ssize_t size = fread(buffer, sizeof(char), 1, file_in_);
            if (size && buffer[0] == 'q')
            {
                kill(p, SIGTERM);
                waitpid(p, 0, 0);
                break;
            }
            
            if (size > 0)
            {
                fwrite(buffer, sizeof(char), 1, pipe_);
                fflush(pipe_);
            }
        }
        disable_raw_mode_(file_in_);
        exit(EXIT_SUCCESS);

    }
    else
    {
        enable_raw_mode_(file_in_);
        
        FILE *pipe_ = fdopen(fd[0], "r");
        enable_raw_mode_(pipe_);
        struct Display  display = {
            .rows = setup->display_rows,
            .cols = setup->display_cols,
            .ground_height = setup->display_ground_height
        };

        struct Server server =
        {
            .display = &display,
            .in = pipe_,
            .out = file_server_out,
            .time_between_frame_ns = setup->time_between_frame_ns * 100000000L,
            .chance = setup->chance,
            .min_chance = setup->min_chance,
            .jump_height = setup->dino_jump_height
        };


        close(fd[1]);
        
        init_server(&server);
        disable_raw_mode_(pipe_);
    
        exit(EXIT_SUCCESS);
    }
    return true;
}