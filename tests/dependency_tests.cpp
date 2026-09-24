#include "../src/dependency/dependency_graph.hpp"
#include <cassert>
#include <iostream>

int main() {
    DependencyGraph graph;

    graph.addDependency("web", "database");

    assert(graph.hasDependency("web", "database"));
    assert(!graph.hasDependency("web", "cache"));

    std::cout << "Dependency tests passed.\n";
    return 0;
}
