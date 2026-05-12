#include <iostream>
#include <string>
#include <algorithm>
#include "Graph1.h"

using namespace std;


template <class Vertex, class Distance = double>
Vertex furthest_hospital( Graph<Vertex, Distance>& g)
{
    std::unordered_map<Vertex, std::vector<std::pair<Vertex, Distance> > > incident;
    auto vertices = g.vertices();

    for (const auto& v : vertices)
        incident[v] = {};

    for (const auto& from : vertices)
    {
        for (const auto& e : g.edges(from))
        {
            incident[from].push_back({ e.target, e.weight });
            incident[e.target].push_back({ from, e.weight });
        }
    }
    
    std::unordered_map<Vertex, Distance> avg_dist;
    for (const auto& [v, edges] : incident)
    {
        if (edges.empty())
            throw std::invalid_argument("Graph is not connected (isolated vertex)");

        Distance sum = Distance();
        for (const auto& [_, w] : edges)
            sum += w;

        avg_dist[v] = sum / edges.size();
    }

    auto max_it = std::max_element(avg_dist.begin(), avg_dist.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    return max_it->first;
}


int main()
{
    Graph<std::string, double> g;
    g.add_edge("A", "B", 4);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "C", 1);
    g.add_edge("C", "D", 5);
    g.add_edge("D", "B", 3);
    g.add_edge("D", "E", 5);
    g.add_edge("D", "F", 7);

    auto path = g.shortest_path("A", "F");
    for (auto& e : path)
        cout << e.target << "(" << e.weight << ") ";

    cout << endl;
    cout << furthest_hospital(g);
    cout << endl;
    g.print();
    
    return 0;
}
