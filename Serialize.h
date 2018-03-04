#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <bitset>

using namespace std;
using std::string;

#ifndef SERIALIZE_H
#define SERIALIZE_H

class Serialize {
public:
	static void writeFile(string fName, string jData){
		struct stat st = {0};
		if(stat(dir.c_str(), &st) == -1){
			mkdir(dir.c_str(), 0700);
		}

		ofstream fileObj;
		fileObj.open(dir+fName+ext, ios::app);

		for(size_t i = 0; i<jData.size(); ++i){
			fileObj<<bitset<8>(jData.c_str()[i]) << endl;
		}
		fileObj.close();
	}
	
	static string readFile(string fName){
		string jData = "";
		string binJson = "";
		if(ifstream is{dir+fName+ext, ios::binary | ios::ate}) {
			auto size = is.tellg();
			string binData(size, '\0');
			is.seekg(0);
			if(is.read(&binData[0], size)){
				binJson+=binData;
			}
		}
		stringstream sstream(binJson);
			while(sstream.good()){
				bitset<8> bits;
				sstream >> bits;
				char c = char(bits.to_ulong());
				jData += c;
			}
		return jData;
	}
private:

	const static string dir;
	const static string ext;
};

#endif