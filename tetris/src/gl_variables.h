/***** Header que contém todas as variáveis principais utilizadas no jogo e funções para atualização e responsividade *****/

/** Defs do Jogo **/
#define FL 27 //Linhas no tabuleiro
#define FC 15 //Colunas no tabuleiro
#define SS 5 //Shape Size
#define ST 7 //Shapes Total
#define HS 3 //History Size

/** Defs dos BitMaps **/
#define CT 16 //Chars Total
#define CL 10 //Char Lines
#define CC 9  //Char Columns

int screenWidth = 460, screenHeight = 700;
int mx, my, mouseBtnClicked, mouseBtnState;

/** Variáveis gerais do jogo **/
struct game
{
  int renderState;
  int mode; //0 = Pausado | 1 = Tetris | 2 = Menu | 3 = Game Over
  int state;
  int swapped; //Detecta se o usuário ja usou o a função hold naquele round
  int isPaused;

  int initX; //Inicio frame do jogo
  int initY; //Inicio do frame do jogo
  int endX;  //Fim do frame do jogo (usado pra calcular a posição da borda)
  int endY;  //Fim do frame do jogo (usado pra calcular a posição da borda)

  int borderThick; //Espessura da borda dos outros renders
  int cellSize; //Tamanho de cada celula (recomendo deixar em 20 msm)
  int fullWidth;

  int pointsInitX; //Inicio do frame dos pontos
  int pointsInitY;
  int pointsEndX;
  int pointsEndY;
  int points;
  int pointsMultiplier;

  int linesInitX; //Inicio do frame das linhas
  int linesInitY;
  int linesEndX;
  int linesEndY;
  int clearedLines; //Total de linhas removidas durante o jogo
  int fullLines[FL]; //Array que armazena o total de linhas preenchidas no fim de cada round

  float colors[3];
  int field[FL][FC]; //Matriz geral do tabuleiro
}; struct game game = {1, 2, 0, 0, 0, 10000, 95, 0, 0, 4, 20, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0};

/** Variáveis da UI **/
struct ui
{
  /** Textos **/
  int logo[6][CL][CC];
  int go[9][CL][CC];

  /** Botoes **/
  int jogar[5][CL][CC];
  int sair[4][CL][CC];
  int jn[15][CL][CC];
  int mi[12][CL][CC];
  int pause[CL][CC];
}; struct ui ui;


typedef struct
{
  float fontSize;
  int fullCharSize;
  int initX, initY;
  int endX, endY;
} uiPos;

//Menu Inicial
uiPos logo; uiPos *logo_ptr = &logo;
uiPos jogar; uiPos *jogar_ptr = &jogar;
uiPos sair; uiPos *sair_ptr = &sair;

//Game Over
uiPos go; uiPos *go_ptr = &go;
uiPos jn; uiPos *jn_ptr = &jn;
uiPos miGO; uiPos *miGO_ptr = &miGO;

//Menu de Pause
uiPos pause;
uiPos miP; uiPos *miP_ptr = &miP;


/** Tetrominoes **/
struct tetroActive
{
  int posX;
  int posY;
  int projPosY;
  int type; //Tipo de peça, O, I, Z, S...
  int typeHistory[HS]; //Historico de peças, usei isso pra não repetirem muitas peças
  int tetro[SS][SS];
  int projection[SS][SS]; //Projeção de onde a peça vai encaixar na rotação e posX atual
}; struct tetroActive tetroActive = {5, 2, 2};

typedef struct
{
  int initX;
  int initY;
  int endX;
  int endY;
  int type;
  int tetro[SS][SS];
} tetroAux;
  tetroAux tetroNext = {10000}; tetroAux *next_ptr = &tetroNext;
  tetroAux tetroHold = {10000}; tetroAux *hold_ptr = &tetroHold;

int tetros[ST][SS][SS]
{
 {{0,0,0,0,0},
  {0,1,1,0,0},
  {0,1,1,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}},

 {{0,0,0,0,0},
  {0,0,0,0,0},
  {2,2,2,2,0},
  {0,0,0,0,0},
  {0,0,0,0,0}},

 {{0,0,0,0,0},
  {0,3,3,0,0},
  {0,0,3,3,0},
  {0,0,0,0,0},
  {0,0,0,0,0}},

 {{0,0,0,0,0},
  {0,0,4,4,0},
  {0,4,4,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}},

 {{0,0,0,0,0},
  {0,5,0,0,0},
  {0,5,5,5,0},
  {0,0,0,0,0},
  {0,0,0,0,0}},

 {{0,0,0,0,0},
  {0,0,0,6,0},
  {0,6,6,6,0},
  {0,0,0,0,0},
  {0,0,0,0,0}},

 {{0,0,0,0,0},
  {0,0,7,0,0},
  {0,7,7,7,0},
  {0,0,0,0,0},
  {0,0,0,0,0}},
};

/** Infos de timing **/
auto moveCounterStart = std::chrono::high_resolution_clock::now();
auto moveCounterEnd = std::chrono::high_resolution_clock::now();
float delay, threshold = 1;

/********************************************************************************************************************************************************************************************/
/*** Prototipando para os verificadores ***/
int getProjectionY(int posY);
int resetPosY(int posY);
void moveTetroAuto();
int getRandom();

/********************************************************************************************************************************************************************************************/
/*** Funções que inicializam e atualizam os valores das posições ***/
/** Inicializa os valores que não precisam ser atualizados **/
void fillStructs() //Podia fazer uma função e passar as structs por referência, mas, seria tipo usar um tanque de guerra pra matar uma mosca.
{
  /*** Jogo ***/
  /** game **/
  game.fullWidth = game.cellSize*FC + game.cellSize*7;

  game.pointsInitY = game.initY + 9;
  game.pointsEndY = game.pointsInitY + 35;

  game.linesInitY = game.pointsEndY + game.cellSize*2;
  game.linesEndY = game.linesInitY + 35;

  /** tetroActive **/
  for (int i = 0; i < HS; i++) {tetroActive.typeHistory[i] = -1;}
  tetroActive.posX = (FC - 4) / 2;

  /** tetroHold **/
  tetroHold.type = -1;

  /** tetroNext **/
  tetroNext.initY =  tetroHold.initY + 5*game.cellSize;

  /***************************************************/
  /*** UI ***/
  /** logo **/
  logo.initY = 20;

  /** gameOver **/
  go.initY = 20;

  /** pause **/
  pause.fontSize = 4;
  pause.initX = 14;
  pause.initY = screenHeight - 20;
  pause.endX = pause.fontSize * CC + pause.initX;
  pause.endY = pause.initY - pause.fontSize * CL;

  miP.initX = pause.endX + 20;
}

/** Deixa os botoes da UI responsivos **/
void getResponsiveBtn(uiPos* ptr, uiPos* prev_ptr, int stringSize)
{
  ptr->endX = ptr->fullCharSize*stringSize;
  ptr->initX = ((screenWidth - ptr->endX) / 2) + ptr->fontSize*3 / 2;
  ptr->initY = prev_ptr->endY + 120; //Não sei pq esse tem q ficar aqui, mas tem q ser constantemente chamado
  ptr->endY = ptr->initY + ptr->fontSize*(CL+7);
}

/** Deixa os headers da UI responsivos **/
void getResponsiveHeader(uiPos* ptr, int stringSize)
{
  ptr->endX = ptr->fullCharSize*stringSize;
  ptr->initX = ((screenWidth - ptr->endX) / 2) + ptr->fontSize*3 / 2;
  ptr->endY = ptr->initY + ptr->fontSize*(CL+7);
}

/** Atualiza constantemente as posições **/
void updatePos()
{
  /*******************************************************************************************************/
  /*** Jogo ***/
  /** game **/
  game.initX = (screenWidth - game.fullWidth) / 2 - 5; // -5 pra margem ficar 100% certinha
  game.endX = game.initX + game.fullWidth; //Pega o tamanho total do tabuleiro

  game.pointsInitX = game.initX + game.cellSize * FC;
  game.pointsEndX = game.endX;

  game.linesInitX = game.initX + game.cellSize * FC;
  game.linesEndX = game.endX;

  /** tetroActive **/
  if (game.mode == 1) //Se nao fizer essa condição, no primeiro round a projeção nao aparece
    tetroActive.projPosY = getProjectionY(tetroActive.projPosY);

  /** tetroHold **/
  tetroHold.initX = game.initX + game.cellSize * FC;
  tetroHold.initY = game.linesEndY + game.cellSize*2;

  /** tetroNext **/
  tetroNext.initX = game.initX + game.cellSize * FC;
  tetroNext.initY = tetroHold.endY + game.cellSize*2;

  /*******************************************************************************************************/
  /*** UI ***/
  /** Menu Inicial **/
  getResponsiveHeader(logo_ptr, 6);
  getResponsiveBtn(jogar_ptr, logo_ptr, 5);
  getResponsiveBtn(sair_ptr, jogar_ptr, 4);

  /** Game Over **/
  getResponsiveHeader(go_ptr, 9);
  getResponsiveBtn(jn_ptr, go_ptr, 15);
  getResponsiveBtn(miGO_ptr, jn_ptr, 12);

  /** Menu de Pause **/
  pause.initY = screenHeight - 20;
  pause.endY = pause.initY - pause.fontSize * CL;

  miP.endX = miP.fullCharSize*12;
  miP.initY = pause.endY + 10;
  miP.endY = miP.initY + miP.fontSize*(CL+7);
}

