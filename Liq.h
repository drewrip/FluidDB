#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <cstdio>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
using std::string;

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
		fileObj<<"{"<<endl<<jName<<endl;
		fileObj<<hexify(jData)<<endl;
		fileObj<<"}"<<endl;
		fileObj.close();
	}
	
	static string readFile(string lName, string jName){
		string liqData = "";
		if(std::ifstream is{dir+lName+ext, std::ios::binary | std::ios::ate}) {
			auto size = is.tellg();
			std::string str(size, '\0');
			is.seekg(0);
			if(is.read(&str[0], size)){
				liqData+=str;
			}
		}
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

	static string get(string lName, int index){
		string liqData = "";
		if(std::ifstream is{dir+lName+ext, std::ios::binary | std::ios::ate}) {
			auto size = is.tellg();
			std::string str(size, '\0');
			is.seekg(0);
			if(is.read(&str[0], size)){
				liqData+=str;
			}
		}
		char temp;
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
			charNum++;
			temp = liqData[charNum];
		}
		charNum++;
		return stringify(parseBoat(liqData,charNum));
	}

	static void rmLiq(string lName){
		remove((dir+lName+ext).c_str());
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