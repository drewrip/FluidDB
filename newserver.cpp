#include <iostream>
#include "rpc/server.h"

using namespace std;

void foo() {
	cout << "foo was called!" << std::endl;
}

int main(int argc, char *argv[]) {
	// Creating a server that listens on port 8080
	rpc::server srv(8080);

	srv.bind("getboat", [](string liqname, string boatname){
		return "boat gotten";
	});

	srv.bind("getboatbyindex", [](string liqname, string index){
		return "boat gotten by index";
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

	srv.bind("adddata", [](string liqname, string boatname, string jData){
		return "Database altered";
	});

	srv.bind("removedata", [](string liqname, string boatname, string jData){
		return "Data Removed";
	});

	srv.bind("changedata", [](string liqname, string boatname, string jData){
		return "Data Changed";
	});
	// Run the server loop.
	srv.run();

	return 0;
}