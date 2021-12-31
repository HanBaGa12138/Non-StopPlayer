/*
        Copyright (C) 2003-2021 AQin Lab
        2021/12/11

        When you want to deploy "Player.exe" to a new computer,click this executable file,everyting will be done soon
*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <atlstr.h>
#include <io.h>
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")
#pragma warning(disable:4996)

CString default_path = "C:\\Non-StopPlayer"; //Ҫ���Ƶ����ļ�Ĭ��·��,ʵ������ʱ��Ҫ��ȡ��setting.txt��
char _src_dir[20] = "file\\"; //Ҫ���Ƶ��ļ����ļ���(�ԡ�\\����β)
char temp[200] = "";

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
    //�����ļ�Ŀ¼
    CString src_dir = _src_dir;
    intptr_t handle;
    _finddata_t data;
    strcat(_src_dir, "\\*.*");
    handle = _findfirst(_src_dir, &data); // Ѱ�ҵ�һ���ļ�

    CString dst_file;
    if (handle == -1)
    {
        std::cout << "ԴĿ¼Ϊ��" << std::endl;
        system("pause");
        exit(-1);
    }
    else
    {
        while (_findnext(handle, &data) != -1)
        {
            dst_file = default_path;
            if (strcmp(data.name, ".") == 0 || strcmp(data.name, "..") == 0)
            {
                continue;
            }
            else if (data.attrib == _A_SUBDIR)
            {
                printf("�ҵ���Ŀ¼:%s|����\n", data.name);
                continue;
            }
            else
            {
                CString file_name = data.name;
                CString t_src_file = src_dir + (CString)data.name;
                dst_file = dst_file + "\\" + file_name;
                printf("�ҵ��ļ�:%S\n���Ƶ�:%S\n", t_src_file.GetBuffer(0), dst_file.GetBuffer(0));
                CopyFile(t_src_file, dst_file, false);
            }
        }
    }

    //���������ļ�
    CString shortcutFile = default_path + "\\ShortcutCreator.exe";
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
    printf("\n�����ⲿ���򴴽���ݷ�ʽ...\n");
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