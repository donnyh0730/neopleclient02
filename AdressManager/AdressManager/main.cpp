#include <iostream>
#include <fstream>
#include <string>
#include "AdressManager.h"
#include "json/json.h"
#include <conio.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

using namespace std;
using namespace Json;

int main()
{
	//std::ofstream json_file;
	//json_file.open("Json_data.json");

	//StreamWriterBuilder builder;
	//builder["commentStyle"] = "None";
	//builder["indentation"] = "	";
	//unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	//Json::Value Object;

	//Json::Value item;
	//
	////예시로 더미데이터를 만듭니다.
	//for (int i = 0; i < 5; ++i)
	//{
	//	item["id"] = i;
	//	item["name"] = "홍길동"+to_string(i);
	//	item["phone"] = "010-7507-0000";
	//	item["description"] = "더미데이터";
	//	Object["items"].append(item);
	//}
	//writer->write(Object, &cout);
	//writer->write(Object, &json_file);
	//json_file.close();
	AdressManager admanager;
	char ch;
	
	int idx = 0;
	cout << " * 1. 예시 데이터로 시작하기 \n";
	cout << "   2. 새로만들거나 데이터를 로드하기. \n";
	while (true)
	{
		char c;
		c = _getch();
		if (c == -32) {
			c = _getch();
			switch (c) {
			case LEFT:
				idx--;
				if (idx < 0)
					idx = 1;
				break;
			case RIGHT:
				idx++;
				if (idx > 1)
					idx = 0;
				break;
			case UP:
				idx--;
				if (idx < 0)
					idx = 1;
				break;
			case DOWN:
				idx++;
				if (idx > 1)
					idx = 0;
				break;
			}
		}
		system("cls");
		if (idx == 0)
		{
			cout << " * 1. 예시 데이터로 시작하기 \n";
			cout << "   2. 새로만들거나 데이터를 로드하기. \n";
		}
		else
		{
			cout << "   1. 예시 데이터로 시작하기 \n";
			cout << " * 2. 새로만들거나 데이터를 로드하기. \n";
		}

		if (c == 13 && idx == 0)
		{
			admanager.LoadData();
			break;
		}
		else if (c == 13 && idx == 1)
		{
			string filename;
			cout << "기존에 없는 이름을 입력하면 새로운 파일이 생성되어 작업하게됩니다."<<endl
				<<"기존에 있는 파일명을 입력시 해당파일을 로드합니다."<<endl
				<<"(확장자는 생략하세요.)" << endl;
			cin >> filename;
			filename += ".json";
			admanager.LoadData(filename);//기존 데이터를 읽어 옵니다.
			break;
		}
	}
	
	int index = 0;
	admanager.DisplayMenu(index);
	while (true)
	{
		char c;
			
		c = _getch();
		if (c == -32) {
			c = _getch();
			switch (c) {
			case LEFT:
				index--;
				if (index < 0)
					index = Command::MAX - 1;
				break;
			case RIGHT:
				index++;
				if (index > Command::MAX - 1)
					index = 0;
				break;
			case UP:
				index--;
				if (index < 0)
					index = Command::MAX - 1;
				break;
			case DOWN:
				index++;
				if (index > Command::MAX - 1)
					index = 0;
				break;
			}
			admanager.DisplayMenu(index);
		}
		if (c == 13 && index != 6)//엔터키 입력받았을때.
		{
			admanager.ReceivCommand(index);
		}
		if (c == 13 && index == 6)
		{
			cout << "\n현재정보를 저장하고 종료합니다.\n";
			admanager.SaveData();
			return 0;
		}

	}
	return 0;
}