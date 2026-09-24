#ifndef DEPENDENCY_GRAPH_HPP
#define DEPENDENCY_GRAPH_HPP

#include <string>
#include <map>
#include <vector>

class DependencyGraph {
public:
    void addDependency(const std::string& service,
                       const std::string& dependency);

    bool hasDependency(const std::string& service,
                       const std::string& dependency) const;

    std::vector<std::string> getDependencies(
        const std::string& service) const;

private:
    std::map<std::string, std::vector<std::string>> graph;
};

#endif
