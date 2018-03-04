#include "rpc/server.h"
#include <iostream>

int main(){
	rpc::server srv(8080);

    // Binding a lambda function to the name "add".
    srv.bind("add", [](int a, int b) {
        return a + b;
    });

    // Run the server loop.
    srv.run();
	return 0;
}