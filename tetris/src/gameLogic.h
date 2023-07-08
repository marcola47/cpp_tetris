/***** Header que contém as funções essenciais para o funcionamento lógico do jogo *****/

/*** Funções gerais ***/
/** Verifica se o mouse está em cima de algum botão **/
int checkRenderPosition(int initX, int initY, int endX, int endY)
{
  if (mx > initX && my > initY && mx < endX && my < endY)
    return 1;

  else
    return 0;
}

/** Verifica se acabou o jogo **/
int gameIsOver()
{
  for (int c = 0; c < SS; c++)
    if (game.field[3][c + 5] != 0) //5 é a posicão X inicial em todo novo round
      return 1;

  return 0;
}

/** Retorna o delay **/
void delayVerifier()
{
  moveCounterEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> aux = moveCounterEnd - moveCounterStart; //Magia negra
  delay = aux.count();
}

/** Atualiza a dificuldade **/
void updateDifficulty()
{
  threshold *= 0.99; //Aumenta a velocidade das peças em 1% a cada peça jogada
}

/** Gerador aleatorio **/
int getRandom()
{
  return rand() % 7;
}

/** Função que seta as cores de cada render do jogo **/
void colorPicker(int index)
{
  switch(index)
  {
    case 1:  game.colors[0] = 1.0;  game.colors[1] = 1.0;  game.colors[2] = 0.0; break; //O (Amarelo)
    case 2:  game.colors[0] = 0.2;  game.colors[1] = 0.5;  game.colors[2] = 1.0; break; //I (Azul-Eserdeado)
    case 3:  game.colors[0] = 1.0;  game.colors[1] = 0.1;  game.colors[2] = 0.1; break; //Z (Vermelho)
    case 4:  game.colors[0] = 0.1;  game.colors[1] = 1.0;  game.colors[2] = 0.1; break; //S (Verde)
    case 5:  game.colors[0] = 1.0;  game.colors[1] = 0.6;  game.colors[2] = 0.1; break; //L (Laranja)
    case 6:  game.colors[0] = 0.0;  game.colors[1] = 0.0;  game.colors[2] = 1.0; break; //J (Azul)
    case 7:  game.colors[0] = 0.5;  game.colors[1] = 0.0;  game.colors[2] = 1.0; break; //T (Roxo)
    case 8:  game.colors[0] = 0.0;  game.colors[1] = 0.0;  game.colors[2] = 0.0; break; //Borda invisivel (Preto)
    case 9:  game.colors[0] = 1.0;  game.colors[1] = 1.0;  game.colors[2] = 1.0; break; //Linha completa (Branco)
    default: game.colors[0] = 0.1;  game.colors[1] = 0.1;  game.colors[2] = 0.1;        //Espaço vazio (Cinza Escuro)
  }
}

/********************************************************************************************************************************************************************************************/
/*** Funções do campo e tetrominoes ***/
/** Preenche as bordas do tabuleiro **/
void getFieldBorder()
{
  for (int l = 0; l < FL; l++)
    for (int c = 0; c < FC; c++)
      if (l == 0 || l == FL - 1 || c == 0 || c == FC - 1)
        game.field[l][c] = 8;
}

/** Reseta o tabuleiro **/
void resetField()
{
  for (int l = 1; l < FL - 1; l++)
    for (int c = 1; c < FC - 1; c++)
      game.field[l][c] = 0;
}

/** Preenche a matriz de uma peça **/
void getTetro(int tetros[ST][SS][SS], int tetro[SS][SS], int type)
{
  for (int l = 0; l < SS; l++)
    for (int c = 0; c < SS; c++)
      tetro[l][c] = tetros[type][l][c];
}

/** Inicializa as peças **/
void getTetroActive()
{
  getTetro(tetros, tetroActive.tetro, tetroActive.type);
}

void getTetroNext()
{
  getTetro(tetros, tetroNext.tetro, tetroNext.type);
}

void getTetroHold()
{
  getTetro(tetros, tetroHold.tetro, tetroHold.type);
}

void getTetroProjection()
{
  for (int l = 0; l < SS; l++)
    for (int c = 0; c < SS; c++)
      tetroActive.projection[l][c] = tetroActive.tetro[l][c];
}

/** Verifica se o next é igual ao active ou qualquer um do histórico **/
int isEqual()
{
  for (int i = 0; i < HS; i++)
    for (int j = 0; j < HS; j++)
      if (tetroNext.type == tetroActive.typeHistory[j] || tetroNext.type == tetroActive.type)
        return 1;

  return 0;
}

/** Gera um next diferente do active e das outras peças sorteadas **/
void getNewType()
{
  int verifier = isEqual();
  tetroNext.type = getRandom();

  while (verifier == 1)
  {
    srand(rand());
    tetroNext.type = getRandom();
    verifier = isEqual();
  }
}

/** Sequencia os valores das peças em jogo **/
void sequenceTetros()
{
  for (int i = HS - 1; i > 0; i--)
    tetroActive.typeHistory[i] = tetroActive.typeHistory[i - 1];

  tetroActive.typeHistory[0] = tetroActive.type;
  tetroActive.type = tetroNext.type;

  getNewType();
}

/** Faz o swap entre o Active e Hold **/
void swapTetros()
{
  if (game.swapped == 0)
  {
    tetroActive.posX = 5;
    tetroActive.posY = resetPosY(tetroActive.posY);

    int aux = tetroActive.type;
    tetroActive.type = tetroHold.type;
    tetroHold.type = aux;

    getTetroActive();
    getTetroHold();

    if (tetroActive.type > 6 || tetroActive.type < 0)
    {
      sequenceTetros();
      getTetroActive();
      getTetroNext();
      getTetroProjection();
    }
  }

  game.swapped = 1;
  moveCounterStart = std::chrono::high_resolution_clock::now();
  tetroActive.projPosY = resetPosY(tetroActive.projPosY);
  tetroActive.projPosY = getProjectionY(tetroActive.projPosY);
  getTetroProjection();
}

/** Registra a peça ativa dentro do tabuleiro quando ela for assentada **/
void putTetro()
{
  for (int l = 0; l < SS; l++)
    for (int c = 0; c < SS; c++)
      if (tetroActive.tetro[l][c] != 0)
        game.field[tetroActive.posY + l][tetroActive.posX + c] = tetroActive.tetro[l][c];
}

/********************************************************************************************************************************************************************************************/
/*** Removedor de linhas completas ***/
/** Verifica se a linha está cheia **/
int lineIsFull(int line)
{
  for (int c = 1; c < FC - 1; c++)
    if (game.field[line][c] == 0)
      return 0;

  return 1;
}

/** Pinta a linha inteira de branco antes dela desaparecer **/
void paintFullLines(int value)
{
  for (int l = 1; l < FL - 1; l++)
    if (game.fullLines[l] == 1)
      for (int c = 1; c < FC - 1; c++)
        game.field[l][c] = value;
}

/** Apaga uma linha **/
void eraseLine()
{
  int topLine = 1;
  for (int l = 1; l < FL - 1; l++) //Determina qual a linha completa mais de cima
  {
    if (game.fullLines[l] == 1)
    {
      topLine = l;
      game.pointsMultiplier++;
      break;
    }
  }

  for (int l = topLine; l > 0; l--) //Desce todas as linhas de cima
    for (int c = 1; c < FC - 1; c++)
      game.field[l][c] = game.field[l - 1][c];

  for (int c = 1; c < FC - 1; c++)
    game.field[1][c] = 0; //Se nao fizer isso, a primeira linha do tabuleiro recebe a borda

  for (int i = 0; i < FL; i++) //Reseta a matriz que guarda todas as linhas completas
    game.fullLines[i] = 0;
}

void eraseLines()
{
  for (int l = 1; l < FL - 1; l++)
  {
    game.fullLines[l] = lineIsFull(l);
    eraseLine();
  }
}

/** Soma os pontos atuais com 2^n **/
int calculatePoints (int points)
{
  return points += (1 << game.pointsMultiplier) * 100;
}

void resetMultiplier()
{
  game.pointsMultiplier = -1;
}

void updateScore()
{
  game.points = calculatePoints(game.points);
  resetMultiplier();
}

/** Executa todo o resto para ser chamada só uma função **/
void fullLineLogic()
{
  for (int l = 1; l < FL - 1; l++)
  {
    if (lineIsFull(l) == 1)
    {
      game.renderState = 1;
      game.clearedLines++;
    }

    game.fullLines[l] = lineIsFull(l);
  }

  paintFullLines(9);
  game.renderState = 1;
  moveCounterStart = std::chrono::high_resolution_clock::now();
}

/********************************************************************************************************************************************************************************************/
/*** Game loop e lógica do ranking ***/
/** Reseta o round **/
void newRound()
{
  /* Resetando o cronometro de movimento */
  moveCounterStart = std::chrono::high_resolution_clock::now();
  putTetro();

  /* Aplicando lógica de quando as linhas estão completas e somando pontos por assentar a peça*/
  fullLineLogic();
  game.points += 5;
  updateDifficulty();

  /* Atualizando os valores das peças */
  sequenceTetros();
  getTetroActive();
  getTetroProjection();
  getTetroNext();

  /* Resetando alguns parametros */
  game.swapped = 0;
  tetroActive.posX = 5;
  tetroActive.posY = resetPosY(tetroActive.posY);
  tetroActive.projPosY = resetPosY(tetroActive.projPosY);
}

/** Sequencia o jogo **/
void sequenceGame()
{
  delayVerifier();
  moveTetroAuto();
}
