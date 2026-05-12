#include <iostream>
#include <string>
#include "Graph1.h"

using namespace std;


int main()
{
    Graph<std::string, double> g;
    g.add_edge("A", "B", 4);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "C", 1);
    g.add_edge("C", "D", 5);
    g.add_edge("D", "B", -3);

    auto path = g.shortest_path("A", "D");
    for (auto& e : path)
        std::cout << e.target << "(" << e.weight << ") ";
    std::cout << std::endl;
    g.print();
    
    return 0;
}
