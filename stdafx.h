#ifndef stdafx_h
#define stdafx_h

#include <windows.h>
#include <mmsystem.h>
#include <list>
using namespace std;
#define BUFFER_SIZE 16
#define BLOCK_SIZE   1280+sizeof(WAVEHDR)
#define FRAGMENT_SIZE 320
#define FRAGMENT_NUM 32 

#endif