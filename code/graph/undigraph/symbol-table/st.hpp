#include "../base/undirected-graph.hpp"
#include <map>
#include <string>

class SymbolGraph
{
public:
    SymbolGraph(int size);
    ~SymbolGraph() { delete[] str_arr; };
    bool contains(std::string key) { return str_map.find(key) != str_map.end(); };
    int index(std::string key) { return str_map[key]; };
    std::string name(int v) { return str_arr[v]; };
    Graph G() { return _G; };

private:
    std::map<std::string, int> str_map;
    std::string *str_arr;
    Graph _G;
};

SymbolGraph::SymbolGraph(int size) : str_arr(new std::string[size]), _G(size) {}
