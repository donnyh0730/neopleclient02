#include "AdressInfo.h"
#include <string>
using namespace std;
AdressInfo::AdressInfo(const string&& Inname, const string&& InPhone)
{
	name = Inname;
	phone = InPhone;
}

string AdressInfo::getName()
{
	return name;
}

string AdressInfo::getPhoneNumber()
{
	return phone;
}
