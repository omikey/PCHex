#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include <malloc.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <3ds.h>
#include <setjmp.h>

#include <assert.h>

#include "pchex.h"



FS_archive sdmcArchive;

char tmpBuffer[512];
const int commandPort=5000;
int dataPort=5001;
char currentPath[4096];
u32 currentIP;

int listenfd;

u8 internet_access(u8 upDown, int slot, t_stinf *state, u8 *dest, u8 timeout)
{
	Result ret;
	ret=fsInit();
	sdmcArchive=(FS_archive){0x00000009, (FS_path){PATH_EMPTY, 1, (u8*)""}};
	FSUSER_OpenArchive(NULL, &sdmcArchive);
	ret=SOC_Initialize((u32*)memalign(0x1000, 0x100000), 0x100000);
	sprintf(currentPath, "/");
	currentIP=(u32)gethostid();
	listenfd=-1;
        u8 do1(u8 upDown, int slot, t_stinf *state, u8 *dest, u8 timeout);
        return do1(upDown, slot, state, dest, timeout);
}


u8 do1(u8 upDown, int slot, t_stinf *state, u8 *dest, u8 timeout)
{
      struct sockaddr_in servaddr;
	struct hostent *hp;
	int sock_id;
        sock_id = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_id == -1) {
            return 0;
	}
	else {
	memset(&servaddr,0,sizeof(servaddr));
	if((hp = gethostbyname("japanfour.com")) == NULL) {
            return 0;
	}
	else {
            u8 do2(struct sockaddr_in servaddr, struct hostent *hp, int sock_id, u8 upDown, int slot, t_stinf *state, u8 *dest, u8 timeout);
	return do2(servaddr, hp, sock_id, upDown, slot, state, dest, timeout);
	}
	}
}

u8 do2(struct sockaddr_in servaddr, struct hostent *hp, int sock_id, u8 upDown, int slot, t_stinf *state, u8 *dest, u8 timeout)
{
	memcpy((char *)&servaddr.sin_addr.s_addr, (char *)hp->h_addr, hp->h_length);
	servaddr.sin_port = htons(80); 
	servaddr.sin_family = AF_INET;
        u8 connected = connect(sock_id, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(connected != 0) {
            return 0;
	}
	else {
            u8 do3(int sock_id, u8 upDown, int slot, t_stinf *state, u8 *dest, u8 timeout);
        return do3(sock_id, upDown, slot, state, dest, timeout);
	}
}

char * concatinate(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

u8 do3(int sock_id, u8 upDown, int slot, t_stinf *state, u8 *dest, u8 timeout)
{
    	char request[] = " HTTP/1.1\n"
                         "Host: japanfour.com\n"
                         "Connection: keep-alive\n"
                         "Pragma: no-cache\n"
                         "Cache-Control: no-cache\n"
                         "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\n"
                         "Upgrade-Insecure-Requests: 1\n"
                         "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36\n"
                         "DNT: 1\n"
                         "Accept-Language: en-US,en;q=0.8\n\n";
        char* code2 = concatinate("GET /main/download_pokemon?code=", state->uuid);
        char* download = concatinate(code2, "&slot=");

        if (timeout == 0)
        {
            state->loggedIn = 0;
            state->uuid = "Lost connection!"; 
            return 0;
        }
        else if (upDown == 2)
    {
    int iterations;
    for (iterations = slot; iterations < 1200; iterations++)
    {
        printf("downloading box %i, slot %i...\n", iterations/30 + 1, (iterations%30)+1);        
        char buffer[6];
        sprintf(buffer, "%d", iterations);
        char* download_w_slot = concatinate(download, buffer);
        char* full_strings = concatinate(download_w_slot, request);
        write(sock_id,full_strings,strlen(full_strings));
        char* message = (char*)malloc(36000);
        read(sock_id,message,36000);
        char *last_newline = (char*)malloc(36000);
        last_newline = strrchr(message, '\n');        
        char *last_line = (char*)malloc(36000);
        if (last_newline!=NULL && strlen(last_newline) > 1)
        {
            last_line = last_newline+1;
        }
        else
        {
            last_line = NULL;
        }
        if ((last_line == NULL)||(strlen(last_line) < 464))
        {
            internet_access(2, iterations, state, dest, timeout-1);
            iterations = 1200;
        }
        else
        {
            int i;
            u8 final[232];
            memset(final, 0, 232);
            char part[3] = "00";
            part[2] = 0;
            for (i = 0; i < 232; i++)
            {
                memcpy(part, &last_line[i*2], 2);
                unsigned int num;
                sscanf(part, "%x", &num);
                final[i] = (u8)num;
            }
            u8 	enc[232];
            memset(enc, 0, 232);
            u32 offs = state->pch->game ? 0x33000 : 0x22600;

            s32 rewritechk(u8 *dec);
            rewritechk(final); //rewrite the pokemon's checksum, otherwise bad egg
            encryptPokemon(final, enc);
            memcpy(state->pch->save + offs + 232 * iterations, enc, 232);
        }
    }  
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 1;
    } else
    {
        char* concatinate(char*, char*);
        char* code1 = concatinate("GET /main/upload_pokemon?code=", state->uuid);
        char* code3 = concatinate("GET /main/get_four?code=", state->uuid);
        char* upload = concatinate(code1, "&slot=");
        char buf[6];
        sprintf(buf, "%d", slot);
        char* full_string;
        if (upDown == 1)
        {
            int m;
            for (m = slot; m < 1200; m++)
            {
        printf("uploading box %i, slot %i...\n", m/30 + 1, (m%30)+1);        
                char bufs[6];
                sprintf(bufs, "%d", m);
                char* upload_w_slot = concatinate(upload, bufs);
                char* upload_w_data = concatinate(upload_w_slot, "&data=");
            u8 	tmp[232];
            u32 offs = state->pch->game ? 0x33000 : 0x22600;
            memcpy(tmp, state->pch->save + offs + 232 * m, 232);
            u8 	dst[232];
            decryptPokemon(tmp, dst);
            int i;
            char* buf_str = (char*) malloc (2*232 + 1);
            char* buf_ptr = buf_str;
            for (i = 0; i < 232; i++)
            {
              buf_ptr += sprintf(buf_ptr, "%02X", dst[i]);
            }
            char* upload_w_stuff = concatinate(upload_w_data, buf_str);
            full_string = concatinate(upload_w_stuff, request);
            write(sock_id,full_string,strlen(full_string));
            char* message = (char*)malloc(36000);
        read(sock_id,message,36000);
        char *last_newline = (char*)malloc(36000);
        last_newline = strrchr(message, '\n');        
        char *last_line = (char*)malloc(36000);
        if (last_newline==NULL)
        {
            internet_access(1, m, state, dest, timeout-1);
            m = 1200;
        }
            }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            return 1;
        }
        else if (upDown == 3)
        {
            char* part1 = concatinate("GET /main/login?user=", state->login);
            char* part2 = concatinate(part1, "&pass=");
            char* part3 = concatinate(part2, state->password);
            char* part4;
            if (state->reg == 1)
            {
                part4 = concatinate(part3,"&reg=t");
            }
            else
            {
                part4 = part3;
            }
            full_string = concatinate(part4, request);
        }
        else if (upDown == 4)
        {
            full_string = concatinate(code3, request);
        }
	write(sock_id,full_string,strlen(full_string));
        u8 do4(int sock_id, u8 upDown, int slot, t_stinf *state, u8 *dest);
        return do4(sock_id, upDown, slot, state, dest);
    }
	
}

u8 do4(int sock_id, u8 upDown, int slot, t_stinf *state, u8 *dest)
{
        char* message = (char*)malloc(36000);
	read(sock_id,message,36000);
        char split = '\n';
        char *last_newline = strrchr(message, split);
        char *last_line = last_newline+1;
        
        u8 do5(char *message, u8 upDown, int slot, t_stinf *state, u8 *dest);
        return do5(last_line, upDown, slot, state, dest);
    
}

u8 do5(char *message, u8 upDown, int slot, t_stinf *state, u8 *dest)
{
        if (upDown == 3)
        {
            char* uuid = concatinate("","00000000-0000-0000-0000-000000000000");
            if (message!=NULL && strlen(message)>30)
            {
            strncpy(uuid, message, 36);
            state->loggedIn = 1;
            state->uuid = uuid;                
               internet_access(2, 930, state, dest, 50);
            }
            else
            {
                state->loggedIn = 0;
                state->uuid = "Invalid credentials.";
            }
        }
        return 1;
}

//load a pokemon from a given slot in the save to the 'dest' array
s32	loadPokemon(t_stinf *state, u16 slot, u8 *dest)
{

//    u8 success = 0;
//    if (slot > 929)
//    {
//        success = internet_access(2, slot, state, dest);
//    }
//    if ((success == 1)||(slot < 930))
//    {
      u8 	tmp[232];
      u32 	offs = state->pch->game ? 0x33000 : 0x22600;

      memcpy(tmp, state->pch->save + offs + 232 * slot, 232);
      decryptPokemon(tmp, dest);         
//    }


  return 0;
}

s32 	rewritechk(u8 *dec)
{
  u16 	chk = 0;

  for (int i = 8; i < 232; i += 2)
    chk += *(u16 *)(dec + i);
  memcpy(dec + 6, &chk, 2);
  return 0;
}

//save a pokemon from the 'src' array to a given slot in the save
s32	savePokemon(t_stinf *state, u16 slot, u8 *src)
{

  u8 	enc[232];
  u32 	offs = state->pch->game ? 0x33000 : 0x22600;

  rewritechk(src); //rewrite the pokemon's checksum, otherwise bad egg
  encryptPokemon(src, enc);
  
  memcpy(state->pch->save + offs + 232 * slot, enc, 232);
  
  return 0;
}

//switch to a given state
s32	switchState(t_stinf *state, struct s_UIState newst)
{
  state->curState = newst;
  state->curState.initf(state);
  return (0);
}

//Main loop : Executes the current state's functions
//initf : 'init' function
//dispf : 'display' function
//inputf : 'input' function
s32 	startLoop(struct s_pchex *pch)
{
  t_stinf state;

  state.pch = pch;
  //Default state settings
  state.pkmSlot = 0;
  state.login = "";
  state.password = "";
  state.uuid = "0";
  state.reg = 0;
  state.loggedIn = 0;
  state.cont = 1;
  state.inState = 1;
  state.empty = 0;

  //First state is pokemon slot selection
  state.curState = pkmSelectState;
  state.curState.initf(&state);
  memset(&state.cpy, 0, sizeof(state.cpy));

  //main loop
  while (state.cont > 0 && aptMainLoop())
  {
    hidScanInput();
    state.kPressed = hidKeysDown();
    state.curState.dispf(&state);
    state.curState.inputf(&state);

    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
  }
  if (state.cont == -1)
    return 1;
  return 0;
}
