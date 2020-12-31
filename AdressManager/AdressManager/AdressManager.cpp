#include "AdressManager.h"
#include "json/json.h"
#include <vector>
#include <stdlib.h>
#include <fstream>
using namespace std;
using namespace Json;

AdressManager::AdressManager()
{
	points.resize(10);


}

AdressManager::~AdressManager()
{

}

void AdressManager::DisplayMenu(int index)
{
	system("cls");
	for (int i = 0; i < points.size(); i++)
	{
		if (i == index)
		{
			points[i] = '*';
		}
		else
			points[i] = ' ';
	}
	cout << "메뉴를 선택해주세요. 위아래 방향키로 메뉴를 이동할 수 있습니다.\n";

	cout << points[0] << "  1. 주소 등록 : 주소록에 개인의 주소를 등록합니다." << endl
		<< points[1] << "  2. 주소 삭제 : 주소록에서 선택한 항목을 삭제합니다." << endl
		<< points[2] << "  3. 전체 보기 : 주소록의 명단을 확인합니다." << endl		
		<< points[3] << "  4. 검색 : 주소록의 내용을 검색할 수 있습니다." << endl;
}

void AdressManager::InsertData(const string& name, const string& phone)
{

}

void AdressManager::DeleteDataByName(const string& name)
{

}

void AdressManager::DeleteDataByPhoneNumber(const string& phone)
{

}

void AdressManager::DeleteDataByIndex(int id)
{

}

void AdressManager::FindDataByName(const string& name)
{

}

void AdressManager::FindDataByPhoneNumber(const string& phone)
{

}

void AdressManager::SaveData()
{
	std::ofstream json_file;
	json_file.open("Json_data.json");

	StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "	";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	Json::Value Object;

	for (int i = 0; i < Infos.size(); ++i)
	{
		Json::Value item;
		item["id"] = i;
		item["NAME"] = Infos[i].getName();
		item["Phone"] = Infos[i].getPhoneNumber();
		Object.append(item);
	}
	writer->write(Object, &json_file);

}

void AdressManager::LoadData()
{
	ifstream json_dir("json_data.json");
	CharReaderBuilder builder;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;
	Value jsondata;
	bool check = parseFromStream(builder, json_dir, &jsondata, &errs);
	
	if (check)
	{
		for (int i = 0; i < jsondata["items"].size(); ++i)
		{
			Value &val = jsondata["items"][i];			
			Infos.emplace_back(val["name"].asString(), val["phone"].asString());
		}
	}
	else
		cout << "데이터 로드 실패";

}
