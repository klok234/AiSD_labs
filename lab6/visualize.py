import json
import networkx as nx
import matplotlib.pyplot as plt
import sys

def show_graph(json_file):
    # Загружаем данные
    with open(json_file, 'r') as f:
        data = json.load(f)
    
    # Создаём ориентированный граф
    G = nx.DiGraph()
    
    # Добавляем вершины
    for v in data['vertices']:
        G.add_node(v)
    
    # Добавляем рёбра с весами
    edges = []
    edge_labels = {}
    for e in data['edges']:
        G.add_edge(e['from'], e['to'], weight=e['weight'])
        edges.append((e['from'], e['to']))
        edge_labels[(e['from'], e['to'])] = str(e['weight'])
    
    # Рисуем граф
    pos = nx.spring_layout(G, seed=42, k=2)  # расположение вершин
    plt.figure(figsize=(10, 8))
    nx.draw_networkx_nodes(G, pos, node_color='lightblue', node_size=800)
    nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold')
    nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='gray', 
                           width=2, arrowstyle='->', arrowsize=20)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=10)
    
    plt.title("Визуализация графа", fontsize=16)
    plt.axis('off')
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) > 1:
        show_graph(sys.argv[1])
    else:
        print("Укажите путь к JSON файлу")