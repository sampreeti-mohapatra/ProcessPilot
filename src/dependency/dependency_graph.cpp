#include "dependency_graph.hpp"

void DependencyGraph::addDependency(const std::string& service,
                                     const std::string& dependency) {
    graph[service].push_back(dependency);
}

bool DependencyGraph::hasDependency(const std::string& service,
                                     const std::string& dependency) const {
    auto it = graph.find(service);
    if (it == graph.end()) {
        return false;
    }

    for (const auto& item : it->second) {
        if (item == dependency) {
            return true;
        }
    }

    return false;
}

std::vector<std::string> DependencyGraph::getDependencies(
    const std::string& service) const {
    auto it = graph.find(service);
    if (it == graph.end()) {
        return {};
    }

    return it->second;
}
