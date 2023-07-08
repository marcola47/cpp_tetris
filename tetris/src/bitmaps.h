/***** Header que contém os bitmaps e funções que geram as palavras usadas no jogo *****/

/*** Bitmaps ***/
int bitMaps[CT][CL][CC]
{
 {{0,0,1,1,1,1,1,0,0}, //A 0
  {0,1,1,1,1,1,1,1,0},
  {1,1,1,0,0,0,1,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1}},

 {{0,1,1,1,1,1,1,1,0}, //C 1
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,1,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1,0}},

 {{0,1,1,1,1,1,1,1,1}, //E 2
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,0,0,0,0,0,0},
  {1,1,1,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,0,0,0,0,0,0},
  {1,1,1,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1,1}},

 {{0,1,1,1,1,1,1,1,0}, //G 3
  {1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,1,1,1,1,0},
  {1,1,0,0,1,1,1,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1,0}},

 {{1,1,1,1,1,1,1,1,1}, //I 4
  {0,1,1,1,1,1,1,1,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,1,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,1,1}},

 {{0,0,0,1,1,1,1,1,0}, //J 5
  {0,0,0,0,1,1,1,1,0},
  {0,0,0,0,0,0,1,1,0},
  {0,0,0,0,0,0,1,1,0},
  {0,0,0,0,0,0,1,1,0},
  {1,1,0,0,0,0,1,1,0},
  {1,1,0,0,0,0,1,1,0},
  {1,1,0,0,0,0,1,1,0},
  {1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0,0}},

 {{0,1,0,0,0,0,0,0,0}, //L 6
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,1,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1,0}},

 {{1,1,0,0,0,0,0,1,1}, //M 7
  {1,1,1,0,0,0,1,1,1},
  {1,1,1,1,0,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,0,1,1,1,0,1,1},
  {1,1,0,0,1,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1}},

 {{1,1,0,0,0,0,0,1,1}, //N 8
  {1,1,1,0,0,0,0,1,1},
  {1,1,1,1,0,0,0,1,1},
  {1,1,1,1,1,0,0,1,1},
  {1,1,0,1,1,1,0,1,1},
  {1,1,0,0,1,1,1,1,1},
  {1,1,0,0,0,1,1,1,1},
  {1,1,0,0,0,0,1,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1}},

 {{0,1,1,1,1,1,1,1,0}, //O 9
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,0,0,0,1,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,1,0,0,0,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1,0}},

 {{1,1,1,1,1,1,1,0,0}, //R 10
  {1,1,1,1,1,1,1,1,0},
  {1,1,0,0,0,0,1,1,0},
  {1,1,0,0,0,0,1,1,0},
  {1,1,0,0,0,1,1,1,0},
  {1,1,1,1,1,1,1,0,0},
  {1,1,1,1,1,0,0,0,0},
  {1,1,0,1,1,1,0,0,0},
  {1,1,0,0,1,1,1,0,0},
  {1,1,0,0,0,1,1,1,0}},

 {{0,1,1,1,1,1,1,1,0}, //S 11
  {1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,1,1},
  {0,0,0,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1,0}},


 {{1,1,1,1,1,1,1,1,1}, //T 12
  {0,1,1,1,1,1,1,1,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,1,1,1,1,1,0,0}},

 {{1,1,0,0,0,0,0,1,1}, //U 13
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,1,0,0,0,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1,0}},

 {{1,1,0,0,0,0,0,1,1}, //V 14
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,1,1},
  {1,1,1,0,0,0,1,1,1},
  {0,1,1,0,0,0,1,1,0},
  {0,1,1,1,0,1,1,1,0},
  {0,0,1,1,1,1,1,0,0},
  {0,0,0,1,1,1,0,0,0}},

 {{8,9,9,9,9,9,9,9,8}, //PAUSE BUTTON 15
  {9,9,8,8,8,8,8,9,9},
  {9,8,8,8,8,8,8,8,9},
  {9,8,8,9,8,9,8,8,9},
  {9,8,8,9,8,9,8,8,9},
  {9,8,8,9,8,9,8,8,9},
  {9,8,8,9,8,9,8,8,9},
  {9,8,8,8,8,8,8,8,9},
  {9,9,8,8,8,8,8,9,9},
  {8,9,9,9,9,9,9,9,8}},
};

/*****************************************************************/
/*** Textos ***/
void getLogo(int logo[6][CL][CC])
{
  for (int b = 0; b < 6; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        switch(b)
        {
          case 0: logo[b][l][c] = bitMaps[12][l][c]; break;
          case 1: logo[b][l][c] = bitMaps[2][l][c]; break;
          case 2: logo[b][l][c] = bitMaps[12][l][c]; break;
          case 3: logo[b][l][c] = bitMaps[10][l][c]; break;
          case 4: logo[b][l][c] = bitMaps[4][l][c]; break;
          case 5: logo[b][l][c] = bitMaps[11][l][c]; break;
        }
}

void getGO(int go[9][CL][CC])
{
  for (int b = 0; b < 9; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        switch(b)
        {
          case 0: go[b][l][c] = bitMaps[3][l][c]; break;
          case 1: go[b][l][c] = bitMaps[0][l][c]; break;
          case 2: go[b][l][c] = bitMaps[7][l][c]; break;
          case 3: go[b][l][c] = bitMaps[2][l][c]; break;
          case 4: go[b][l][c] = 0; break; //Espaço
          case 5: go[b][l][c] = bitMaps[9][l][c]; break;
          case 6: go[b][l][c] = bitMaps[14][l][c]; break;
          case 7: go[b][l][c] = bitMaps[2][l][c]; break;
          case 8: go[b][l][c] = bitMaps[10][l][c]; break;
        }
}

/*****************************************************************/
/*** Botões ***/
void getBtnJogar(int btnJogar[5][CL][CC])
{
  for (int b = 0; b < 5; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        switch(b)
        {
          case 0: btnJogar[b][l][c] = bitMaps[5][l][c]; break;
          case 1: btnJogar[b][l][c] = bitMaps[9][l][c]; break;
          case 2: btnJogar[b][l][c] = bitMaps[3][l][c]; break;
          case 3: btnJogar[b][l][c] = bitMaps[0][l][c]; break;
          case 4: btnJogar[b][l][c] = bitMaps[10][l][c]; break;
        }
}

void getBtnSair(int btnSair[4][CL][CC])
{
  for (int b = 0; b < 4; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        switch(b)
        {
          case 0: btnSair[b][l][c] = bitMaps[11][l][c]; break;
          case 1: btnSair[b][l][c] = bitMaps[0][l][c]; break;
          case 2: btnSair[b][l][c] = bitMaps[4][l][c]; break;
          case 3: btnSair[b][l][c] = bitMaps[10][l][c]; break;
        }
}

void getBtnPause(int btnPause[CL][CC])
{
  for (int l = 0; l < CL; l++)
    for (int c = 0; c < CC; c++)
      btnPause[l][c] = bitMaps[15][l][c];
}

void getBtnJN(int btnJN[15][CL][CC])
{
  for (int b = 0; b < 15; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        switch(b)
        {
          case 0: btnJN[b][l][c] = bitMaps[5][l][c]; break;
          case 1: btnJN[b][l][c] = bitMaps[9][l][c]; break;
          case 2: btnJN[b][l][c] = bitMaps[3][l][c]; break;
          case 3: btnJN[b][l][c] = bitMaps[0][l][c]; break;
          case 4: btnJN[b][l][c] = bitMaps[10][l][c]; break;
          case 5: btnJN[b][l][c] = 0; break; //Espaço
          case 6: btnJN[b][l][c] = bitMaps[8][l][c]; break;
          case 7: btnJN[b][l][c] = bitMaps[9][l][c]; break;
          case 8: btnJN[b][l][c] = bitMaps[14][l][c]; break;
          case 9: btnJN[b][l][c] = bitMaps[0][l][c]; break;
          case 10: btnJN[b][l][c] = bitMaps[7][l][c]; break;
          case 11: btnJN[b][l][c] = bitMaps[2][l][c]; break;
          case 12: btnJN[b][l][c] = bitMaps[8][l][c]; break;
          case 13: btnJN[b][l][c] = bitMaps[12][l][c]; break;
          case 14: btnJN[b][l][c] = bitMaps[2][l][c]; break;
        }
}

void getBtnMI(int btnMI[12][CL][CC])
{
  for (int b = 0; b < 12; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        switch(b)
        {
          case 0: btnMI[b][l][c] = bitMaps[7][l][c]; break;
          case 1: btnMI[b][l][c] = bitMaps[2][l][c]; break;
          case 2: btnMI[b][l][c] = bitMaps[8][l][c]; break;
          case 3: btnMI[b][l][c] = bitMaps[13][l][c]; break;
          case 4: btnMI[b][l][c] = 0; break; //Espaço
          case 5: btnMI[b][l][c] = bitMaps[4][l][c]; break;
          case 6: btnMI[b][l][c] = bitMaps[8][l][c]; break;
          case 7: btnMI[b][l][c] = bitMaps[4][l][c]; break;
          case 8: btnMI[b][l][c] = bitMaps[1][l][c]; break;
          case 9: btnMI[b][l][c] = bitMaps[4][l][c]; break;
          case 10: btnMI[b][l][c] = bitMaps[0][l][c]; break;
          case 11: btnMI[b][l][c] = bitMaps[6][l][c]; break;
        }
}

/*****************************************************************/
/*** Outros ***/
void logoRandomizer (int logo[6][CL][CC])
{
  for (int b = 0; b < CT; b++)
    for (int l = 0; l < CL; l++)
      for (int c = 0; c < CC; c++)
        if (logo[b][l][c] == 1)
          logo[b][l][c] = getRandom() + 1;
}

void getUIComponents()
{
  getLogo(ui.logo);
  getGO(ui.go);
  getBtnJogar(ui.jogar);
  getBtnSair(ui.sair);
  getBtnPause(ui.pause);
  getBtnJN(ui.jn);
  getBtnMI(ui.mi);

  logoRandomizer(ui.logo);
}
