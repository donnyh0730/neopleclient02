#include "AdressInfo.h"
#include <string>
#include <iostream>
using namespace std;
AdressInfo::AdressInfo(const int&& id, const string&& Inname, const string&& InPhone, const string&& Desc)
{
	this->id = id;
	name = Inname;
	phone = InPhone;
	description = Desc;
}

AdressInfo::AdressInfo()
{
}

int AdressInfo::getId()
{
	return id;
}

string AdressInfo::getName()
{
	return name;
}

string AdressInfo::getPhoneNumber()
{
	return phone;
}

std::string AdressInfo::getDescription()
{
	return description;
}

void AdressInfo::setId(int index)
{
	id = index;
}

void AdressInfo::setName(const string& _name)
{
	name = _name;
}

void AdressInfo::setPhoneNumber(const string& _number)
{
	phone = _number;
}

void AdressInfo::setDescription(const string& _desc)
{
	description = _desc;
}

void AdressInfo::DisplayInfo()
{
	cout << "이름: " << name << " 전화번호 : "<<phone<<" 설명: "<<description<<endl;
}

AdressInfo* AdressInfo::get()
{
	return this;
}
