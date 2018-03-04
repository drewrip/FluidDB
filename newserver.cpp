#include <iostream>
#include "rpc/server.h"
#include "FluidDB.h"

using namespace std;

void foo() {
	cout << "foo was called!" << std::endl;
}

int main(int argc, char *argv[]) {
	// Creating a server that listens on port 8080
	rpc::server srv(8080);
	Boat boat;
	json j;
	srv.bind("getboat", [](string liqname, string boatname){
		return boat.open(liqname, boatname).dump();
	});

	srv.bind("getboatbyindex", [](string newname, string index){
		return boat.getboatbyindex(index, newname);
	});

	srv.bind("getnumberboats", [](string liqname){
		return Liq::allBoats(liqname).size();
	});

	srv.bind("makeboat", [](string liqname, string boatname, string data){
		boat.makeboat(liqname, boatname, data);
		return "Boat Created."
	});

	srv.bind("makeliq", [](string liqname){
		Liq::makeLiq(liqname);
		return "Created liq";
	});

	srv.bind("removeboat", [](string liqname, string boatname){
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
		boat.removeddata(pathtoremove);
		return "Data Removed";
	});

	srv.bind("changedata", [](string pathtopointer, string newdata){
		boat.changedata(pathtopointer, newdata);
		return "Data Altered";
	});

	srv.close("close"){
		boat.close();
		return "FluidDB Closed."
	}

	srv.run();

	return 0;
}