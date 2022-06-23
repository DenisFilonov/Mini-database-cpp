#include "User.h"

bool User::isLoginAvail(const char* _login)
{
	FILE* fp = nullptr;
	fopen_s(&fp, login, "rb");
	if (fp != NULL)
	{
		fclose(fp);
		return false;
	}
	else return true;
}

bool User::isValidEmail(const char* _email)
{
	int size = strlen(_email);
	int amountOfAt = 0;
	int posAt = -1;
	for (int i = 0; i < size; i++)
	{
		if (_email[i] == '@')
		{
			posAt = i;
			amountOfAt++;
		}
	}

	if (amountOfAt!=1)
	{
		return false;
	}
	else if (posAt < 1 || posAt > size - 3)
	{
		return false;
	}

	int posDot = -1;
	int amountOfDots = 0;
	for (int i = posAt + 1; i < size; i++)
	{
		if (_email[i] == '.')
		{
			posDot = i;
			amountOfDots++;
		}
	}
	
	if (amountOfDots < 1)
	{
		return false;
	}
	else if (!isalpha(_email[posDot - 1]) || !isalpha(_email[posDot + 1]))
	{
		return false;
	}
	return true;
}

bool User::isValidDate(Date d)
{
	if (d.getMonth() == 1 || d.getMonth() == 3 || d.getMonth() == 5 || d.getMonth() == 7 || d.getMonth() == 8 || d.getMonth() == 10 || d.getMonth() == 12)
	{
		if (d.getDay() >= 1 && d.getDay() <= 31)
		{
			return true;
		}
		else return false;
	}
	else if (d.getMonth() == 4 || d.getMonth() == 6 || d.getMonth() == 9 || d.getMonth() == 11)
	{
		if (d.getDay() >= 1 && d.getDay() <= 30)
		{
			return true;
		}
		else return false;
	}
	else if (d.getMonth() == 2)
	{
		if (d.isLeapYear() && d.getDay() >= 1 && d.getDay() <= 29)
		{
			return true;
		}
		else if (!d.isLeapYear() && d.getDay() >= 1 && d.getDay() <= 28)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

int User::calcСomplexity(const char* _password) const
{
	int size = strlen(_password) + 1;
	if (size < 6) return 0; // чисто символы без \0
	bool isDigit = false;
	bool isUpper = false;
	bool isLower = false;
	bool isSymbol = false;

	for (int i = 0; i < size; i++)
	{
		if (isdigit(_password[i]))
		{
			isDigit = true;
		}
		else if (isupper(_password[i]))
		{
			isUpper = true;
		}
		else if (islower(_password[i]))
		{
			isLower = true;
		}
		else isSymbol = true;
	}

	return isDigit + isUpper + isLower + isSymbol;
}

User::User(const char* _login, const char* _password, const char* _email)
{
	int size = strlen(_login) + 1;
	login = new char[size];
	strcpy_s(login, size, _login);

	size = strlen(_password) + 1;
	password = new char[size];
	strcpy_s(password, size, _password);

	size = strlen(_email) + 1;
	email = new char[size];
	strcpy_s(email, size, _email);
}

User::~User()
{
	if (login != NULL) delete[] login;
	if (password != NULL) delete[] password;
	if (email != NULL) delete[] email;
}

void User::showInfo()
{
	cout << "\nЛогин: " << login;
	cout << "\nЭлектронная почта: " << email;
	cout << "\nПароль: " << password;
	cout << "\nУровень сложности пароля: " << calcСomplexity(password);
	cout << "\nДата рождения: "; birth.showDate();
	cout << endl << endl;
}

bool User::signIn()
{
	char tmplogin[50] = "";
	char tmppassword[50] = "";
	cout << "\nВведите логин: ";
	cin >> tmplogin;
	if (isLoginAvail(tmplogin) == 0)
	{
		cout << "\nДанный пользователь не зарегистрирован.\n\n";
	}
	else
	{
		if (login != NULL) delete[] login;
		int size = strlen(tmplogin) + 1;
		login = new char[size];
		strcpy_s(login, size, tmplogin);

		this->decodePassword();
		this->frBin();

		cout << "\nВведите пароль: ";
		cin >> tmppassword;
		decodePassword();
		if (strcmp(tmppassword, password) == 0)
		{
			cout << "\nДобро пожаловать!\n\n";
			return true;
		}
		else
		{
			cout << "\nНеверный пароль!\n\n";
			return false;
		}
	}
}

void User::signUp()
{
	char login[50] = "", password[50] = "", email[50] = "";
	int day = 10, month = 10, year = 1991;
	int pass;

	cout << "\n===============================================";
	cout << "\n\tРегистрация нового пользователя: ";
	cout << "\nВведите логин для учётной записи: ";
	cin >> login;
	if (isLoginAvail(login))
	{
		cout << "\nВведите пароль для учётной записи: ";
		cin >> password;
		pass = calcСomplexity(password);
		if (pass >= 2)
		{
			cout << "\nВведите электронную почту для учётной записи: ";
			cin >> email;
			if (isValidEmail(email))
			{
				cout << "\nВведите через пробел вашу дату рождения ДД ММ ГГГГ:";
				cin >> day >> month >> year;
				if (isValidDate(Date (day,month,year)))
				{
					User somebody(login, password, email);
					somebody.setBirth(Date(day, month, year));
					somebody.codePassword();
					somebody.toBin();
					somebody.showInfo();
					cout << "\nРегистрация кабинета пройдена успешно!\n\n";
				}
				else
				{
					cout << "\nНеверно ввведена дата рождения! Введите её корректно и повторите процедуру регистрации.\n\n";
				}
			}
			else
			{
				cout << "\nНеверно введён адрес электронной почты! Введите его корректно и повторите процедуру регистрации.\n\n";
			}
		}
		else
		{
			cout << "\nНенадёждый пароль! Попробуйте другой и повторите процедуру регистрации.\n\n";
		}
	}
	else
	{
		cout << "\nДанный логин уже используется! Попробуйте другой и повторите процедуру регистрации.\n\n";
	}
	cout << "\n===============================================\n\n";

}

void User::codePassword()
{
	Date tmpdate = getBirth();

	int size = strlen(password) + 1;
	char* codedpass = new char[size];

	for (int i = 0; i < size; i++)
	{
		codedpass[i] = int(password[i]) + tmpdate.getMonth();
	}
	codedpass[size - 1] = '\0';
	password = codedpass;
}

void User::decodePassword()
{
	Date tmpdate = getBirth();

	int size = strlen(password) + 1;
	char* codedpass = new char[size];

	for (int i = 0; i < size; i++)
	{
		codedpass[i] = int(password[i]) - tmpdate.getMonth();
	}
	codedpass[size - 1] = '\0';
	password = codedpass;
}

void User::setLogin(const char* _login)
{
	if (strcmp(_login, "NewUser") == 0)
	{
		cout << "\nОшибка изменения логина!\n\n";
	}
	else
	{
		/*if (!isLoginAvail(_login)) cout << "\nТакой логин уже существует!\n\n";
		else*/
		delete[] login;
		int size = strlen(_login) + 1;
		login = new char[size];
		strcpy_s(login, size, _login);
		cout << "\nЛогин установлен!\n\n";
	}
	
}

void User::setPassword(const char* _password)
{
	if (calcСomplexity(_password) > 1)
	{
		delete[] password;
		int size = strlen(_password) + 1;
		password = new char[size];
		strcpy_s(password, size, _password);
	}
	else cout << "\nНенадёжный пароль! Попробуйте снова.\n\n";
}

void User::setEmail(const char* _email)
{
	if (!isValidEmail(_email))
	{
		cout << "\nНеверный адрес электронной почты! Попробуйте другой.\n\n";
	}
	else
	{
		delete[] email;
		int size = strlen(_email) + 1;
		email = new char[size];
		strcpy_s(email, size, _email);
		cout << "\nАдрес электронной почты сохранён!\n\n";
	}
}

void User::changeMyInfo()
{
	int menu;
	char str[50] = "";
	Date tmp;

	do
	{
		cout << "\n\tИзменение личных данных:\n";
		cout << "\n1. Изменить электронную почту.";
		cout << "\n2. Изменить пароль.";
		cout << "\n3. Изменить дату рождения.";
		cout << "\n0. Вернуться назад.\nВыбор: ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			cout << "\nНовая электронная почта: ";
			cin >> str;
			setEmail(str);
			break;

		case 2:
			cout << "\nНовый пароль: ";
			cin >> str;
			setPassword(str);
			break;

		case 3:
			tmp.setDate();
			setBirth(tmp);
			break;

		default: if (menu > 2 && menu != 0 || menu < 0) cout << "Неверно выбран пункт меню.\n\n"; break;
		}

	} while (menu != 0);
}

void User::congratulateMe()
{
	Date today;
	today.getNowDate();
	if (today.getDay() == birth.getDay() && today.getMonth() == birth.getMonth())
	{
		system("start congr.jpg");
	}
}

const char* User::getLogin() const
{
	return login;
}

const char* User::getPassword() const
{
	return password;
}

const char* User::getEmail() const
{
	return email;
}

void User::setBirth(Date d)
{
	birth = d; //присвоения
}

Date User::getBirth() const
{
	return birth;
}

void User::toBin() const
{
	FILE* fp = nullptr;
	fopen_s(&fp, login, "wb");
	if (fp != NULL)
	{
		int size = strlen(login) + 1;
		fwrite(&size, sizeof(int), 1, fp);
		fwrite(login, sizeof(char), size, fp);

		size = strlen(password) + 1;
		fwrite(&size, sizeof(int), 1, fp);
		fwrite(password, sizeof(char), size, fp);

		size = strlen(email) + 1;
		fwrite(&size, sizeof(int), 1, fp);
		fwrite(email, sizeof(char), size, fp);

		fwrite(&birth, sizeof(Date), 1, fp);

		fclose(fp);
		cout << "\nФайл успешно сохранён!\n\n";
	}
	else cout << "\nОшибка открытия файла!\n\n";
}

void User::frBin()
{
	FILE* fp = nullptr;
	fopen_s(&fp, login, "rb");
	if (fp != NULL)
	{
		int size = 0;
		fread(&size, sizeof(int), 1, fp);
		login = new char[size];
		fread(login, sizeof(char), size, fp);

		fread(&size, sizeof(int), 1, fp);
		password = new char[size];
		fread(password, sizeof(char), size, fp);

		fread(&size, sizeof(int), 1, fp);
		email = new char[size];
		fread(email, sizeof(char), size, fp);

		fread(&birth, sizeof(Date), 1, fp);

		fclose(fp);
		cout << "\nФайл успешно загружен!\n\n";
	}
	else cout << "\nОшибка открытия файла!\n\n";
}
