#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <cstdio>
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

using namespace std;
using json = nlohmann::json;
using std::string;
using std::vector;

#ifndef LIQ_H
#define LIQ_H

class Liq {
public:
	static void writeFile(string lName, string jName, string jData){
		struct stat st = {0};
		if(stat(dir.c_str(), &st) == -1){
			mkdir(dir.c_str(), 0700);
		}

		ofstream fileObj;
		fileObj.open(dir+lName+ext, ios::app);
		if(jName == "" && jData == ""){
			fileObj.close();
			return;
		}
		fileObj<<"{"<<endl<<jName<<endl;
		fileObj<<hexify(jData)<<endl;
		fileObj<<"}"<<endl;
		fileObj.close();
	}
	
	static string readFile(string lName, string jName){
		string liqData = readLiq(lName);
		string boat = "";
		int bLength = jName.length();
		char temp;
		string tempName = "";
		for(int i = 0; i<liqData.length(); i++){
			temp = liqData[i];
			if(temp == '{'){
				int j;
				for(j = i+2; j<=bLength+1; j++){
					tempName+=liqData[j];
				}
				if(tempName == jName){
					boat = parseBoat(liqData, j+1);
					return stringify(boat);
				}
				tempName = "";
			}

		}

		return "";
	}

	static vector<string> get(string lName, int index){
		string liqData = readLiq(lName);
		char temp;
		string boatName = "";
		int currInd = -1;
		int charNum = -1;
		while(currInd<index){
			charNum++;
			temp = liqData[charNum];
			if(temp =='{'){
				currInd++;

			}
		}
		charNum++;
		while(temp != '\n'){
			boatName+=temp;
			charNum++;
			temp = liqData[charNum];
		}
		charNum++;
		vector<string> boatVec;
		string newBoatString = "";
		for(int i = 1; i<boatName.length(); i++){
			newBoatString+=boatName[i];
		}
		boatVec.push_back(newBoatString);
		boatVec.push_back(stringify(parseBoat(liqData,charNum)));
		return boatVec;
	}

	static vector<string> allBoats(string liqName){
		vector<string> boats;
		string boatName = "";
		string liqData = readLiq(liqName);
		int liqLen = liqData.length();
		char temp;
		for(int i = 0; i<liqLen; i++){
			temp = liqData[i];
			int newI = i+2;
			if(temp=='{'){
				while(liqData[newI] != '\n'){
					boatName+=liqData[newI];
					newI++;
				}
				boats.push_back(boatName);
				boatName = "";
				i = newI;
			}
		}
		return boats;
	}

	static void rmBoat(string liqname, string boatname){
		string liqData = readLiq(liqname);
		char temp;
		string tempName = "";
		string newBoat = "";
		bool shouldParse = true;
		for(int i = 0; i<liqData.length(); i++){
			temp = liqData[i];
			if(temp == '{'){
				if(!shouldParse){
					shouldParse = true;
				}
				else{
					for(int j = i+2; j<boatname.length(); j++){
						temp = liqData[j];
						tempName+=temp;
					}
					if(temp == boatName){
						shouldParse = false;
					}
				}
			}
			if(shouldParse){
				newBoat+=temp;
			}
		}
		ofstream ofs;
		ofs.open(dir+liqname+ext, ios::trunk);
		ofs.write();
		ofs.close();
		ofs.open(dir+liqName+ext, ios::app);
		ofs<<newBoat<<endl;
	}

	static void rmLiq(string lName){
		remove((dir+lName+ext).c_str());
	}

	static void makeLiq(string liqname){
		writeFile(liqname , "", "");
	}

private:
	static string hexify(const string& input){
		static const char* const lut = "0123456789ABCDEF";
		size_t len = input.length();

		string output;
		output.reserve(2 * len);
		for (size_t i = 0; i < len; ++i){
			const unsigned char c = input[i];
			output.push_back(lut[c >> 4]);
			output.push_back(lut[c & 15]);
		}
		return output;
	}
	static string stringify(const string& input){
		static const char* const lut = "0123456789ABCDEF";
		size_t len = input.length();

		string output;
		output.reserve(len / 2);
		for (size_t i = 0; i < len; i += 2){
			char a = input[i];
			const char* p = lower_bound(lut, lut + 16, a);

			char b = input[i + 1];
			const char* q = lower_bound(lut, lut + 16, b);
			output.push_back(((p - lut) << 4) | (q - lut));
		}
		return output;
	}

	static string readLiq(string liqName){
		string liqData = "";
		if(std::ifstream is{dir+liqName+ext, std::ios::binary | std::ios::ate}) {
			auto size = is.tellg();
			std::string str(size, '\0');
			is.seekg(0);
			if(is.read(&str[0], size)){
				liqData+=str;
			}
		}
		return liqData;
	}

	static string parseBoat(string& fullString, int charNum){
		string jData = "";
		char tempChar = fullString[charNum];
		while(tempChar != '}'){
			jData+=tempChar;
			charNum++;
			tempChar = fullString[charNum];
		}
		return jData;
	}

	const static string dir;
	const static string ext;
};

#endif