#ifndef waveout_h
#define waveout_h

#include "stdafx.h"

class waveout  
{
	WAVEFORMATEX wave_format;
	HWAVEOUT h_waveout;
public:
	char m_buf[BUFFER_SIZE][BLOCK_SIZE];
	list<char*>m_buf_free;
	waveout();
	~waveout();
	bool start();
	bool stop();
	int input(unsigned char* buf);
	bool inlineis_start(){return (h_waveout != NULL);}
};

void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2);

#endif