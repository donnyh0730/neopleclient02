#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "json/json.h"
#include "AdressInfo.h"
using namespace std;

enum Command
{
	Insert,
	Delete,
	Display,
	Search,
	Save,
	Load,
	Quit,
	MAX
};

class AdressManager
{
public:
	AdressManager();

	~AdressManager();

	void ReceivCommand(const int index);

	void DisplayMenu(const int index = 0);
	void DisplayAll();
	
	void InsertData();
	void InsertData(const string& name, const string& phone ,const string& desc);
	
	void DeleteData();
	bool DeleteDataByName(const string& name);

	
	void FindData();

	AdressInfo* FindDataByName(const string& name);
	
	void SaveData();
	void SaveCurrentData();
	void SaveAndLoadData();
	void LoadData(const string& filename = "");

	string currentFilename;
protected:
	vector<char> points;
	vector<AdressInfo> Infos;//출력과 저장을 위한 리스트
	map<string, AdressInfo> Infomap_namekey;//이름으로 찾기 검색을 위한 맵.
private:
	void ClearData();
	
};



