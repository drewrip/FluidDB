#include <iostream>
#include "rpc/client.h"
#include <string>
#include <nlohmann/json.hpp>
#include <vector>


using namespace std;

const string rpccalls[] = {"getboat", "getboatbyindex", "getnumberboats", "makeboat", "makeliq", "removeboat", "removeliq", "adddata", "removedata", "changedata"};

int main(int argc, char * argv[]){
	int port = 8080;
	string addr = "127.0.0.1";
	std::vector<string> args;
	for(int i = 1; i < argc; i++){
		string currarg = argv[i];
		for(string s : rpccalls){
			if(argv[i] == s){
				for(int n = i; n < argc; n++){
					args.push_back(argv[n]);
				}
			}

		}
		// Testing for arg flags
		if(currarg == "-p"){
			port = atoi(argv[i+1]);
		}
		else if(currarg == "-a"){
			addr = argv[i+1];
		}
	}
    // Creating a client that connects to the localhost on port 8080
    rpc::client client(addr, port);

    // Calling a function with paramters and converting the result to int
    string result = client.call(args[0], args).as<string>();
    std::cout << result << std::endl;
    return 0;
}