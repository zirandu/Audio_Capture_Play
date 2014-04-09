#include <stdio.h>
#include "wavein.h"
#include "waveout.h"

#pragma comment(lib,"winmm.lib")

FILE *fp_pcm;

wavein  wave_in;
waveout wave_out;

int main()
{
	if(fp_pcm = fopen("fp_pcm.pcm","ab+"))
		puts("open the file successed.\n");
	else
		puts("open the file failued.\n");

	wave_in.start();
	wave_out.start();
	while(1)
	{
		Sleep(1);
	}

}


void CALLBACK waveInProc(HWAVEIN hwi, 
						 UINT uMsg, 
						 DWORD_PTR dwInstance,
						 DWORD_PTR dwParam1,
						 DWORD_PTR dwParam2)
{
	LPWAVEHDR pwh = (LPWAVEHDR)dwParam1;

	static int capnum = 0;  

    if( WIM_DATA == uMsg )
	{
		fwrite(pwh->lpData, sizeof(char), pwh->dwBytesRecorded, fp_pcm); //´æ´¢ÎªpcmÎÄ¼þ
		printf("cap %d \n",capnum++);
		wave_out.input((unsigned char*)pwh->lpData);

		waveInAddBuffer(hwi, pwh, sizeof(WAVEHDR));
	}
}

void CALLBACK waveOutProc(HWAVEOUT hwo,
						  UINT uMsg,
						  DWORD dwInstance,
						  DWORD dwParam1,
						  DWORD dwParam2)
{
	 static int outnum = 0;
	 if(uMsg == WOM_DONE)
	 {
	    printf("out %d \n",outnum++);
		WAVEHDR* p_wavehdr = (WAVEHDR *) dwParam1;
		waveout* p_wvo = (waveout *) dwInstance;
		p_wvo->m_buf_free.push_back((char *) p_wavehdr);
	}
}