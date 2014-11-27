//---------------------------------------------------------------------------

#ifndef ProcessInfoUH
#define ProcessInfoUH
#include "Windows.h"
void    ProcessInfoCreate(DWORD PID);
void    Terminate(DWORD PID);
void    VirtualMemCreate(void);
long    PageKol(DWORD ProcessHandle);
boolean CheckProcessForErrors(DWORD ProcessHandle);
boolean CheckProcessPresenceInSystem(DWORD ProcessHandle);
LPVOID  GetLPVOID(void);
//---------------------------------------------------------------------------
#endif
 