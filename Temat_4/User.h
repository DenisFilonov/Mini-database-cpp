#pragma once
#include "Date.h"

class User
{
	char* login;
	char* password;
	char* email;
	Date birth;

	bool isLoginAvail(const char* _login);
	bool isValidEmail(const char* _email);
	bool isValidDate(Date d); //���������
	int calc�omplexity(const char* _password)const;

public:
	User(const char* _login = "NewUser", const char* _password = "12345", const char* _email = "");
	~User();
	void showInfo();
	bool signIn(); //���� � ������ �������
	void signUp(); //�����������

	void codePassword();
	void decodePassword();

	void setLogin(const char* _login);
	void setPassword(const char* _password);
	void setEmail(const char* _email);

	void changeMyInfo();
	void congratulateMe();

	const char* getLogin() const;
	const char* getPassword() const;
	const char* getEmail() const;

	void setBirth(Date d); //����������� ����������� ������ Date
	Date getBirth()const;


	void toBin()const;
	void frBin();
};

