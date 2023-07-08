#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <chrono>

#include "gl_canvas2d.h"
#include "gl_variables.h"

#include "bitmaps.h"
#include "gameLogic.h"
#include "movementFunctions.h"
#include "renderFunctions.h"

/********************************************************************************************************************************************************************************************/
/*** Controles ***/
/**--------------------------------------------------|
| Movimentação:                                      |
| - SETA PARA BAIXO = Mover para baixo               |
| - SETA PARA DIREITA = Mover para direita           |
| - SETA PARA ESQUERDA = mover para esquerda         |
|----------------------------------------------------|
| Funcionalidades:                                   |
| - ESPAÇO = Arremeça a peça para o fim do tabuleiro |
| - ENTER = Inicia o jogo                            |
| - ESC = Pausa o jogo (Também tem o icone na tela)  |
| - Z = Segura uma peça a peça                       |
| - X = Rotacionar                                   |
|--------------------------------------------------**/

/*** Quesitos implementados ***/
/**-------------------------------------------------------------------------------------------------|
| Requisitos mínimos:                                                                               |
| - Desenhar o cenário do jogo                                                                      |
| - Usando teclado/mouse, o usuário pode mover e girar a peça                                       |
| - Contador de pontos                                                                              |
| - Remoção das linhas completas                                                                    |
| - Peças acima de uma linha removida são abaixadas um nível                                        |
| - Menu principal do jogo                                                                          |
|---------------------------------------------------------------------------------------------------|
| Bônus:                                                                                            |
| - Animação das peças caindo/explodindo (fileiras completas)                                       |
| - Ajuste de velocidade que a peça cai (aumentando conforme o jogo avança)                         |
| - Tamanho de tela variável e responsivo                                                           |
| - Game over e reset                                                                               |
| - Mostrar qual será a próxima peça no canto da tela                                               |
| - Projeção da peça sobre as demais, possibilitando enxergar onde a peça cairá                     |
| - Função hold                                                                                     |
| --------------------------------------------------------------------------------------------------|
| Bônus além dos bônus:                                                                             |
| - Menu e função de pause                                                                          |
| - Peça cai automaticamente no fim do tabuleiro ao apertar espaço                                  |
| - Cor das bordas do tabuleiro ou da UI refletem a cor da respectiva peça                          |
| - Logo para o jogo com pixels de cores aleatorias que troca a cada tick do timer                  |
| - Gerador aleatório de peças sofisticado (leva um histório de peças em consideração)              |
| - Contador de linhas preenchidas                                                                  |
| - Função para o canvas2D que gera um rect() com espessura acima de 1px                            |
| - Bitmaps customizados para os botões e textos principais                                         |
| - A peça ativa mostra graficamente a distancia entre ela e a ultima linha disponivel do tabuleiro |
|-------------------------------------------------------------------------------------------------**/

/********************************************************************************************************************************************************************************************/
/*** Render ***/
void render()
{
  //Aplica pra todos os modos
  CV::clear(0, 0, 0);
  updatePos();

  switch(game.mode)
  {
    case 0:
      renderLogo(6.25);
      renderGameElements();
      renderPauseMenu();
      renderBtnMIP(1.7);
      break;

    case 1:
      renderLogo(6.25);
      renderGameElements();
      renderPauseMenu();
      sequenceGame();
      updateScore();
      break;

    case 2:
      renderLogo(6.25);
      renderBtnJogar(3);
      renderBtnSair(3);
      break;

    case 3:
      renderGameOver(4.2);
      renderBtnJN(1.8);
      renderBtnMIGO(1.8);
      break;
  }
}

/********************************************************************************************************************************************************************************************/
/*** Função dos Controles ***/
/** Iniciar o jogo **/
void startGame()
{
  for (int i = 0; i < 10000; i++)
  {
    tetroNext.type = getRandom();
    if (tetroNext.type != tetroActive.type)
      break;
  }

  moveCounterStart = std::chrono::high_resolution_clock::now();
  tetroActive.posY = resetPosY(tetroActive.posY);
  tetroHold.type = -1;

  game.mode = 1;
  game.isPaused = 0;
  game.points = 0;
  game.clearedLines = 0;

  resetField();
  getFieldBorder();
  getTetroActive();
  getTetroProjection();
  getTetroNext();
}

/** Pausar jogo **/
void pauseGame()
{
  if (game.isPaused == 0)
  {
    game.mode = 0;
    game.isPaused = 1;
  }

  else if (game.isPaused == 1)
  {
    game.mode = 1;
    game.isPaused = 0;
  }
}

/********************************************************************************************************************************************************************************************/
/*** Funções de Mouse ***/
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
  printf("mouse %d %d %d %d %d %d\n", button, state, wheel, direction,  x, y);
  mouseBtnClicked = button;
  mouseBtnState = state;
  mx = x;
  my = y;

  /*** Funções dos botões ***/
  /** Iniciar jogo **/
  if (checkRenderPosition(jogar.initX - 20, jogar.initY - 10, jogar.endX + jogar.initX + 10, jogar.endY + 10) == 1 && mouseBtnClicked == 0 && mouseBtnState == 0 && game.mode == 2)
    startGame();

  /** Sair do jogo **/
  if (checkRenderPosition(sair.initX - 20, sair.initY - 10, sair.endX + sair.initX + 10, sair.endY + 10) == 1 && mouseBtnClicked == 0 && mouseBtnState == 0 && game.mode == 2)
    exit(0);

  /** Pause **/
  else if (checkRenderPosition(pause.initX, pause.endY, pause.endX, pause.initY) == 1 && mouseBtnClicked == 0 && mouseBtnState == 0 && (game.mode == 1 || game.mode == 0))
    pauseGame();

  /** Menu Inicial dentro do pause **/
  else if (checkRenderPosition(miP.initX - 20, miP.initY - 10, miP.endX + miP.initX + 10, miP.endY + 10) == 1 && mouseBtnClicked == 0 && mouseBtnState == 0 && game.isPaused == 1)
    game.mode = 2;

  /** Jogar Novamente **/
  else if (checkRenderPosition(jn.initX - 20, jn.initY - 10, jn.endX + jn.initX + 10, jn.endY + 10) == 1 && mouseBtnClicked == 0 && mouseBtnState == 0 && game.mode == 3)
    startGame();

  /** Menu inicial dentro do game over **/
  else if (checkRenderPosition(miGO.initX - 20, miGO.initY - 10, miGO.endX + miGO.initX + 10, miGO.endY + 10) == 1 && mouseBtnClicked == 0 && mouseBtnState == 0 && game.mode == 3)
    game.mode = 2;
}

/********************************************************************************************************************************************************************************************/
/*** Funções de Teclado ***/
void keyboard(int key)
{
  printf("key down: %d\n", key);

  /** Inicia o jogo **/
  if (key == 13 && (game.mode == 2 || game.mode == 3))
    startGame(); //Só é válido se o modo de jogo for game over ou menu inicial

  /** Pausar o jogo **/
  else if (key == 27 && (game.mode == 1 || game.mode == 0))
    pauseGame(); //Só é válido se o modo de jogo for pausado ou normal

  else if (game.mode == 1)
  {
    switch(key)
    {
      /** Mover Esquerda **/ //Seta pra esquerda
      case 200: tetroActive.posX = moveTetroX(tetroActive.posX, -1); break;

      /** Mover Direita **///Seta pra direita
      case 202: tetroActive.posX = moveTetroX(tetroActive.posX, 1); break;

      /** Mover Baixo **/ //Seta pra baixo
      case 203: tetroActive.posY = moveTetroY(tetroActive.posY); break;

      /** Arremeçar **/
      case 32: forceTetroY(); break;

      /** Segurar um Tetromino **/
      case 'z': swapTetros(); break;
      case 'Z': swapTetros(); break;

      /** Rotacionar **/
      case 'x': rotate(); break;
      case 'X': rotate(); break;
    }
  }
}

void keyboardUp(int key)
{
  printf("key up: %d\n", key);
}

/********************************************************************************************************************************************************************************************/
int main(void)
{
  srand(GetTickCount());
  tetroActive.type = getRandom();
  getUIComponents();
  fillStructs();

  CV::init(&screenWidth, &screenHeight, "TETRIS - Marcos Eduardo - SI/LA - 2022.01");
  CV::run();
}
