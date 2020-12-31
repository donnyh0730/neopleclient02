#pragma once
#include <string>
using namespace std;
class AdressInfo
{
public:
	AdressInfo() = delete;
	AdressInfo(const string&& Inname, const string&& InPhone);

	string getName();
	string getPhoneNumber();
protected:
	int id;
	string name;
	string phone;
	

private :

};