#include "System.h"
#include <Windows.h>

int main()
{
	setlocale(NULL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//User A;

	/*A.setLogin("USER");
	A.setPassword("En!asdo44");
	A.setEmail("afniesf@gmail.com");
	A.setBirth(Date(1,1,2005));
	A.showInfo();
	A.toBin();*/

	/*A.setLogin("USER"); //1)
	A.frBin();			  //2)
	A.showInfo();		  //3)*/

	//if (A.signIn())
	//{
	//	A.showInfo();
	//}

	//====================================================================================================

	int menu1, menu2;
	char name[50] = "";
	char password[50] = "";
	System admin;
	User somebody;

	
	do
	{
		cout << "\n1. ���� ��� ������ � ��������.";
		cout << "\n2. ���� ��� ������ �� ����� ���������.";
		cout << "\n0. ��������� �����.\n�����: ";
		cin >> menu1;

		switch (menu1)
		{
		case 1:
			do
			{
				cout << "\n1. ����� ������������.";
				cout << "\n2. ������� ������ �������������.";
				cout << "\n3. ������������, ������� ����� �� ������������ ������ ���������.";
				cout << "\n4. ������� ������������ � ���� ������.";
				cout << "\n0. ��������� �����.\n�����: ";
				cin >> menu2;
				switch (menu2)
				{
				case 1:
					admin.showUser();
					break;

				case 2:
					admin.showAllUsers();
					break;

				case 3:
					admin.showUsersWhoHaventLoggedLongTime();
					break;

				case 4:
					admin.deleteUsersData();
					break;

				default: if (menu2 > 2 && menu2 != 0 || menu2 < 0) cout << "������� ������ ����� ����.\n\n"; break;
				}

			} while (menu2 != 0);

			break;

		case 2: //�������
			do
			{
				cout << "\n1. �����������.";
				cout << "\n2. ���������� ����������� � ���� � �������.";
				cout << "\n3. �������� ������ ������.";
				cout << "\n0. ��������� �����.\n�����: ";
				cin >> menu2;

				switch (menu2)
				{
				case 1:
					somebody.signUp();
					break;

				case 2:
					if (somebody.signIn())
					{
						somebody.showInfo();
						somebody.congratulateMe();
					}
					break;

				case 3:
					if (somebody.signIn())
					{
						somebody.changeMyInfo();
					}
					break;

				default: if (menu2 > 3 && menu2 != 0 || menu2 < 0) cout << "������� ������ ����� ����.\n\n"; break;
				}

			} while (menu2 != 0);

			break;

		default: if (menu1 > 2 && menu1 != 0 || menu1 < 0) cout << "������� ������ ����� ����.\n\n"; break;
		}
	} while (menu1 != 0);
	


	//somebody.setLogin("Abcd");
	//somebody.setEmail("bab@gmail.com");
	//somebody.setPassword("Babab!123");
	//somebody.setBirth(Date(1, 2, 1990));
	//somebody.codePassword();	
	//somebody.showInfo();
	//somebody.toBin();

	//somebody.setLogin("Abcd");
	//somebody.frBin();
	//somebody.decodePassword();
	//somebody.showInfo();

	return 0;
}