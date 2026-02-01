class DisjointSet:
    def __init__(self, vertices):
        self.parent = {v: v for v in vertices}
        self.rank = {v: 0 for v in vertices}

    def find(self, vertex):
        if self.parent[vertex] != vertex:
            self.parent[vertex] = self.find(self.parent[vertex])
        return self.parent[vertex]
    
    def union(self, root1, root2):
        if self.rank[root1] > self.rank[root2]:
            self.parent[root2] = root1
        elif self.rank[root1] < self.rank[root2]:
            self.parent[root1] = root2
        else:
            self.parent[root2] = root1
            self.rank[root1] += 1

def kruskal(graph: map):
    # extract edges and deduplicate
    edges = []
    for vertex, neighbors in graph.items():
        for neighbor, weight in neighbors:
            if (neighbor, vertex, weight) not in edges:
                edges.append((vertex, neighbor, weight))
    
    # sort edges by weight ascending
    edges.sort(key=lambda edge: (edge[2], edge[0], edge[1]))

    # extract vertices
    vertices = list(graph.keys())

    disjoint_set = DisjointSet(vertices)

    mst = []
    for u, v, weight in edges:
        root_u = disjoint_set.find(u)
        root_v = disjoint_set.find(v)

        if root_u != root_v:
            mst.append((u, v, weight))
            disjoint_set.union(root_u, root_v)

    return mst

if __name__ == "__main__":
    graph = {
        'A': [('B', 10), ('D', 50)],
        'B': [('A', 10), ('C', 25), ('D', 5)],
        'C': [('B', 25), ('D', 25)],
        'D': [('C', 25), ('A', 50), ('B', 5)],
    }

    mst = kruskal(graph)

    print(mst)
