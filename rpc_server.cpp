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
	string addr = "127.0.0.1";

	for(int i = 1; i < argc; i++){
		string currarg = argv[i];

		// Testing for arg flags
		if(currarg == "-p"){
			port = atoi(argv[i+1]);
		}
		else if(currarg == "-a"){
			addr = argv[i+1];
		}
		else{
		}
	}
	rpc::server srv(port);
	cout << "Starting FluidDB RPC server on " << addr << ":" << port << std::endl;


    srv.bind("getboat", [](string liqname, string boatname){
    	ostringstream details;
    	fstream data;
 		data.open("samples.json");
 		json j;
 		data >> j;
 		string jstr = j.dump(4);
        return jstr;
    });

    srv.bind("getboatbyindex", [](string liqname, int index){
    	ostringstream details;
    	details << liqname << "[" << index << "]";
    	return details.str();
    });

    srv.bind("getnumberboats", [](string liqname){
    	return "There are 4 databases in this liq";
    });

    srv.bind("makeboat", [](string liqname, string boatname){
    	return "Boat created!";
    });

    srv.bind("makeliq", [](string liqname){
    	return "Created liq";
    });

    srv.bind("removeboat", [](string liqname, string boatname){

    	return "Removed boat";
    });

    srv.bind("removeliq", [](string liqname){

    	return "Removed liq";
    });

    srv.bind("adddata", [](string liqname, string boatname, string jsondata){

    	return "Database altered";
    });

    srv.bind("removedata", [](string liqname, string boatname, string jsondata){

    	return "Data Removed";
    });

    srv.bind("changedata", [](string liqname, string boatname, string jsondata){

    	return "Data Changed";
    });


    // Run the server loop.
    srv.run();
	return 0;
}