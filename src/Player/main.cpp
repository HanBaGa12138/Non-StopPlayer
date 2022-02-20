/*
        Copyright (C) 2003-2021 AQin Lab
		Unknown Date

		This is a program will play a period of music, and you can't stop it until you start task manger or restart the computer
*/
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#include <time.h>
#include <fstream>
#include "function.h"
#pragma comment (lib, "winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#pragma warning(disable:4996)
using namespace std;

int VolumeLevel = 100;
double music_length = 0;//�ӳ�ʱ��(ms)
double delay = 0.1;
char music_path[MAX_PATH] = { 0 };
char cfg_file_name[20] = "audio_cfg.txt";

void SetVolume();
void PlayMusic();

int main()
{
	//������־
	fstream log_file;
	log_file.open("Log.txt", ios::out|ios::app);
	//��ȡ����ʱ��
	char time_str[MAX_PATH];
	time_t current_sec = time(NULL);
	tm* current;
	current = localtime(&current_sec);
	strftime(time_str, 100, "[%Y/%m/%d %H:%M:%S]", current);
	//���Ҫ���ŵ��ļ���·��
	FILE* path_cfg;
	path_cfg = fopen(cfg_file_name, "rb");
	if (path_cfg == nullptr)
	{
		fstream cfg_file;
		cfg_file.open(cfg_file_name, ios::out | ios::app);
		cfg_file << ".\\audio.wav";
		cfg_file.close();

		log_file << time_str << "Can't find configure file" << endl;
		log_file.close();
		return -1;
	}
	fread(music_path, sizeof(char), MAX_PATH, path_cfg);
	fclose(path_cfg);
	RemoveTabSymbols(music_path);
	//FILE *music_file;
	if (!fopen(music_path, "rb"))
	{
		log_file << time_str << "Can't find audio file in \"" << cfg_file_name << "\"" << endl;
		log_file.close();
		return -1;
	}
	//д����־
	strcat_s(time_str, "����ʼ����");
	log_file << time_str << endl;
	log_file.close();
	//��ȡ��Ƶ�ļ�����
	music_length = GetPlayTime(music_path);
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
		PlaySound(music_path, NULL, SND_FILENAME | SND_ASYNC);
		Sleep(music_length);
	}
	return;
}
