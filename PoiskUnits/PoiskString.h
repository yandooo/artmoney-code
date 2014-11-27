//---------------------------------------------------------------------------

#ifndef PoiskStringH
#define PoiskStringH
#include "Windows.h"
long PoiskString          (DWORD ProcessHandle,AnsiString BPoiskString, LPVOID VirtualMem);
long PoiskStringAgainQucly(DWORD ProcessHandle,AnsiString BPoiskString, LPVOID VirtualMem, long FindNumber);
//---------------------------------------------------------------------------
#endif
 