#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <exception>
#include <vector>
#include <memory>
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>
#include "Unordered_Map.h"


template<typename Vertex, typename Distance = double>
class Graph {
private:
    UnorderedMap<Vertex, std::vector<Edge> > adj;
public:
    struct Edge {
        Vertex target;
        Distance weight;

        Edge(const Vertex& t, Distance w) : target(t), weight(w) {}

        bool operator==(const Edge& other) const {
            return target == other.target && weight == other.weight;
        }
    };


    bool has_vertex(const Vertex& v) const
    {
        return adj.contains(v);
    }

    bool add_vertex(const Vertex& v)
    {
        if (has_vertex(v)) return false;
        adj.insert(v, std::vector<Edge>());
        return true;
    }

    bool remove_vertex(const Vertex& v)
    {
        if (!has_vertex(v)) return false;

        // Удаляем все рёбра, которые ссылаются на v
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            auto& edges = it->second;
            edges.erase(std::remove_if(edges.begin(), edges.end(),
                [&v](const Edge& e) { return e.target == v; }),
                edges.end());
        }
        // Удаляем саму вершину
        adj.erase(v);
        return true;
    }

    std::vector<Vertex> vertices() const;


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d)
    {
        adj[from].push_back()
    }
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); //c учетом расстояния
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e) const; //c учетом расстояния в Edge

    std::vector<Edge> edges(const Vertex& vertex)
    {
        return adj[vertex];
    }


    size_t order() const; //порядок 
    size_t degree(const Vertex& v) const; //степень вершины
    bool is_connected() const; //является ли граф сильно связным


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex,
        std::function<void(const Vertex&)> action)const;
    void print()// Сделайте красивую визуализацию графа с помощью LLM. Можете красивый вывод в консоле сделать, можете сохранять как картинки. Пожалуйста, не поленитесь и сделайте визуализацию индивидуально.


#endif
