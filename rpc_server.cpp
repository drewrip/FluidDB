#include <iostream>
#include "rpc/server.h"
#include "FluidDB.h"
#include <nlohmann/json.hpp>

using namespace std;
const string Liq::ext = ".liq";
const string Liq::dir = "data/";

void foo() {
	cout << "foo was called!" << std::endl;
}
Boat boat;

void fin(){
	boat.close();
}
int main(int argc, char *argv[]) {
	// Creating a server that listens on port 8080
	rpc::server srv(8080);
	srv.bind("getboat", [](string liqname, string boatname){
		boat.open(liqname, boatname);
		return "Repository Opened.";
	});

	srv.bind("getboatbyindex", [](int index, string newname){
		return boat.getboatbyindex(index, newname);
	});

	srv.bind("getnumberboats", [](string liqname){
		return Liq::allBoats(liqname).size();
	});

	srv.bind("makeboat", [](string liqname, string boatname, string data){
		boat.make(liqname, boatname, data);
		return "Boat Created.";
	});

	srv.bind("makeliq", [](string liqname){
		Liq::makeLiq(liqname);
		return "Created liq.";
	});

	srv.bind("removeboat", [](string liqname, string boatname){
		Liq::rmBoat(liqname, boatname);
		return "Removed boat";
	});

	srv.bind("removeliq", [](string liqname){
		Liq::rmLiq(liqname);
		return "Removed liq.";
	});

	srv.bind("append", [](string key, string pair){
		boat.append(key, pair);
		return "Database appended";
	});

	srv.bind("removedata", [](string pathtoremove){
		boat.removedata(pathtoremove);
		return "Data Removed";
	});

	srv.bind("changedata", [](string pathtopointer, string newdata){
		boat.changedata(pathtopointer, newdata);
		return "Data Altered";
	});

	srv.bind("close", &fin);

	srv.run();

	return 0;
}