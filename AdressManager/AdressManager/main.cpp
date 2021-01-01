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
#define CNT_MENU 7
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
	////writer->write(Object, &cout);
	//writer->write(Object, &json_file);
	//json_file.close();
	AdressManager admanager;
	char ch;
	cout << "기본 데이터를 보려면 1 을입력하세요.\n";
	cout << "데이터를 파일명으로 로드하려면 2 를입력하세요.\n";
	while (true)
	{
		cin >> ch;
		if (ch == '1')
		{
			admanager.LoadData();
			break;
		}
		else if (ch == '2')
		{
			string filename;
			cout << "새로운 파일 이름을 입력하면 새로운 파일이 생성되어 작업하게됩니다." << endl;
			cin >> filename;
			admanager.LoadData(filename);//기존 데이터를 읽어 옵니다.
			break;
		}
		else
		{
			cout << "1 또는 2중에 입력해 주세요."<<endl;
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
		if (c == 13)//엔터키 입력받았을때.
		{
			admanager.ReceivCommand(index);
		}
		if (c == 'q')
		{
			cout << "현재정보를 저장하고 종료합니다.";
			admanager.SaveData();
			return 0;
		}

	}
	return 0;
}