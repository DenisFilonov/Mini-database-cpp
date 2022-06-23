#include "System.h"
#include <cstdlib>
#include <Windows.h>

void System::showUser()
{
	char str[50] = "";
	cout << "\n����� ������������: ";
	cin >> str;
	WIN32_FIND_DATA fileobj;
	HANDLE hf = FindFirstFile(str, &fileobj);
	if (hf == INVALID_HANDLE_VALUE) cout << "\n������������ �� ���������!\n\n";
	else
	{
		User somebody;
		somebody.setLogin(str);		  //1)
		somebody.frBin();			  //2)
		somebody.showInfo();		  //3)
	}
	FindClose(hf);
}

void System::showAllUsers()
{
	WIN32_FIND_DATA fileobj;//���������� ���������, ������� ������ ���������� � ����� ��� �����
	HANDLE hf = FindFirstFile("*", &fileobj); // ������������ ���������, ��������� �������
	User somebody;
	int i = 0;
	if (hf == INVALID_HANDLE_VALUE) cout << "���� �� ���������\n";
	else
	{
		cout << "\n=========================================================\n";
		cout << "\t������ ������������� � �������:\n";
		do
		{
			if (!(fileobj.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (strstr(fileobj.cFileName,".") == 0 && strcmp(fileobj.cFileName,"Debug")!=0)
				{
					cout << ++i << ") ������������ - " << fileobj.cFileName << endl;
					somebody.setLogin(fileobj.cFileName);
				}
			}
		} while (FindNextFile(hf, &fileobj));
		cout << "=========================================================\n\n";
		FindClose(hf);
	}
}

void System::showUsersWhoHaventLoggedLongTime()
{
	WIN32_FIND_DATA fileobj;
	HANDLE hf = FindFirstFile("*", &fileobj);
	_SYSTEMTIME date;

	if (hf == INVALID_HANDLE_VALUE) cout << "\n������������ �� ����������!\n\n";
	else
	{
		do
		{
			if (fileobj.dwFileAttributes)
			{
				cout << "\n��� ������������: " << fileobj.cFileName;

				FileTimeToSystemTime(&fileobj.ftLastAccessTime, &date);
				cout << date.wDay << "-" << date.wMonth << "-" << date.wYear << endl;
			}
		} while (FindNextFile(hf, &fileobj));
		FindClose(hf);
	}
}

void System::deleteUsersData()
{
	char str[50] = "";
	char command[256] = "";
	cout << "\n����� ������������: ";
	cin >> str;
	WIN32_FIND_DATA fileobj;
	HANDLE hf = FindFirstFile(str, &fileobj);
	if (hf == INVALID_HANDLE_VALUE) cout << "\n������������ �� ���������!\n\n";
	else
	{
		strcpy_s(command, 256, "del ");//del 
		strcat_s(command, 256, str);//del nickname
		system(command);
		cout << "\n���� �����.\n\n";
	}
	FindClose(hf);
}
