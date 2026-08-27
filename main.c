#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
    
    int i, pid;
    pid_t pids[10];
    srand(time(NULL)); //Pai
    int sleep_time = 1 + (rand() % 20);
    printf("Ordem Criação\n");
    for(i=0; i<10; i++){
        
        pids[i] = fork();
        
         //Filho
        if(pids[i] > 0){
            printf("%d: PID: %d\n", i, pids[i]);
            // printf("Processo pai %d criou o filho %d\n",getpid(),pids[i]);
        }else if(pids[i] == 0){
            srand(time(NULL)+getpid());
            int sleep_time = 1 + (rand() % 20);
            sleep(sleep_time);
            // printf("Processo filho %d, tempo: %d terminou\n",getpid(), sleep_time);
            exit(0);
        }else{
            perror("fork");
            exit(1);
        }
    }

    // int filhos = 10;
    // while(filhos > 0){
    //     int status;
    //     for(i=0; i<10; i++){
    //         if(pids[i] != 0){
    //             int status;
    //             pid_t res = waitpid(pids[i], &status , WNOHANG);
    //             if(res == pids[i]){
    //                 printf("Processo filho %d terminou\n",res);
    //                 pids[i] = 0;
    //                 fi  lhos--;
    //             }
    //         }
    //     }
    //     usleep(100000);
    // }

    printf("Ordem Termino\n");
    for(int i=0; i<10; i++){
        int status;
        pid_t res = wait(&status);
        printf("%d: PID %d\n", i, res);
    }

    return 0;
}

