#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <exception>
#include <vector>
#include <memory>
#include <queue>
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <cstdlib>
#include <unordered_map>


template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex target;
        Distance weight;

        Edge(const Vertex& t, Distance w) : target(t), weight(w) {}

        bool operator==(const Edge& other) const {
            return target == other.target && weight == other.weight;
        }
    };
private:
    std::unordered_map<Vertex, std::vector<Edge> > adj;
public:
    bool has_vertex(const Vertex& v) const
    {
        return adj.contains(v);
    }

    bool add_vertex(const Vertex& v)
    {
        if (has_vertex(v)) return false;
        adj.insert({v, std::vector<Edge>()});
        return true;
    }

    bool remove_vertex(const Vertex& v)
    {
        if (!has_vertex(v)) return false;

        for (auto& vert : adj)
        {
            for (auto& it : vert.second)
            {
                if (it.target == v)
                {
                    vert.second.erase(std::find(vert.second.begin(), vert.second.end(), it));
                }
            }
        }
        adj.erase(v);
        return true;
    }

    std::vector<Vertex> vertices() const
    {
        std::vector<Vertex> vert;
        for (auto& it : adj)
        {
            vert.push_back(it.first);
        }
        return vert;
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d)
    {
        add_vertex(from);
        add_vertex(to);
        adj[from].push_back(Edge(to, d));
    }

    bool remove_edge(const Vertex& from, const Vertex& to)
    {
        if (!has_vertex(from) || !has_vertex(to))
        {
            return false;
        }
        bool t = false;
        for (auto& it : adj[from])
        {
            if (it.target == to)
            {
                adj[from].erase(std::find(adj[from].begin(), adj[from].end(), it));
                t = true;
            }
        }
        return t;
    }

    bool remove_edge(const Edge& e)
    {
        bool t = false;
        for (auto& vert : adj)
        {
            for (auto& it : vert.second)
            {
                if (*it == e)
                {
                    vert.second.erase(std::find(vert.second.begin(), vert.second.end(), it));
                    t = true;
                }
            }
        }
        return t;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const
    {
        if (!has_vertex(from) || !has_vertex(to))
        {
            return false;
        }
        for (auto& it : adj[from])
        {
            if (it.target == to)
            {
                return true;
            }
        }
        return false;
    }
    bool has_edge(const Edge& e) const
    {
        for (auto& vert : adj)
        {
            for (auto& it : vert.second)
            {
                if (*it == e)
                {
                    return true;
                }
            }
        }
        return false;
    }

    std::vector<Edge> edges(const Vertex& vertex)
    {
        if (!adj.contains(vertex))
        {
            return std::vector<Edge>();
        }
        return adj[vertex];
    }


    size_t order() const
    {
        return adj.size();
    }
    size_t degree(const Vertex& v) const
    {
        size_t result = 0;
        if (!has_vertex(v))
        {
            return 0;
        }
        for (auto& vert : adj)
        {
            if (vert.first == v)
            {
                result += vert.second.size();
                continue;
            }
            for (auto& it : vert.second)
            {
                if (it.target == v)
                {
                    result++;
                }
            }
        }
        return result;
    }
    bool is_connected() const
    {
        if (adj.size() < 2)
        {
            return true;
        }
        for (auto& vert : adj)
        {
            std::vector<Vertex> visited = walk(vert.first, [](const Vertex& v) { });
            if (visited.size() != adj.size())
            {
                return false;
            }
        }
        return true;
    }

    std::vector<Vertex> walk(const Vertex& start_vertex,
        std::function<void(const Vertex&)> action) const
    {
        std::unordered_map<Vertex, bool> visited;
        std::queue<Vertex> q;
        std::vector<Vertex> res;
        for (auto& vert : adj)
        {
            visited.insert({ vert.first, false });
        }
        q.push(start_vertex);
        while (!q.empty())
        {
            auto vert = q.front();
            q.pop();
            visited[vert] = true;
            action(vert);
            res.push_back(vert);
            for (auto& it : adj.at(vert))
            {
                if (visited[it.target] == false)
                {
                    q.push(it.target);
                    visited[it.target] = true;
                }
            }
        }
        return res;
    }

    std::unordered_map<Vertex, Distance> bellman_ford(const Vertex& from) const {
        const Distance INF = std::numeric_limits<Distance>::infinity();
        std::unordered_map<Vertex, Distance> dist;
        for (const auto& p : adj) dist[p.first] = INF;
        if (!dist.count(from)) return dist;
        dist[from] = Distance();

        size_t V = order();
        for (size_t i = 0; i < V - 1; ++i) {
            bool updated = false;
            for (const auto& [u, edges] : adj) {
                if (dist[u] == INF) continue;
                for (const Edge& e : edges) {
                    if (dist[u] + e.weight < dist[e.target]) {
                        dist[e.target] = dist[u] + e.weight;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }
        for (const auto& [u, edges] : adj) {
            if (dist[u] == INF) continue;
            for (const Edge& e : edges) {
                if (dist[u] + e.weight < dist[e.target])
                    throw std::runtime_error("Negative cycle in graph");
            }
        }
        return dist;
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        auto dist = bellman_ford(from);
        if (dist.find(to) == dist.end() || dist[to] == std::numeric_limits<Distance>::infinity())
            return {};

        std::vector<Edge> path;
        Vertex cur = to;
        while (cur != from) {
            bool found = false;
            for (const auto& [u, edges] : adj) {
                for (const Edge& e : edges) {
                    if (e.target == cur && dist[u] + e.weight == dist[cur]) {
                        path.emplace_back(cur, e.weight);
                        cur = u;
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (!found) return {};
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    void export_to_json(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        file << "{\n  \"vertices\": [";
        std::vector<Vertex> verts = vertices();
        for (size_t i = 0; i < verts.size(); ++i) {
            file << "\"" << verts[i] << "\"";
            if (i + 1 < verts.size()) file << ", ";
        }
        file << "],\n  \"edges\": [\n";

        bool first_edge = true;
        for (const auto& [from, edges] : adj) {
            for (const Edge& e : edges) {
                if (!first_edge) file << ",\n";
                first_edge = false;
                file << "    {\"from\": \"" << from << "\", \"to\": \"" << e.target
                    << "\", \"weight\": " << e.weight << "}";
            }
        }
        file << "\n  ]\n}\n";
        file.close();
    }

    void print() const {
        const std::string json_file = "graph_temp.json";
        export_to_json(json_file);

        std::string cmd = "python -c \"import subprocess, sys; sys.path.append('.'); "
            "import visualize; visualize.show_graph('" + json_file + "')\"";
        int ret = std::system(cmd.c_str());
        if (ret != 0) {
            throw std::runtime_error("Something went wrong in visualizing");
        }
    }

};
#endif
