#include "wavein.h"

#define BUFFER_SIZE (8000*16*1/8*1)
#define FRAGMENT_SIZE 320
#define FRAGMENT_NUM 32

wavein::wavein()
{
	wave_format.wFormatTag = WAVE_FORMAT_PCM;
	wave_format.nChannels = 1;
	wave_format.nSamplesPerSec = 8000;
	wave_format.nAvgBytesPerSec = 8000*16*1/8;
	wave_format.nBlockAlign = 2;
	wave_format.wBitsPerSample = 16;  
	wave_format.cbSize = 0;
	h_wavein = NULL;
}

wavein::~wavein()
{
	stop();
}

void wavein::start()
{
	MMRESULT nRet = waveInOpen(&h_wavein,WAVE_MAPPER, &wave_format, (DWORD_PTR) waveInProc, 0, CALLBACK_FUNCTION);
    if(nRet != MMSYSERR_NOERROR)
		printf("false");
	WAVEINCAPS wic;
	waveInGetDevCaps((UINT_PTR)h_wavein, &wic, sizeof(WAVEINCAPS));

	for(int i = 0; i < FRAGMENT_NUM; i++)
	{
		wh[i].lpData = new char[FRAGMENT_SIZE];  
        wh[i].dwBufferLength = FRAGMENT_SIZE;  
        wh[i].dwBytesRecorded = 0;  
        wh[i].dwUser = NULL;  
        wh[i].dwFlags = 0;  
        wh[i].dwLoops = 1;  
        wh[i].lpNext = NULL;  
        wh[i].reserved = 0;  
        //将建立好的wHdr1做为备用
        waveInPrepareHeader(h_wavein, &wh[i], sizeof(WAVEHDR));  
        //将两个wHdr添加到waveIn中去
		waveInAddBuffer(h_wavein, &wh[i], sizeof(WAVEHDR)); 
	}
	waveInStart(h_wavein);
}

bool wavein::stop()
{
	waveInStop(h_wavein);
	waveInReset(h_wavein);
	for(int i=0;i < FRAGMENT_NUM; i++)
	{
		waveInUnprepareHeader(h_wavein,&wh[i],sizeof(WAVEHDR));
	}
	waveInClose(h_wavein);
	return true;
}

