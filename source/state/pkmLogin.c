#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <3ds.h>

#include "../pchex.h"
#include "state.h"

/*
 * General tab state
 */

char helpstringsLog[20][3][50] = {
  { "Up/Down/Left/Right : Choose field",
    "A : Select field ",
    "Start : Back" },
  {"","A : Choose Login","B : Leave field"},
  {"","A : Choose Password","B : Leave field"},
  {"","A : Register Yes/No","B : Leave field"},
  {"","A : Log In","B : Leave field"}
};

void 	pkmLoginInit(t_stinf *state)
{
  state->inState = 1;
  state->inSel = 0;
  consoleClear();
}

void 	pkmLoginHelp(t_stinf *state)
{
  u8	sel = state->inState;

  for (int i = 0; i < 40; i++)
    printf("-");
  if (!state->inSel)
    sel = 0;
  printf("%-40s", helpstringsLog[sel][0]);
  printf("%-40s", helpstringsLog[sel][1]);
  printf("%-40s", helpstringsLog[sel][2]);
}

void 	pkmLoginDisplay(t_stinf *state)
{
  struct s_pkx *pkx = &state->pkm.pkx;
  u8	ist = state->inState, sel = state->inSel;
  char 	tmp[50];
  
  pkmHeader(state);
  printf("\n");
  printf("\n");

  selectColor(1, ist, sel);
  printf(concatinate("Login: ", state->login));
  printf("\n");
  printf("\n");

  selectColor(2, ist, sel);
  printf(concatinate("Password: ", state->password));
  printf("\n");
  printf("\n");

  selectColor(3, ist, sel);
  char* getRegister(u8 reg);
  printf(concatinate("Register: ", getRegister(state->reg)));
  printf("\n");
  printf("\n");
  
  selectColor(4, ist, sel);
  printf(concatinate("Log In: ", state->uuid));
  printf("\n");
  printf("\n");
  
  resetColor();
  printf("\x1B[26;0H");
  pkmLoginHelp(state);
}

char* getRegister(u8 reg)
{
    if (reg == 0)
    {
        return concatinate("", "No ");
    }
    return concatinate("", "Yes");
}

void 	pkmLoginInput(t_stinf *state)
{
  u32 	kPressed = state->kPressed;

  if (kPressed & KEY_START)
  {	
    switchState(state, pkmSelectState);
    return;
  }
  pkmLogInputField(state);
}

struct s_UIState pkmLoginState = {&pkmLoginInit, &pkmLoginDisplay, &pkmLoginInput};

