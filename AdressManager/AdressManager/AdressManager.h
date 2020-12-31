#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "json/json.h"
#include "AdressInfo.h"
using namespace std;

class AdressManager
{
public:
	AdressManager();

	~AdressManager();

	void DisplayMenu(int index = 0);
	void InsertData(const string& name = "비어있음", const string& phone = "비어있음");
	void DeleteDataByName(const string& name);
	void DeleteDataByPhoneNumber(const string& phone);
	void DeleteDataByIndex(int id);
	
	void FindDataByName(const string& name);
	void FindDataByPhoneNumber(const string& phone);
	void SaveData();
	void LoadData();
	

protected:

private:
	string str_menu;
	vector<char> points;
	vector<AdressInfo> Infos;
};



