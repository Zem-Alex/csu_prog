import networkx as nx
import matplotlib.pyplot as plt

def certifying_split(graph):
    # Implementation of Certifying-Split algorithm
    # You need to replace this with your own implementation
    K = set()
    I = set()
    for node in graph.nodes():
        if node % 2 == 0:
            K.add(node)
        else:
            I.add(node)
    return K, I

def certifying_threshold(graph):
    K, I = certifying_split(graph)

    # Non-decreasing degree ordering α
    alpha = sorted(graph.nodes(), key=lambda v: graph.degree(v))

    # Nested neighborhood ordering β
    beta = [v for v in alpha if v in I]

    # Delete isolated vertices
    graph.remove_nodes_from(list(nx.isolates(graph)))

    # Initialize variables
    threshold = True
    i = len(alpha) - 1

    while i >= 0:
        vi = alpha[i]

        if vi in graph.nodes():
            if graph.degree(vi) == len(graph) - 1:
                graph.remove_node(vi)
                for x in graph.neighbors(vi):
                    graph[x] = list(set(graph[x]) - {vi})
                    if graph.degree(x) == 0:
                        graph.remove_node(x)
            else:
                threshold = False
                break

        i -= 1

    if threshold:
        return True, beta

    # Cleanup remaining vertices
    while True:
        removed = False
        for v in K.copy():
            if not any(graph.neighbors(v)) or all(graph.has_edge(v, u) for u in I):
                graph.remove_node(v)
                K.remove(v)
                removed = True

        for v in I.copy():
            if all(graph.has_edge(v, u) for u in K):
                graph.remove_node(v)
                I.remove(v)
                removed = True

        if not removed:
            break

    # Choose a vertex v of I with the highest degree
    v = max(I, key=lambda x: graph.degree(x))

    # Find a non-neighbor y of v in K
    y = next(x for x in K if not graph.has_edge(v, x))

    # Find a neighbor z of y in I
    z = next(x for x in I if graph.has_edge(y, x))

    # Find a vertex w ∈ K that is a neighbor of v and a non-neighbor of z
    w = next(x for x in K if graph.has_edge(v, x) and not graph.has_edge(z, x))

    return False, [v, w, y, z]

# Example usage
G = nx.Graph()
G.add_nodes_from([1, 2, 3, 4])
G.add_edges_from([(1, 2), (2, 4), (4, 3), (3, 1)])

# Visualize the graph
nx.draw(G, with_labels=True, node_color='lightblue', node_size=500, font_size=12, font_color='black', edge_color='gray')

# Display the graph
plt.show()

result, order = certifying_threshold(G)
if result:
    print("Graph is threshold with order:", order)
else:
    print("Graph is not threshold, induced P4:", order)

