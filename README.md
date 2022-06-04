# Curvas Bspline
O OpenGL consiste em um conjunto de rotinas gráficas gratuitas. Pensando nisso foi feito um algoritimo em C/C++ de para desenhar Curvas B-Spline em formato 2D conforme pontos de controle inseridos pelo usuário, utilizando openGL.

## Requsitos
É necessário ter o openGL instalado corretamente em seu computador, além disso é preciso ter o compilador de C/C++ intalado também.

### Execução
Basta compilar os arquivos contidos neste repositório e executá-los.

### Funcionalidades
1) Desenha Curvas B-Spline em formato 2D conforme pontos de controle inseridos pelo usuário.
2) Permite o desenho de 1 até 5 curvas distintas simultaneamente na tela, sendo que cada curva deverá ter uma cor diferente para facilitar a visualização.
3) Permite a inserção de pontos de controle via digitação para cada curva desejada. 
4) Permite a inserção de pontos de controle via cliques de mouse cada curva desejada. 
5) Suporta no mínimo a faixa de 3 a 9 pontos de controle por curva, conforme escolha do usuário.
6) Possui um sistema de referência na tela de visualização, com escala indicativa das distâncias, com as seguintes características:
    - Ponto central de coordenadas no centro da tela de visualização.
    - Eixo de coordenadas x (linha contínua)
    - Eixo de coordenadas y (linha contínua)
    - Ambos eixos x e y tem 10 segmentos positivos e 10 segmentos negativos, e possuem pequenas marcações (um pequeno tracinho) para sinalizar cada divisão.
8) Permite o desenho e redesenho de curvas sem sair do programa. 
9) Valida as coordenadas de entrada conforme segue:
    - As coordenadas devem estar dentro dos limites do sistema de coordenadas do universo (da tela);
    - Não permitir a entrada de pontos repetidos (iguais);
