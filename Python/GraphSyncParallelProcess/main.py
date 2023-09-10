import networkx as nx

def is_perfect_elimination_ordering(G, alpha):
    for i in range(len(alpha)):
        v = alpha[i]
        neighbors = set(G.neighbors(v))
        if any(alpha[j] in neighbors for j in range(i + 1, len(alpha))):
            if not all(alpha[j] in neighbors for j in range(i + 1, len(alpha)) if alpha[j] not in neighbors):
                return False
    return True

def certifying_split(G):
    V = G.nodes()
    E = G.edges()

    # Compute a non-decreasing degree ordering α
    alpha = sorted(V, key=lambda v: G.degree(v))

    # Check if α is a perfect elimination ordering (peo)
    if not is_perfect_elimination_ordering(G, alpha):
        # Find a vertex vi with two neighbors vj and vk such that vjvk ∉ E and i < j < k
        for i in range(len(alpha)):
            vi = alpha[i]
            neighbors = list(G.neighbors(vi))
            for j in range(len(neighbors)):
                vj = neighbors[j]
                for k in range(j + 1, len(neighbors)):
                    vk = neighbors[k]
                    if not G.has_edge(vj, vk):
                        # Check if vj and vk have a common neighbor z with vi z ∉ E
                        common_neighbors = list(set(G.neighbors(vj)).intersection(set(G.neighbors(vk))))
                        common_neighbors.remove(vi)
                        z = next((n for n in common_neighbors if not G.has_edge(n, vi)), None)
                        if z is not None:
                            # {vi, vj, z, vk} induces a C4
                            return False, [vi, vj, z, vk]

                        # Find two vertices x and y such that vjx, vky ∈ E and vjy, vkx, vix, viy ∉ E
                        for x in G.neighbors(vj):
                            if G.has_edge(vk, x):
                                continue
                            for y in G.neighbors(vk):
                                if not G.has_edge(vj, y) and not G.has_edge(vi, x) and not G.has_edge(vi, y):
                                    if G.has_edge(x, y):
                                        # {vi, vj, x, vk, y} induces a C5
                                        return False, [vi, vj, x, vk, y]
                                    else:
                                        # {vj, x, vk, y} induces a 2K2
                                        return False, [vj, x, vk, y]

    # Compute the largest size of a clique in G
    k = max(len(c) for c in nx.find_cliques(G))

    K = set()
    I = set()
    i = len(alpha) - 1

    # Construct clique K and independent set I
    while len(K) <= k - 1:
        vi = alpha[i]
        A = set(G.neighbors(vi)).intersection(K)
        if len(A) == len(K):
            K.add(vi)
        else:
            x = next(x for x in G.neighbors(vi) if x not in K)
            y = next(y for y in K if not G.has_edge(vi, y))
            z = next(z for z in G.neighbors(y) if not G.has_edge(vi, z))
            # {vi, x, y, z} induces a 2K2
            return False, [vi, x, y, z]
        i -= 1

    i = len(alpha) - 1

    # Check for vertices in I
    while i >= 0:
        vi = alpha[i]
        A = set(G.neighbors(vi)).intersection(K | I)
        if A.issubset(K):
            I.add(vi)
        else:
            x = next(x for x in A.intersection(I))
            y = next(y for y in K if not G.has_edge(x, y) and not G.has_edge(vi, y))
            z = next(z for z in G.neighbors(y) if not G.has_edge(x, z))
            # {vi, x, y, z} induces a 2K2
            return False, [vi, x, y, z]
        i -= 1

    # Output yes and K and I
    return True, K, I

def certifying_threshold(G):
    # Run Certifying-Split to recognize whether G is split
    is_split, K, I = certifying_split(G)

    if not is_split:
        # G is not split, output no and the vertex set inducing 2K2, C4, or P4
        return False, K

    # Compute a non-decreasing degree ordering α
    alpha = sorted(G.nodes(), key=lambda v: G.degree(v))

    beta = list(filter(lambda v: v in I, alpha))

    # Delete all isolated vertices
    G.remove_nodes_from(list(nx.isolates(G)))

    threshold = True
    i = len(alpha) - 1

    while i >= 0:
        vi = alpha[i]
        if vi in G.nodes() and G.degree(vi) == len(G.nodes()):
            # vi is universal
            G.remove_node(vi)
            for x in G.neighbors(vi):
                G.remove_node(x)
            continue
        else:
            threshold = False
            break
        i -= 1

    if threshold:
        # Output yes and β
        return True, beta
    else:
        # Delete remaining vertices
        while True:
            K = set(v for v in K if any(u in I for u in G.neighbors(v)))
            I = set(v for v in I if all(u in K for u in G.neighbors(v)))

            if not any(v in I for v in K):
                break

        # Choose a vertex v of I of highest degree
        v = max(I, key=lambda u: G.degree(u))

        # Find a non-neighbor y of v in K
        non_neighbors = [n for n in K if not G.has_edge(v, n)]
        if not non_neighbors:
            # No non-neighbors found, handle the case accordingly
            return False, []  # or any other appropriate response

        y = next(iter(non_neighbors))

        # Find a neighbor z of y in I
        z = next(n for n in G.neighbors(y) if n in I)

        # Find a vertex w ∈ K that is a neighbor of v and a non-neighbor of z
        w = next(n for n in G.neighbors(v) if n in K and not G.has_edge(z, n))

        # Output no and {v, w, y, z} which induces a P4
        return False, [v, w, y, z]


# Create a threshold graph
G = nx.Graph()
G.add_edges_from([(1, 2), (1, 3), (2, 3), (2, 4), (3, 4), (4, 5)])

# Call the certifying_threshold function
is_threshold, result = certifying_threshold(G)

print("Is threshold:", is_threshold)
if is_threshold:
    beta = result
    print("Nested neighborhood ordering:", beta)
else:
    vertex_set = result
    print("Vertex set inducing 2K2, C4, or P4:", vertex_set)