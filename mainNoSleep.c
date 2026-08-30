#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


typedef struct {
    int experimento;
    int filho;
    pid_t pid;
    int ordem_criacao;
    int tempo;
    int ordem_termino;
} Filho;

int main(int argc, char *argv[])
{

    int experimento = atoi(argv[1]);
    Filho filhos[10];
    pid_t pids[10];

    printf("Experimento: %d\n", experimento);
    printf("Ordem Criação\n");
    for(int i=0; i<10; i++){
        pids[i] = fork();
        
         //Filho
        if(pids[i] > 0){
            printf("%d: PID: %d\n ", i+1, pids[i]);
            // printf("Processo pai %d criou o filho %d\n",getpid(),pids[i]);
            filhos[i].experimento = experimento;
            filhos[i].filho = i+1;
            filhos[i].pid = pids[i];
            filhos[i].ordem_criacao = i+1;
            filhos[i].tempo = 0;

        }else if(pids[i] == 0){
            printf("Processo filho %d, PID: %d terminou\n",i+1, getpid());
            // printf("Processo filho %d, tempo: %d terminou\n",getpid(), sleep_time);
            exit(0);
        }else{
            perror("fork");
            // fclose(arquivo);
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



    int ordem_termino = 0;
    printf("Ordem Termino\n");
    for(int i=0; i<10; i++){
        int status;
        pid_t res = wait(&status);
        ordem_termino++;
        for(int j=0; j<10; j++){
            if(filhos[j].pid == res){
                filhos[j].ordem_termino = ordem_termino;
                printf("%d: Filho: %d,  PID: %d\n", filhos[j].ordem_termino, filhos[j].filho, res);
                break;
            }
        }
    }

    FILE *arquivo = fopen("resultados_NoSleep.csv", "a+");

        if(arquivo == NULL){
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fseek(arquivo, 0, SEEK_END);

        if(ftell(arquivo) == 0){
        fprintf(arquivo, "experimento,filho, pid, ordem criação, tempo, ordem termino\n");
    }

    for(int i=0; i<10; i++){
        fprintf(arquivo, 
            "%d,%d,%d,%d,%d,%d\n", 
            filhos[i].experimento, 
            filhos[i].filho, 
            filhos[i].pid, 
            filhos[i].ordem_criacao, 
            filhos[i].tempo, 
            filhos[i].ordem_termino);
    }
    fclose(arquivo);

    return 0;
}

