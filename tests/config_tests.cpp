#include "../src/config/config_parser.hpp"
#include <cassert>
#include <iostream>

int main() {
    ConfigParser parser;

    assert(parser.load("../configs/demo.service"));
    assert(parser.get("Name") == "demo");
    assert(parser.get("Command") == "/bin/sleep 60");

    std::cout << "Config tests passed.\n";
    return 0;
}
