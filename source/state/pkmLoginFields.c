#include <3ds.h>
#include "state.h"

void 	logLoginEnter(t_stinf *state)
{
  if (dirInputField(state, 0, 2, 0, 0)) return;
  if (state->kPressed & KEY_A)
  {
    state->login = overlayGetLogin();
    state->modded = 1;
    state->inSel = 0;
  }
}

void 	logPasswordEnter(t_stinf *state)
{
  if (stdInputField(state, -1, 1, 0, 0)) return;
  if (state->kPressed & KEY_A)
  {
    state->password = overlayGetPassword();
    state->modded = 1;
    state->inSel = 0;
  }
}

void 	logRegisterYesNo(t_stinf *state)
{
  if (stdInputField(state, -1, 1, 0, 0)) return;
  if (state->kPressed & KEY_A)
  {
    if (state->reg == 0)
        state->reg = 1;
    else
        state->reg = 0;
    state->inSel = 0;
  }
}

void login(t_stinf *state)
{
  if (stdInputField(state, -1, 0, 0, 0)) return;
  if (state->kPressed & KEY_A)
  {
    u8 src[232];

    u8 internet_access(u8 upDown, int slot, t_stinf *state, u8 *dest, u8 timeout);
    internet_access(3, 0, state, src, 50);
  }
}

void 	pkmLogInputField(t_stinf *state)
{
  switch (state->inState){
    case 1: logLoginEnter(state); break;
    case 2: logPasswordEnter(state); break;
    case 3: logRegisterYesNo(state); break;
    case 4: login(state); break;
  }
}
