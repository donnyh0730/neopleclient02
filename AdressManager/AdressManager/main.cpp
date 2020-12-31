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
#define CNT_MENU 4
using namespace std;
using namespace Json;

int main()
{
	std::ofstream json_file;
	json_file.open("Json_data.json");

	StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "	";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	Json::Value Object;

	Json::Value item;
	
	//예시로 더미데이터를 만듭니다.
	for (int i = 0; i < 10; ++i)
	{
		item["id"] = i;
		item["name"] = "홍길동"+to_string(i);
		item["phone"] = "010-7507-0000";
		Object["items"].append(item);
	}
	//writer->write(Object, &cout);
	writer->write(Object, &json_file);
	json_file.close();

	AdressManager admanager;//주소록 매니저 클래스를 생성합니다.
	admanager.LoadData();//기존 데이터를 읽어 옵니다.
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
					index = CNT_MENU - 1;
				break;
			case RIGHT:
				index++;
				if (index > CNT_MENU - 1)
					index = 0;
				break;
			case UP:
				index--;
				if (index < 0)
					index = CNT_MENU - 1;
				break;
			case DOWN:
				index++;
				if (index > CNT_MENU - 1)
					index = 0;
				break;
			}
			admanager.DisplayMenu(index);
		}
		if (c == 13)
		{
			admanager.DisplayMenu(index);
			cout << "엔터키 입력";
		}
			

	}
	return 0;
}