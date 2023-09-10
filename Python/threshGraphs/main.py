import networkx as nx
import random
import time
import matplotlib.pyplot as plt

def THRESHOLD(G):
    while G.edges():  # while the edge set is nonempty
        # Delete all isolated vertices
        isolated_vertices = [v for v in G.nodes() if G.degree(v) == 0]
        G.remove_nodes_from(isolated_vertices)

        # Check if there is a vertex x adjacent to all remaining vertices
        remaining_vertices = list(G.nodes())
        x = remaining_vertices[0]  # Pick the first remaining vertex as x
        is_adjacent_to_all = all(G.has_edge(x, v) for v in remaining_vertices[1:])

        if is_adjacent_to_all:
            G.remove_node(x)
        else:
            return False

    return True


def generate_random_graph(n, max_edges):
    G = nx.Graph()
    nodes = list(range(n))
    G.add_nodes_from(nodes)

    num_edges = random.randint(0, max_edges)

    while G.number_of_edges() < num_edges:
        u, v = random.sample(nodes, 2)
        G.add_edge(u, v)

    return G


def test_algorithm(n, max_edges, num_graphs):
    total_execution_time = 0
    threshold_count = 0

    for _ in range(num_graphs):
        G = generate_random_graph(n, max_edges)

        start_time = time.time()

        is_threshold = THRESHOLD(G)
        if is_threshold:
            threshold_count += 1

        end_time = time.time()
        execution_time = end_time - start_time

        total_execution_time += execution_time

    average_execution_time = total_execution_time / num_graphs
    threshold_percentage = (threshold_count / num_graphs) * 100

    return average_execution_time, threshold_percentage


# Vary the number of vertices and measure average execution time and threshold percentage
num_vertices = list(range(10, 500, 10))  # Example: Varying number of vertices from 10 to 1000 in steps of 10
num_graphs = 30  # Number of graphs to generate for each number of vertices
average_execution_times = []
threshold_percentages = []

for n in num_vertices:
    average_execution_time, threshold_percentage = test_algorithm(n, n - 1, num_graphs)
    average_execution_times.append(average_execution_time)
    threshold_percentages.append(threshold_percentage)

# Plot the average execution times
plt.plot(num_vertices, average_execution_times)
plt.ylabel("Average Execution Time (seconds)")
plt.xlabel("Number of Vertices")
plt.title("Algorithm Speed vs. Number of Vertices")
plt.show()

# Plot the threshold percentages
plt.plot(num_vertices, threshold_percentages)
plt.ylabel("Threshold Percentage")
plt.xlabel("Number of Vertices")
plt.title("Threshold Graph Percentage vs. Number of Vertices")
plt.show()
