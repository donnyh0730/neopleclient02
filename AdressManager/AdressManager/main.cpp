/*
2. 주소록

전화번호/이름을 입력받아 관리하고 볼 수 있는 주소록 프로그램을 작성하세요.

1명의 주소록에는 최소한 이름, 전화번호를 포함해야 합니다.

키보드의 방향키와 엔터키를 이용해서 메뉴를 선택하고 이용할 수 있어야 합니다.



주소록에는 다음의 메뉴가 있어야 합니다.

-       주소 등록 : 주소록에 개인의 주소를 등록합니다.

-       주소 삭제 : 주소록에서 선택한 항목을 삭제합니다.

-       전체 보기 : 주소록의 명단을 확인합니다.

-       저장/불러오기 : 주소록에 추가삭제 작업을 했을때 자동저장, 프로그램 동작시 불러오기

-       검색 : 주소록의 내용을 검색할 수 있습니다.



그 외에 주소록의 편리 기능/추가 디테일은 자유롭게 구현하세요.

사용성이 뛰어날수록 가산점을 부여합니다.



  요구사항

   윈도우즈 콘솔 프로그램으로 작성하며, 언어는 C++로 합니다.

  미리 컴파일된 헤더는 사용하지 말아주세요.

  외부 라이브러리 사용 가능합니다.

  솔루션 및 실행 파일도 같이 첨부해 주세요.
*/
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
#define CNT_MENU 5
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
	
	
	for (int i = 0; i < 10; ++i)
	{
		item["id"] = i;
		item["name"] = "홍길동 "+to_string(i);
		item["phone"] = "010-7507-0000";
		Object["items"].append(item);
	}
	writer->write(Object, &cout);
	writer->write(Object, &json_file);
	json_file.close();

	AdressManager admanager;
	int index = 0;
	admanager.LoadData();
	while (true)
	{
		char c;
			
		admanager.DisplayMenu(index);
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
		}

	}
	return 0;
}