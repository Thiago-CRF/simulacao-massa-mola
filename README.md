Simulação simples de um sistema massa-mola feita em C usando a biblioteca externa 'Raylib'

Variáveis da simulação estão no começo do código, nos #define e nas variáveis globais. Pode-se mexer a massa ao clicar com o mouse também.

Pretendo fazer um criador de gráfico para criar um gráfico do movimento da massa, e melhorar as váriaveis da simulaçao.

Precisa-se instalar a biblioteca no computador 'https://github.com/raysan5/raylib/wiki'  
Para compilar, precisa usar as flags da biblioteca raylib. 

- Por exemplo, o comando gcc que usava para compilar e rodar era:
- gcc -Wall -Wextra -g3 -std=c2x -lm spring.c -o output/spring -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./output/spring

Um makefile com as flags da biblioteca (-lraylib -lGL -lm -lpthread -ldl -lrt -lX11) é mais prático para compilar o programa.
