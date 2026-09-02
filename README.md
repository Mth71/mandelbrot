# Mandelbrot

Programa em C que gera o conjunto de Mandelbrot em quatro versões,s erial, OpenMP e duas estratégias de Pthreads, medindo o tempo de execução de cada uma.

## Sistema operacional

Testado em Ubuntu (WSL2). Requer `gcc` com suporte a Pthreads e OpenMP.

## Compilar

```bash
make
```

## Executar

```bash
./mandelbrot <largura> <altura> <max_iteracoes> <num_threads>
```

Exemplo:
```bash
./mandelbrot 1000 1000 500 4
```

## Limpar

```bash
make clean
```

## Arquivos gerados

- `mandelbrot_mcr_serial.pgm`
- `mandelbrot_mcr_openmp.pgm`
- `mandelbrot_mcr_pthreads1.pgm`
- `mandelbrot_mcr_pthreads2.pgm`
- `times.txt` — tempo de execução de cada implementação

Cada `.pgm` contém só os valores de intensidade (0–255) de cada pixel, sem cabeçalho de imagem,um valor por pixel, separado por espaço, uma linha por linha da imagem.

## Estrutura

| Arquivo | Responsabilidade |
|---|---|
| `mandelbrot.c` | Núcleo matemático (cálculo de iterações e intensidade) |
| `serial.c` | Cálculo sequencial |
| `openmp.c` | Cálculo paralelo com OpenMP |
| `pthreads1.c` | Cálculo paralelo com Pthreads (blocos de linhas) |
| `pthreads2.c` | Cálculo serial + escrita paralela da matriz com Pthreads |
| `matriz_saida.c` | Escrita do arquivo de saída |
| `args.c` | Validação dos argumentos de linha de comando |
| `timer.c` | Cronômetro de alta precisão |
| `main.c` | Orquestra as 4 execuções e gera `times.txt` |

## Tratamento de erros

Valida número de argumentos, valores inválidos, falha de alocação de memória, falha ao criar arquivos e falha ao criar threads. Mensagens de erro vão para `stderr`; o programa não imprime nada em `stdout` durante a execução normal.
