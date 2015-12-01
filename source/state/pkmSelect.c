#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "../pchex.h"

/*
 * Pokemon slot selection state
 */

void 	reloadPokemon(t_stinf *state)
{
  loadPokemon(state, state->pkmSlot, (u8 *) &state->pkm.pkx);
  pkmRecalc(&state->pkm);
}

void 	pkmSelectInit(t_stinf *state)
{
  consoleSelect(&state->pch->bot);
  consoleClear();

  if (state->inState)
  {
    state->inState = 0;
  }
  
  reloadPokemon(state);
}

void 	pkmSelectDisplay(t_stinf *state)
{
  printf("\x1B[0;0H"); //cursor home

  printf("Select a slot :\n");
  printf("Box %-2d Slot %-2d\n", state->pkmSlot / 30 + 1, state->pkmSlot % 30 + 1);
  if (state->pkm.pkx.species)
  {
    state->empty = 0;
    printf("%-12s\n", pkData.species[state->pkm.pkx.species]);
  }
  else
  {
    state->empty = 1;
    printf("Empty       \n");
  }
  for (int i = 0; i < 22; i++)
    printf("\n");
  for (int i = 0; i < 40; i++)
    printf("-");
  printf("DPad Left/Right : Previous/Next Slot\n");
  printf("DPad Up/Down    : Previous/Next Box\n");
  printf("A : Select Slot |   Start : Quit\n");
  char* logged = "Log In ";
  if (state->loggedIn == 1)
  {
      logged = "Log Out";
  }
  printf(concatinate("Select : Save   |   B : ", logged));
}

void 	pkmSelectInput(t_stinf *state)
{
  u32 	kPressed = state->kPressed;
  s8 	slotChange = 0;

  if (kPressed & KEY_START)
  {
    state->cont = 0;
    return;
  }
  if (kPressed & KEY_SELECT)
  {
    u8 src[232];
    if (state->loggedIn == 1)
    {
        internet_access(1, 930, state, src, 50);                        
    }
    consoleSelect(&state->pch->top);
    exportSave(state->pch->save, state->pch->game, &state->pch->sav.handle, &state->pch->sav.arch);
    consoleSelect(&state->pch->bot);
    return;
  }
  if (kPressed & KEY_A)
  {
      switchState(state, pkmGeneralState); 
      state->modded = 0; 
      return;
  }
  if (kPressed & KEY_B)
  { switchState(state, pkmLoginState); state->modded = 0; return;}
  if (kPressed & KEY_LEFT)
    slotChange -= 1;
  if (kPressed & KEY_RIGHT)
    slotChange += 1;
  if (kPressed & KEY_UP)
    slotChange += 30;
  if (kPressed & KEY_DOWN)
    slotChange -= 30;
  if (slotChange)
  {
    state->pkmSlot += slotChange;
    if (state->pkmSlot < 0)
      state->pkmSlot = 0;
    s16 maxSlot = 929;
    if (state->loggedIn == 1)
    {
        maxSlot = 1199;
    }
    if (state->pkmSlot > maxSlot)
      state->pkmSlot = maxSlot;
    reloadPokemon(state);
  }
}

struct s_UIState pkmSelectState = {&pkmSelectInit, &pkmSelectDisplay, &pkmSelectInput};
