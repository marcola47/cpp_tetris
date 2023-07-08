/***** Header que contém as funções essenciais para o sistema de movimento, detecção e rotação das peças e do campo ******/


/*** Mover a peça no eixo X ou Y ***/
/** Verifica se é possivel mover **/
int tetroFits(int tetro[SS][SS], int posX, int posY, int direction)
{
  if (direction == 0)
  {
    for (int l = 0; l < SS; l++)
      for (int c = 0; c < SS; c++)
        if (tetro[l][c] != 0 && game.field[posY + l + 1][posX + c] != 0)
          return 0;
  }

  else
  {
    for (int l = 0; l < SS; l++)
      for (int c = 0; c < SS; c++)
        if (tetro[l][c] != 0 && game.field[posY + l][posX + c + direction] != 0)
          return 0;
  }

  return 1;
}

/** Reseta a posição Y **/
int resetPosY(int posY)
{
  return posY = 0;
}

/** Aumenta a posição da projeção **/
int incrementProjectionY(int posY)
{
  if (tetroFits(tetroActive.projection, tetroActive.posX, tetroActive.projPosY, 0) == 1)
    return posY += 1;

  else
    return posY;
}

/** Recebe o maior valor Y da projeção **/
int getProjectionY (int posY)
{
  for (int l = 1; l < FL - 1; l++)
    return posY = incrementProjectionY(posY);
}

/** Move para baixo **/
int moveTetroY(int posY)
{
  if (tetroFits(tetroActive.tetro, tetroActive.posX, tetroActive.posY, 0) == 1 && gameIsOver() == 0)
  {
    getLogo(ui.logo);
    logoRandomizer(ui.logo);

    moveCounterStart = std::chrono::high_resolution_clock::now();
    return posY + 1;
  }

  else
  {
    newRound();
  }
}

/** Força para baixo **/
void forceTetroY()
{
  getLogo(ui.logo);
  logoRandomizer(ui.logo);

  tetroActive.posY = tetroActive.projPosY;
  newRound();
}

/** Move para esquerda ou direita **/
int moveTetroX(int posX, int direction)
{
  if (tetroFits(tetroActive.tetro, tetroActive.posX, tetroActive.posY, -1) == 1 && direction == -1)
  {
    tetroActive.projPosY = tetroActive.posY;
    return posX - 1;
  }


  else if (tetroFits(tetroActive.tetro, tetroActive.posX, tetroActive.posY, 1) == 1 && direction == 1)
  {
    tetroActive.projPosY = tetroActive.posY;
    return posX + 1;
  }

  else
    return posX;
}

/** Move automaticamente **/
void moveTetroAuto()
{
  if (delay > threshold)
  {
    tetroActive.posY = moveTetroY(tetroActive.posY);
    eraseLines();
  }

  else if (gameIsOver() == 1)
  {
    game.mode = 3;
    resetField();
  }
}

/********************************************************************************************************************************************************************************************/
/*** Rotacionar tetrominoes ***/
/** Transpoe a matriz (linhas viram colunas / colunas viram linhas) **/
void transpose(int tetro[SS][SS])
{
  int matAux[SS][SS];

  for (int l = 0; l < SS; l++)
    for (int c = 0; c < SS; c++)
      matAux[l][c] = tetro[c][l];

  for (int l = 0; l < SS; l++)
    for (int c = 0; c < SS; c++)
      tetro[l][c] = matAux[l][c];
}

/** Inverte as colunas da matriz **/
void reverse(int tetro[SS][SS])
{
  for (int l = 0; l < SS; l++)
  {
    for (int c = 0; c < SS / 2; c++)
    {
      int temp = tetro[l][c];
      tetro[l][c] = tetro[l][SS - c - 1];
      tetro[l][SS - c - 1] = temp;
    }
  }
}

/** Verifica se a rotação é válida **/
int rotationIsValid()
{
  int nextRotation[SS][SS];
  for (int l = 0; l < SS; l++)
    for (int c = 0; c < SS; c++)
      nextRotation[l][c] = tetroActive.tetro[l][c];

  transpose(nextRotation);
  reverse(nextRotation);

  for (int l = 0; l < SS; l++)
    for (int c = 0; c < SS; c++)
      if (nextRotation[l][c] != 0 && game.field[tetroActive.posY + l][tetroActive.posX + c] != 0)
        return 0;

  return 1;
}

/** Executa as duas para rotacionar 90° (Ou só transpoe se a peça for o I) **/
void rotate()
{
  if (rotationIsValid() == 1)
  {
    if (tetroActive.type > 1)
    {
      transpose(tetroActive.tetro);
      reverse(tetroActive.tetro);
    }

    else if (tetroActive.type == 1)
    {
      transpose(tetroActive.tetro);
    }
  }

  // Resetar a projeção da peça
  tetroActive.projPosY = tetroActive.posY;
  tetroActive.projPosY = getProjectionY(tetroActive.projPosY);
  getTetroProjection();
}
