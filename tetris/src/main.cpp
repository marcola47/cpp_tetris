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
| Movimenta��o:                                      |
| - SETA PARA BAIXO = Mover para baixo               |
| - SETA PARA DIREITA = Mover para direita           |
| - SETA PARA ESQUERDA = mover para esquerda         |
|----------------------------------------------------|
| Funcionalidades:                                   |
| - ESPA�O = Arreme�a a pe�a para o fim do tabuleiro |
| - ENTER = Inicia o jogo                            |
| - ESC = Pausa o jogo (Tamb�m tem o icone na tela)  |
| - Z = Segura uma pe�a a pe�a                       |
| - X = Rotacionar                                   |
|--------------------------------------------------**/

/*** Quesitos implementados ***/
/**-------------------------------------------------------------------------------------------------|
| Requisitos m�nimos:                                                                               |
| - Desenhar o cen�rio do jogo                                                                      |
| - Usando teclado/mouse, o usu�rio pode mover e girar a pe�a                                       |
| - Contador de pontos                                                                              |
| - Remo��o das linhas completas                                                                    |
| - Pe�as acima de uma linha removida s�o abaixadas um n�vel                                        |
| - Menu principal do jogo                                                                          |
|---------------------------------------------------------------------------------------------------|
| B�nus:                                                                                            |
| - Anima��o das pe�as caindo/explodindo (fileiras completas)                                       |
| - Ajuste de velocidade que a pe�a cai (aumentando conforme o jogo avan�a)                         |
| - Tamanho de tela vari�vel e responsivo                                                           |
| - Game over e reset                                                                               |
| - Mostrar qual ser� a pr�xima pe�a no canto da tela                                               |
| - Proje��o da pe�a sobre as demais, possibilitando enxergar onde a pe�a cair�                     |
| - Fun��o hold                                                                                     |
| --------------------------------------------------------------------------------------------------|
| B�nus al�m dos b�nus:                                                                             |
| - Menu e fun��o de pause                                                                          |
| - Pe�a cai automaticamente no fim do tabuleiro ao apertar espa�o                                  |
| - Cor das bordas do tabuleiro ou da UI refletem a cor da respectiva pe�a                          |
| - Logo para o jogo com pixels de cores aleatorias que troca a cada tick do timer                  |
| - Gerador aleat�rio de pe�as sofisticado (leva um hist�rio de pe�as em considera��o)              |
| - Contador de linhas preenchidas                                                                  |
| - Fun��o para o canvas2D que gera um rect() com espessura acima de 1px                            |
| - Bitmaps customizados para os bot�es e textos principais                                         |
| - A pe�a ativa mostra graficamente a distancia entre ela e a ultima linha disponivel do tabuleiro |
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
/*** Fun��o dos Controles ***/
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
/*** Fun��es de Mouse ***/
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
  printf("mouse %d %d %d %d %d %d\n", button, state, wheel, direction,  x, y);
  mouseBtnClicked = button;
  mouseBtnState = state;
  mx = x;
  my = y;

  /*** Fun��es dos bot�es ***/
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
/*** Fun��es de Teclado ***/
void keyboard(int key)
{
  printf("key down: %d\n", key);

  /** Inicia o jogo **/
  if (key == 13 && (game.mode == 2 || game.mode == 3))
    startGame(); //S� � v�lido se o modo de jogo for game over ou menu inicial

  /** Pausar o jogo **/
  else if (key == 27 && (game.mode == 1 || game.mode == 0))
    pauseGame(); //S� � v�lido se o modo de jogo for pausado ou normal

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

      /** Arreme�ar **/
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
