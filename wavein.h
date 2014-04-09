#ifndef wavein_h
#define wavein_h

#include "stdafx.h"

class wavein
{
	WAVEFORMATEX wave_format;
	HWAVEIN h_wavein;
	WAVEHDR wh[FRAGMENT_NUM];
public:
	char m_buf[BUFFER_SIZE][BLOCK_SIZE];
	wavein();
	~wavein();
	void start();
	bool stop();
};

void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

#endif
