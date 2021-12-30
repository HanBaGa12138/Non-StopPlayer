/*
        Copyright (C) 2003-2021 AQin Lab
        2021/12/11

        When you want to deploy "Player.exe" to a new computer,click this executable file,everyting will be done soon
*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <atlstr.h>
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")
#pragma warning(disable:4996)

CString default_path = "C:\\Non-StopPlayer";
char temp[100] = "";

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("FileCopy.exe [IconFilePath]");
        exit(0);
        return 0;
    }
    //��ȡĬ��Ŀ¼����
    std::ifstream setting_file;
    setting_file.open("setting.txt");
    setting_file.read(temp, 100);
    default_path = temp;
    //����Ŀ¼
    if (!PathFileExists(default_path))
    {
        CreateDirectory(default_path, NULL);
    }
    //�����ļ�
    CString playerFile = default_path + "\\Player.exe";
    CopyFile(TEXT("file\\Player.exe"), playerFile, false);
    CString audioFile = default_path + "\\audio.wav";
    CopyFile(TEXT("file\\audio.wav"), audioFile, false);
    CString shortcutFile = default_path + "\\ShortcutCreator.exe";
    CopyFile(TEXT("file\\ShortcutCreator.exe"), shortcutFile, false);
    CString srcIcon = argv[1];
    CString Icon_name;
    for (int i = srcIcon.GetLength() - 1; i >= 0; i--)
    {
        if (srcIcon[i] == '\\' || srcIcon[i] == '/')
        {
            for (int j = i; j < srcIcon.GetLength(); j++)
            {
                Icon_name += srcIcon[j];
            }
            break;
        }
    }
    CString iconFile = default_path + Icon_name;
    CopyFile(srcIcon, iconFile, false);
    //�����������ݷ�ʽ
    CString cmd = shortcutFile + " " + iconFile;
    char cmd_[200] = "";
    for (int k = 0; k < cmd.GetLength(); k++)
    {
        cmd_[k] = cmd[k];
    }
    system(cmd_);
    system("pause");
    return 0;
}