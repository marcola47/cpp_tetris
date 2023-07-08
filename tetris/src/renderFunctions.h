/***** Header que contém todas as funções de render que serão chamadas na render() principal *****/

/**** Jogo ****/
/** Renderiza o campo **/
void renderField()
{
  tetroActive.projPosY = getProjectionY(tetroActive.projPosY);
  int l, c;
  for (l = 0; l < FL; l++)
  {
    for (c = 0; c < FC; c++)
    {
      colorPicker(game.field[l][c]);
      CV::color(game.colors[0], game.colors[1], game.colors[2]);

      CV::rectCustom
      (
        c*game.cellSize + game.initX + 1,
        l*game.cellSize + game.initY + 1,
        (c+1)*game.cellSize + game.initX - 1,
        (l+1)*game.cellSize + game.initY - 1,
        game.borderThick*3 //Vira basicamente um rectFill(), mas ele é mais desfocado ou algo assim. Fica mais legal.
      );
    }
  }

  game.endX = FC*game.cellSize + game.initX;
  game.endY = FL*game.cellSize + game.initY;

  colorPicker(tetroActive.tetro[2][2]);
  CV::color(game.colors[0], game.colors[1], game.colors[2]);

  //Função do canvas que criei pra gerar um retangulo com espessura maior que 1px (A espessura aumenta de fora pra dentro, q nem box-sizing: border-box em web)
  CV::rectCustom(game.initX + 9, game.initY + 9, game.endX - 10, game.endY - 10, 9);
}

/** Renderiza a peça ativa **/
void renderActive()
{
  for (int l = 0; l < SS; l++)
  {
    for (int c = 0; c < SS; c++)
    {
      if (tetroActive.tetro[l][c] != 0)
      {
        colorPicker(tetroActive.tetro[l][c]);

        CV::color(game.colors[0] - 0.65, game.colors[1] - 0.65, game.colors[2] - 0.65);
        CV::rectFill
        (
          (c + tetroActive.posX)*game.cellSize + game.initX + 1,
          (l + tetroActive.posY)*game.cellSize + game.initY + 1,
          (c + tetroActive.posX + 1)*game.cellSize + game.initX - 1,
          (l + tetroActive.posY + 1)*game.cellSize + game.initY - 1
        );

        CV::color(game.colors[0], game.colors[1], game.colors[2]);
        CV::rectCustom
        (
          (c + tetroActive.posX)*game.cellSize + game.initX + 1,
          (l + tetroActive.posY)*game.cellSize + game.initY + 1,
          (c + tetroActive.posX + 1)*game.cellSize + game.initX - 1,
          (l + tetroActive.posY + 1)*game.cellSize + game.initY - 1,
          (float)tetroActive.posY / (float)tetroActive.projPosY * 10 + 1
        );
      }
    }
  }
}

/** Renderiza o placar **/
void renderScores()
{
  CV::color(1, 1, 1);

  CV::rectCustom(game.pointsInitX, game.pointsInitY, game.pointsEndX, game.pointsEndY, game.borderThick);
  CV::text(game.pointsInitX + 10, game.pointsInitY + game.cellSize + 2, game.points);
  CV::text(game.pointsInitX, game.pointsEndY + game.cellSize, "PONTOS");

  CV::rectCustom(game.linesInitX, game.linesInitY, game.linesEndX, game.linesEndY, game.borderThick);
  CV::text(game.linesInitX + 10, game.linesInitY + game.cellSize + 2, game.clearedLines);
  CV::text(game.linesInitX, game.linesEndY + game.cellSize, "LINHAS");
}

/** Renderiza peças auxiliares fora do campo **/
void renderTetroAux(tetroAux* ptr)
{
  int l, c;
  for (l = 0; l < SS; l++)
  {
    for (c = 0; c < SS; c++)
    {
      if (ptr->tetro[l][c] != 0)
      {
        colorPicker(ptr->tetro[l][c]);
        CV::color(game.colors[0], game.colors[1], game.colors[2]);

        if (ptr->type == 0) //O
        {
          CV::rectCustom
          (
            (c)*(game.cellSize+5) + ptr->initX + 20,
            (l)*(game.cellSize+5) + ptr->initY + 10,
            (c+1)*(game.cellSize+5) + ptr->initX + 18,
            (l+1)*(game.cellSize+5) + ptr->initY + 8,
             (game.cellSize+5) / 2
          );
        }

        else if (ptr->type == 1) //I
        {
          CV::rectCustom
          (
            (c)*(game.cellSize+5) + ptr->initX + 20,
            (l)*(game.cellSize+5) + ptr->initY - 2,
            (c+1)*(game.cellSize+5) + ptr->initX + 18,
            (l+1)*(game.cellSize+5) + ptr->initY - 4,
             (game.cellSize+5) / 2
           );
        }

        else if (ptr->type > 1 && ptr->type < 7) //Resto
        {
          CV::rectCustom
          (
            (c)*(game.cellSize+5) + ptr->initX + 9,
            (l)*(game.cellSize+5) + ptr->initY + 10,
            (c+1)*(game.cellSize+5) + ptr->initX + 7,
            (l+1)*(game.cellSize+5) + ptr->initY + 8,
             (game.cellSize+5) / 2
          );
        }
      }
    }
  }

  ptr->endX = ptr->initX + (c+2)*game.cellSize;
  ptr->endY = ptr->initY + (l+1)*game.cellSize;
}

/** Renderiza a peça segurada **/
void renderHold() //Eu poderia fazer uma função só pros 2 tetros auxiliares, mas, o render da hold caga se eu nao usar aql 3° condição, alem da função ter MUITOS parametros
{
  getTetroHold();
  renderTetroAux(hold_ptr);

  colorPicker(tetroHold.tetro[2][2]);
  if (tetroHold.type == -1) CV::color(1, 1, 1);
  else if (tetroHold.type != 0) CV::color(game.colors[0], game.colors[1], game.colors[2]);

  CV::rectCustom(tetroHold.initX, tetroHold.initY, tetroHold.endX, tetroHold.endY, game.borderThick);
  CV::text(tetroHold.initX, tetroHold.endY + game.cellSize, "SEGURANDO");
}

/** Renderiza a proxima peça **/
void renderNext()
{
  renderTetroAux(next_ptr);

  colorPicker(tetroNext.tetro[2][2]);
  CV::color(game.colors[0], game.colors[1], game.colors[2]);

  CV::rectCustom(tetroNext.initX, tetroNext.initY, tetroNext.endX, tetroNext.endY, game.borderThick);
  CV::text(tetroNext.initX, tetroNext.endY + game.cellSize, "PROXIMA");
}

/** Renderiza a projeção da peça ativa **/
void renderProjection()
{
  for (int l = 0; l < SS; l++)
  {
    for (int c = 0; c < SS; c++)
    {
      if (tetroActive.projection[l][c] != 0 && tetroFits(tetroActive.projection, tetroActive.posX, tetroActive.projPosY, 0) == 0)
      { //Só renderiza se estiver o mais baixo possivel
        colorPicker(tetroActive.projection[l][c]);

        CV::color(game.colors[0] - 0.9, game.colors[1] - 0.9, game.colors[2] - 0.9);
        CV::rectFill
        (
          (c + tetroActive.posX)*game.cellSize + game.initX + 1,
          (l + tetroActive.projPosY)*game.cellSize + game.initY + 1,
          (c + tetroActive.posX + 1)*game.cellSize + game.initX - 1,
          (l + tetroActive.projPosY + 1)*game.cellSize + game.initY - 1
        );

        CV::color(game.colors[0], game.colors[1], game.colors[2]);
        CV::rect
        (
          (c + tetroActive.posX)*game.cellSize + game.initX + 1,
          (l + tetroActive.projPosY)*game.cellSize + game.initY + 1,
          (c + tetroActive.posX + 1)*game.cellSize + game.initX - 1,
          (l + tetroActive.projPosY + 1)*game.cellSize + game.initY - 1
        );
      }
    }
  }
}

/** Chama todos os outros renders, pra render() ficar menos poluida **/
void renderGameElements()
{
    renderField();
    renderProjection();
    renderActive();
    renderNext();
    renderHold();
    renderNext();
    renderScores();
}

/****************************************************************************************************************************************************************************/
/**** UI ****/ //Eu ia fazer uma função só que precisa mudar os parametros, mas ia ser muito mais complicado, então, não achei valido perder tempo
/*** Headers ***/
/** Renderiza a logo TETRIS **/
void renderLogo(float fontSize)
{
  logo.fontSize = fontSize; //Preciso fazer isso pq se nao a margem fica um pouco deslocada
  logo.fullCharSize = fontSize*(CC+3);

  for (int b = 0; b < 6; b++)
  {
    for (int l = 0; l < CL; l++)
    {
      for (int c = 0; c < CC; c++)
      {
        if (ui.logo[b][l][c] != 0)
        {
          colorPicker(ui.logo[b][l][c]);

          //Quadrado mais escuro de dentro
          CV::color(game.colors[0] - 0.4, game.colors[1] - 0.4, game.colors[2] - 0.4);
          CV::rectFill(c*fontSize + logo.initX + b*logo.fullCharSize, l*fontSize + logo.initY, (c+1)*fontSize + logo.initX + b*logo.fullCharSize, (l+1)*fontSize + logo.initY);

          //Borda mais clara
          CV::color(game.colors[0], game.colors[1], game.colors[2]);
          CV::rect(c*fontSize + logo.initX + b*logo.fullCharSize, l*fontSize + logo.initY, (c+1)*fontSize + logo.initX + b*logo.fullCharSize, (l+1)*fontSize + logo.initY);
        }
      }
    }
  }
}

/** Renderiza o GAME OVER **/
void renderGameOver(float fontSize)
{
  go.fontSize = fontSize; //Preciso fazer isso pq se nao a margem fica um pouco deslocada
  go.fullCharSize = fontSize*(CC+3);

  CV::color(1, 0, 0);
  for (int b = 0; b < 9; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        if (ui.go[b][l][c] != 0)
          CV::rectFill(c*fontSize + go.initX + b*go.fullCharSize, l*fontSize + go.initY, (c+1)*fontSize + go.initX + b*go.fullCharSize, (l+1)*fontSize + go.initY);

  /* Pontos e Linhas */
  CV::color(1, 1, 1);
  CV::text(go.initX, go.endY, "PONTOS:"); CV::text(go.initX + 75, go.endY, game.points);

  if (game.clearedLines >= 100) //Assim as linhas ficam com margem pra direita correta
    {CV::text(go.initX + go.fullCharSize*7 - 20, go.endY, "LINHAS:"); CV::text(go.initX + go.fullCharSize*7 + 55, go.endY, game.clearedLines);}

  else if (game.clearedLines >= 10 && game.clearedLines < 100) //Assim as linhas ficam com margem pra direita correta
    {CV::text(go.initX + go.fullCharSize*7 - 10, go.endY, "LINHAS:"); CV::text(go.initX + go.fullCharSize*7 + 65, go.endY, game.clearedLines);}

  else
    {CV::text(go.initX + go.fullCharSize*7, go.endY, "LINHAS:"); CV::text(go.initX + go.fullCharSize*7 + 75, go.endY, game.clearedLines);}
}

/****************************************************************************************************************************************************************************/
/*** Botões ***/
/** Renderiza o jogo pausado **/
void renderPauseMenu()
{
  for (int l = 0; l < CL; l++)
  {
    for (int c = 0; c < CC; c++)
    {
      colorPicker(ui.pause[l][c]);
      CV::color(game.colors[0], game.colors[1], game.colors[2]);

      if (game.mode == 0)
        CV::color(1, 1, 0);

      if (ui.pause[l][c] != 8) //Se for os quadrados bem dos cantos ele nao renderiza, ai fica meio arredondado
        CV::rectFill(c*pause.fontSize + pause.initX, pause.initY - l*pause.fontSize, (c+1)*pause.fontSize + pause.initX, pause.initY - (l+1)*pause.fontSize);
    }
  }
}


/** Render dos botões **/
void renderBtn(uiPos* pos_ptr, int stringMat[][CL][CC], float fontSize, int stringSize, int color)
{
  pos_ptr->fontSize = fontSize;
  pos_ptr->fullCharSize = fontSize*(CC+3);

  if (checkRenderPosition(pos_ptr->initX - 20, pos_ptr->initY - 10, pos_ptr->endX + pos_ptr->initX + 10, pos_ptr->endY + 10) == 1)
  {
    CV::color(color); //Usa as cores padrões do canvas2D
    CV::line(pos_ptr->initX - 5, pos_ptr->endY - 5, pos_ptr->initX + pos_ptr->endX - 2, pos_ptr->endY - 5);
  }

  else
    CV::color(1, 1, 1);

  for (int b = 0; b < stringSize; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        if (stringMat[b][l][c] != 0)
          CV::rectFill
          (
            c*pos_ptr->fontSize + pos_ptr->initX + b*pos_ptr->fullCharSize,
            l*pos_ptr->fontSize + pos_ptr->initY,
            (c+1)*pos_ptr->fontSize + pos_ptr->initX + b*pos_ptr->fullCharSize,
            (l+1)*pos_ptr->fontSize + pos_ptr->initY
          );
}

/** Renderiza o botao de jogar **/
void renderBtnJogar(float fontSize) {renderBtn(jogar_ptr, ui.jogar, fontSize, 5, 3);}

/** Renderiza o botao de sair **/
void renderBtnSair (float fontSize) {renderBtn(sair_ptr, ui.sair, fontSize, 4, 2);}

/** Renderiza o botao de jogar novamente **/
void renderBtnJN   (float fontSize) {renderBtn(jn_ptr, ui.jn, fontSize, 15, 3);}

/** Renderiza o botão do menu inicial **/
void renderBtnMIGO (float fontSize) {renderBtn(miGO_ptr, ui.mi, fontSize, 12, 2);}

/** Renderiza o botão do menu inicial **/
void renderBtnMIP  (float fontSize) {renderBtn(miP_ptr, ui.mi, fontSize, 12, 13);}
