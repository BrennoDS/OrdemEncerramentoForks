# Ordem de encerramento de processos gerados por `fork()`


## Objetivo

O experimento busca verificar a seguinte hipótese:

> A ordem em que os processos filhos são criados influencia a ordem em que eles serão
executados e terminarão. Consequentemente, ao utilizar wait(), o processo pai tender a receber
os filhos na mesma ordem em que foram criados.

Para testar essa hipótese, foram realizados experimentos com diferentes condições de execução.

## Experimentos

Cada experimento cria **10 processos filhos** e registra:

* número do experimento;
* número do filho;
* PID do processo;
* ordem de criação;
* tempo de espera;
* ordem de término.

Foram realizadas três baterias de testes, cada uma com **150 experimentos**:

1. **Tempo variável + semente aleatória**
   Cada processo recebe um tempo de `sleep()` diferente, utilizando uma semente baseada no horário atual do computador.

2. **Tempo variável + semente fixa**
   Cada processo recebe um tempo de `sleep()` diferente utilizando uma semente fixa (`2580`), permitindo reproduzir a mesma sequência de valores aleatórios.

3. **Tempo semelhante, sem `sleep()`**
   Os processos executam operações semelhantes, sem um tempo de espera definido por `sleep()`.

## Funcionamento do código

O programa utiliza as seguintes funções:

* `fork()` — criação dos processos filhos;
* `wait()` — aguarda o término de qualquer processo filho;
* `rand()` — geração dos tempos aleatórios;
* `srand()` — define da semente utilizada pelo gerador aleatório;
* `sleep()` — define o tempo de espera dos processos;
* `getpid()` — obtém o PID do processo;
* `fopen()` / `fprintf()` — armazenamento dos resultados em arquivos CSV.

Os dados de cada processo são armazenados em uma `struct`. Após a criação dos 10 processos, o processo pai utiliza `wait()` para identificar qual filho terminou. O PID retornado pelo `wait()` é comparado com os PIDs armazenados na `struct`, permitindo determinar a ordem de término de cada processo.


## Clonagem do projeto

Clone o repositório:

```bash
git clone https://github.com/BrennoDS/OrdemEncerramentoForks
```

Entre na pasta:

```bash
cd OrdemEncerramentoForks
```

## Compilação

Compile o programa C com:

```bash
gcc main.c -o main
```
```bash
gcc mainFixo.c -o mainFixo
```
```bash
gcc mainNoSleep.c -o mainNoSleep
```

## Execução

O programa recebe o número do experimento como argumento:

```bash
./programa 1
```

Por exemplo:

```bash
./programa 1
./programa 2
./programa 3
```

## Executando os scripts Bash

Para executar a bateria de teste, o programa tem scripts bash para executa-los de forma automatica

Primeiro verifique se possuem permissão de execução:

```bash
chmod +x *.sh
```

Depois execute o script desejado:

```bash
./experimento.sh
```
```bash
./experimentoFixo.sh
```
```bash
./experimentoNoSleep.sh
```

## Resultados

Os resultados dos experimentos são armazenados em arquivos `.csv`, contendo as informações de cada processo e sua respectiva ordem de término.

No artigo utilizei uma tabela dinamica para analisar os dados retornados dos experimentos, mas o dados que saem direto dos experimentos estão sem nenhum tratamento

## Conclusão

Os experimentos demonstram que a ordem de criação dos processos por meio de `fork()` **não garante a mesma ordem de término**. A ordem de finalização depende das condições de execução dos processos e do escalonamento realizado pelo sistema operacional.

Mesmo quando os processos possuem tempos de execução semelhantes, podem ocorrer diferenças entre a ordem de criação e a ordem de término.
