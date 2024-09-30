#include "Includes/Dino.h"

#include "../dinoServer/src/Includes/Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <bits/waitflags.h>
#include <sys/wait.h>
#include <asm-generic/signal-defs.h>

bool start_dino(struct Setup *setup)
{
    if (!setup)
        return false;

    pid_t cpid = 0;
    pid_t w = 0;
    int status;
    pid_t p; 
    p = fork(); 
    if(p<0) 
    { 
      perror("fork fail"); 
      exit(1); 
    } 
  
    // parent process because return value non-zero. 
    else if ( p == 0) 
    {

        waitpid(cpid, &status, WUNTRACED);
        struct Display  display = {
            .rows = setup->display_rows,
            .cols = setup->display_cols,
            .ground_height = setup->display_ground_height
        };

        struct Server server =
        {
            .display = &display,
            .in = setup->server_in,
            .out = setup->server_out,
            .time_between_frame_ns = setup->time_between_frame_ns,
            .chance = setup->chance,
            .min_chance = setup->min_chance,
            .jump_height = setup->dino_jump_height
        };

        struct sigaction sa;
    sa.sa_handler = SIG_IGN; // Set handler to ignore signal
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

        init_server(&server);

    }
    else
    {
        printf("Heuuuueedsfezfze\n");
        w = waitpid(cpid, &status, WUNTRACED);
        printf("Heuuuueedsfezfze\n");
        if (w == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        int pid = getpid();
        char buffer[] = " ";
        ssize_t size = 0;
        
        while (1)
        {
            size = fread(buffer, sizeof(char), 1, setup->in);
            if (size && buffer[0] == 'q')
            {
                kill(pid, SIGTERM);
                break;
            }
            fwrite(buffer, sizeof(char), 1, setup->server_in);
        }
        printf("Ha mé\n");
        exit(EXIT_SUCCESS);

    }

    return true;
}