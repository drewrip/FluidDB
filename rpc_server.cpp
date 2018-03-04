#include "rpc/server.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

int main(int argc, char * argv[]){

	int port = 8080;

	for(int i = 1; i < argc; i++){
		string currarg = argv[i];

		// Testing for arg flags
		if(currarg == "-p"){
			port = atoi(argv[i+1]);
		}
	}
	rpc::server srv(port);
	cout << "Starting FluidDB RPC server on port " << port << std::endl;


    srv.bind("getboat", [](string liqname, string boatname){
    	ostringstream details;
    	fstream data;
 		data.open("samples.json");
 		json j;
 		data >> j;
 		string jstr = j.dump(4);
        return jstr;
    });

    srv.bind("getboatbyindex", [](vector<string> v){
    	ostringstream details;
    	details << v[1] << "[" << stoi(v[2]) << "]";
    	return details.str();
    });

    srv.bind("getnumberboats", [](vector<string> v){
    	return "There are 4 databases in this liq";
    });

    srv.bind("makeboat", [](vector<string> v){
    	return "Boat created!";
    });

    srv.bind("makeliq", [](vector<string> v){
    	return "Created liq";
    });

    srv.bind("removeboat", [](vector<string> v){

    	return "Removed boat";
    });

    srv.bind("removeliq", [](vector<string> v){

    	return "Removed liq";
    });

    srv.bind("adddata", [](vector<string> v){

    	return "Database altered";
    });

    srv.bind("removedata", [](vector<string> v){

    	return "Data Removed";
    });

    srv.bind("changedata", [](vector<string> v){

    	return "Data Changed";
    });


    // Run the server loop.
    srv.run();
	return 0;
}