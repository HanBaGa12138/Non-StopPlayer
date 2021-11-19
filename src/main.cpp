/*
        Copyright (C) 2003-2021 AQin Lab
*/
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#include <time.h>
#include <fstream>
#include "function.h"
#pragma comment (lib, "winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma warning(disable:4996)
using namespace std;

int VolumeLevel = 100;
int music_length = 10;
int delay = 100; //�ӳ�ʱ��(ms)

void SetVolume();
void PlayMusic();

int main()
{
	//������־
	fstream file;
	file.open("Log.txt", ios::out|ios::app);
	//��ȡ����ʱ��
	char time_str[100];
	time_t current_sec = time(NULL);
	tm* current;
	current = localtime(&current_sec);
	strftime(time_str, 100, "[%Y/%m/%d %H:%M:%S]", current);
	//д����־
	strcat_s(time_str, "����ʼ����");
	file << time_str << endl;
	file.close();
	//��ʼ��������
	thread volume_t(SetVolume);
	thread play_t(PlayMusic);
	play_t.join();
	return 0;
}

void SetVolume()
{
	while (true)
	{
		int temp = CoInitialize(0);
		try
		{
			SetVolumeLevel(-2);
			SetVolumeLevel(VolumeLevel);
		}
		catch (...)
		{

		}
		CoUninitialize();
		Sleep(delay);
	}
	return;
}

void PlayMusic()
{
	while (true)
	{
		PlaySound(TEXT("audio.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Sleep(music_length * 1000);
	}
	return;
}
