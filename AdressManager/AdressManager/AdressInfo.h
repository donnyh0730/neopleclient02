#pragma once
#include <string>

using namespace std;
class AdressInfo
{
public:
	AdressInfo();
	AdressInfo(const int&& id, const string&& Inname, const string&& InPhone,const string&& Desc = "");//복사생성을 피하기위해 이동생성자 사용.
	int getId();
	string getName();
	string getPhoneNumber();
	string getDescription();

	void setId(int index);
	void setName(const string& _name);
	void setPhoneNumber(const string& _number);
	void setDescription(const string& _desc);

	void DisplayInfo();
	AdressInfo* get();
	
protected:
	int id;
	string name;
	string phone;
	string description;

};