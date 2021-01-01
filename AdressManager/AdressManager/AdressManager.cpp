#include "AdressManager.h"
#include "AdressInfo.h"
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
	Infos.clear();
	points.clear();
}

void AdressManager::ReceivCommand(const int index)
{
	switch (index)
	{
	case Command::Insert:
		InsertData();
		break;
	case Command::Delete:
		DeleteData();
		break;
	case Command::Display:
		DisplayAll();
		break;
	case Command::Search:
		FindData();
		break;	
	case Command::Save:
		SaveData();
		break;
	case Command::Load:
		LoadData();
		break;
	}
}

void AdressManager::DisplayMenu(const int index)
{
	system("cls");
	for (unsigned int i = 0; i < points.size(); i++)
	{
		if (i == index)
		{
			points[i] = '*';
		}
		else
			points[i] = ' ';
	}
	cout << "메뉴를 선택해주세요. 위아래 방향키로 메뉴를 이동할 수 있습니다.\n\n";

	cout << points[0] << "  1. 주소 등록 : 주소록에 개인의 주소를 등록합니다.\n" << endl
		<< points[1] << "  2. 주소 삭제 : 주소록에서 선택한 항목을 삭제합니다.\n" << endl
		<< points[2] << "  3. 전체 보기 : 주소록의 명단을 확인합니다.\n" << endl		
		<< points[3] << "  4. 검색 : 주소록의 내용을 검색할 수 있습니다.\n" << endl
		<< points[4] << "  5. 저장 : 주소록의 내용을 현상태로 저장합니다.\n" << endl
		<< points[5] << "  6. 불러오기 : 주소록의 내용을 저장하고 새로운 파일만들거나 불러옵니다.\n" << endl
		<< "  종료하려면 'q'를 입력하세요." << endl;
}

void AdressManager::DisplayAll()
{
	for (int i =0; i< Infos.size();++i)
	{
		Infos[i].DisplayInfo();
	}
}

void AdressManager::InsertData()
{
	string name, phone, desc;
	cout << "데이터를 입력하여 추가합니다.\n";
	
	cout << "이름을 입력해주세요. :";
	cin >> name;
	cout << "\n전화번호를 입력해주세요. :";
	cin >> phone;
	cout << "\n설명을 입력해주세요. (비워두셔도 됩니다.)";
	getline(cin, desc);//cin에 남은 공백을 clear한다.
	getline(cin, desc);
	InsertData(name, phone, desc);
	
}

void AdressManager::InsertData(const string& name /*= "비어있음"*/, const string& phone /*= "비어있음"*/, const string& desc)
{
	Infos.emplace_back((int)Infos.size(),std::move(name), std::move(phone), std::move(desc));
	Infomap_namekey.insert(make_pair(name, Infos.back()));
	Infos.back().DisplayInfo();
	SaveData();//추가삭제작업시 자동저장 수행.
	cout << "의 정보가 추가되었습니다.\n";
}

void AdressManager::DeleteData()
{
	cout << "지울 정보의 이름을 입력하세요.";
	string data;
	cin >> data;
	if (DeleteDataByName(data))
	{
		cout << "데이터를 성공적으로 지웠습니다.";
		return;
	}
}

bool AdressManager::DeleteDataByName(const string& name)
{
	//일단 map에서 O(1)시간에 삭제할 아이템이 있는지 없는지를 먼저 알면 없는 데이터에 대한 순회는 하지않아도 된다.
	if (Infomap_namekey.find(name) == Infomap_namekey.end())
	{
		cout << "일치하는 데이터가 없습니다.";
		return false;
	}	
	else
	{
		AdressInfo* info = Infomap_namekey[name].get();
		bool erased = false;
		for (int i = 0; i < Infos.size(); ++i)
		{
			if (info->getId() == Infos[i].getId()&& !erased)//문자열 비교보다는 int형 비교가 훨씬 빠르다.
			{
				Infos.erase(Infos.begin() + i);
				erased = true;
			}
			if (erased)
			{
				info[i].setId(i - 1);//지워지고난 다음에는 인덱스 값을 1씩 빼준다.
			}

		}
		return false;
	}
}


void AdressManager::FindData()
{
	cout << "찾을 이름을 입력하세요.";
	string data;
	cin >> data;
	
	if (FindDataByName(data) != nullptr)
	{
		FindDataByName(data)->DisplayInfo();
	}
	else
	{
		cout << "일치하는 데이터가 없습니다.";
	}
}

AdressInfo* AdressManager::FindDataByName(const string& name)
{
	if (Infomap_namekey.find(name) == Infomap_namekey.end())
		return nullptr;
	else return Infomap_namekey[name].get();
}

void AdressManager::SaveData()
{
	std::ofstream json_file;
	json_file.open(currentFilename);

	StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "	";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	Json::Value Object;
	for (unsigned int i = 0; i < Infos.size(); ++i)
	{
		Json::Value item;
		item["id"] = i;
		item["name"] = Infos[i].getName();
		item["phone"] = Infos[i].getPhoneNumber();
		item["description"] = Infos[i].getDescription();
		Object.append(item);
	}
	writer->write(Object, &json_file);
	json_file.close();
}

void AdressManager::LoadData(const string& filename)
{
	currentFilename = filename;
	if (filename.empty())
		currentFilename = "json_data.json";

	ifstream json_dir(currentFilename);
	CharReaderBuilder builder;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;
	Value jsondata;
	bool check = parseFromStream(builder, json_dir, &jsondata, &errs);
	
	if (check)
	{
		for (unsigned int i = 0; i < jsondata["items"].size(); ++i)
		{
			Value &val = jsondata["items"][i];			
			Infos.emplace_back(
				std::move(i),
				val["name"].asString(), 
				val["phone"].asString(),
				val["description"].asString());
		}
	}
	else
		cout << "데이터 로드 실패";

	if (!Infos.empty())
	{
		for (int i =0; i< Infos.size();++i)
		{
			string namekey = Infos[i].getName();
			string phonenumberkey = Infos[i].getPhoneNumber();
			Infomap_namekey.insert(make_pair(namekey,Infos[i]));
		}
	}
	
}

void AdressManager::SaveAndLoadData()
{
	SaveData();
	string str;
	cout << "불러올 파일 이름을 입력하세요.(새로운 파일이름 입력시 새로운 카테고리의 데이터파일이 만들어 집니다.) : ";
	cin >> str;
	LoadData(str);
}

