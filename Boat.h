#include <iostream>
#include "FluidDB.h"
#include <string>
#include <nlohmann/json.hpp>

#ifndef BOAT_H
#define BOAT_H

using nlohmann::json_pointer;
using json = nlohmann::json;

class Boat
{
public:
	// Sets the name of the database
	void make(string liqname, string boatname, string data){
		Liq::writeFile(liqname, boatname, data);
		liqdb = liqname;
		raw = json::parse(data);
	}

	void open(string liqname, string boatname){
		cout << Liq::readFile(liqname, boatname) << std::endl;
		raw = json::parse(Liq::readFile(liqname, boatname));
		liqdb = liqname;
		boatid = boatname;
	}

	void importjson(string pathtojson, string liqname, string newboatname){
		fstream data;
		data.open(pathtojson);
		json j;
		ostringstream s;
		data >> j;
		s << j;
		make(liqname, newboatname, s.str());
		boatid = newboatname;
	}

	void changeliq(string toliq){
		liqdb = toliq;
	}

	void getboat(string nameofboat){
		raw = json::parse(Liq::readFile(liqdb, nameofboat));
		boatid = nameofboat;
	}

	void getboatbyindex(int index, string newname){
		raw = json::parse(Liq::get(liqdb, index)[1]);
		boatid = Liq::get(liqdb, index)[0];
	}

	void out(){
		cout << raw.dump(4) << endl;
	}

	string query(string pointerpath){
		json_pointer <json>pptr(pointerpath);
		return raw[pptr];
	}

	void changedata(string pointerpath, string newdata){
		json_pointer <json>pptr(pointerpath);
		raw[pptr] = newdata;
	}

	void append(string key, string pair){
		raw.emplace(key, pair);
	}

	void removedata(string pathtoremove){
		json_pointer <json>pptr([pathtoremove]);
		raw.erase(pptr);
	}

	void close(){
		Liq::writeFile(liqdb, boatid);
	}


private:
	string boatid;
	string liqdb;
	json raw;
};

#endif