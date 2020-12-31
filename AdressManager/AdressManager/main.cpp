
#include <iostream>
#include <fstream>
#include <string>
#include "json/json.h"

using namespace std;
using namespace Json;

int main()
{
	std::ofstream json_file;
	json_file.open("Json_data.json");

	Json::Value Adress;
	
	Adress["ID"] = 1;
	Adress["NAME"] = "ÇÑµ¿¿õ";

	StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "	";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	writer->write(Adress, &cout);
	writer->write(Adress, &json_file);

	json_file.close();
	
	Json::Value root;
	root["id"] = "Luna";
	root["name"] = "Silver";
	root["age"] = 19;
	root["hasCar"] = false;

	Json::Value items;
	items.append("nootbook");
	items.append("ipadmini2");
	items.append("iphone5s");
	root["items"] = items;

	Json::Value friends;
	Json::Value tom;
	tom["name"] = "Tom";
	tom["age"] = 21;
	friends.append(tom);

	tom["name"] = "Tomy";
	tom["age"] = 24;
	
	friends.append(tom);
	root["friends"] = friends;


	writer->write(root, &cout);
	
	return 0;
}