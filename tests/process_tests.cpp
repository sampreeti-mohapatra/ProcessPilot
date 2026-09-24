#include "../src/process/process_manager.hpp"
#include <cassert>
#include <iostream>

int main() {
    ProcessManager manager;

    assert(!manager.isRunning());
    assert(manager.start("sleep 2"));
    assert(manager.isRunning());
    assert(manager.getPid() > 0);
    assert(manager.stop());

    std::cout << "Process tests passed.\n";
    return 0;
}
