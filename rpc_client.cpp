#include <iostream>
#include "rpc/client.h"
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
int main() {
    // Creating a client that connects to the localhost on port 8080
    rpc::client client("127.0.0.1", 6767);

    // Calling a function with paramters and converting the result to int
    string result = client.call("getboatbyindex", "testBoi", 1).as<string>();
    std::cout << result << std::endl;
    return 0;
}