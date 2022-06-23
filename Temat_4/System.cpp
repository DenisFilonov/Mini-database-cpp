#include "System.h"
#include <cstdlib>
#include <Windows.h>

void System::showUser()
{
	char str[50] = "";
	cout << "\nЛогин пользователя: ";
	cin >> str;
	WIN32_FIND_DATA fileobj;
	HANDLE hf = FindFirstFile(str, &fileobj);
	if (hf == INVALID_HANDLE_VALUE) cout << "\nПользователь не обнаружен!\n\n";
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
	WIN32_FIND_DATA fileobj;//переменная структуры, которая хранит информацию о файле или папке
	HANDLE hf = FindFirstFile("*", &fileobj); // многобайтная кодировка, настройки Проекта
	User somebody;
	int i = 0;
	if (hf == INVALID_HANDLE_VALUE) cout << "Файл не обнаружен\n";
	else
	{
		cout << "\n=========================================================\n";
		cout << "\tСписок пользователей в системе:\n";
		do
		{
			if (!(fileobj.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (strstr(fileobj.cFileName,".") == 0 && strcmp(fileobj.cFileName,"Debug")!=0)
				{
					cout << ++i << ") Пользователь - " << fileobj.cFileName << endl;
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

	if (hf == INVALID_HANDLE_VALUE) cout << "\nПользователи не обнаружены!\n\n";
	else
	{
		do
		{
			if (fileobj.dwFileAttributes)
			{
				cout << "\nИмя пользователя: " << fileobj.cFileName;

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
	cout << "\nЛогин пользователя: ";
	cin >> str;
	WIN32_FIND_DATA fileobj;
	HANDLE hf = FindFirstFile(str, &fileobj);
	if (hf == INVALID_HANDLE_VALUE) cout << "\nПользователь не обнаружен!\n\n";
	else
	{
		strcpy_s(command, 256, "del ");//del 
		strcat_s(command, 256, str);//del nickname
		system(command);
		cout << "\nФайл удалён.\n\n";
	}
	FindClose(hf);
}
