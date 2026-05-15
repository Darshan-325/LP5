#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

vector<vector<int>> graph;
vector<int> visited;

void parallelDFS(int node)
{
    visited[node] = 1;

    #pragma omp critical
    cout << node << " ";

    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); i++)
    {
        int adjNode = graph[node][i];

        #pragma omp critical
        {
            if (!visited[adjNode])
            {
                visited[adjNode] = 1;
                parallelDFS(adjNode);
            }
        }
    }
}

int main()
{
    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    graph.resize(vertices);
    visited.resize(vertices, 0);

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "DFS Traversal: ";

    parallelDFS(0);

    return 0;
}

