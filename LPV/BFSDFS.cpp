#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX = 100;

vector<int> graph[MAX];
bool visited[MAX];


// ======================= PARALLEL BFS =======================
void parallelBFS(int start)
{
    queue<int> q;

    // Reset visited array
    for (int i = 0; i < MAX; i++)
    {
        visited[i] = false;
    }

    visited[start] = true;
    q.push(start);

    cout << "\nParallel BFS Traversal: ";

    while (!q.empty())
    {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++)
        {
            int curr;

            // Critical section for queue access
            #pragma omp critical
            {
                curr = q.front();
                q.pop();

                cout << curr << " ";
            }

            // Traverse adjacent vertices
            for (int j = 0; j < graph[curr].size(); j++)
            {
                int neighbor = graph[curr][j];

                if (!visited[neighbor])
                {
                    #pragma omp critical
                    {
                        if (!visited[neighbor])
                        {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
    }

    cout << endl;
}


// ======================= PARALLEL DFS =======================
void parallelDFS(int start)
{
    stack<int> s;

    // Reset visited array
    for (int i = 0; i < MAX; i++)
    {
        visited[i] = false;
    }

    s.push(start);

    cout << "\nParallel DFS Traversal: ";

    while (!s.empty())
    {
        int curr;

        // Critical section for safe stack access
        #pragma omp critical
        {
            if (!s.empty())
            {
                curr = s.top();
                s.pop();
            }
        }

        // Check and mark visited
        if (!visited[curr])
        {
            visited[curr] = true;

            // Print node
            #pragma omp critical
            cout << curr << " ";

            // Explore neighbors in parallel
            #pragma omp parallel for
            for (int i = 0; i < graph[curr].size(); i++)
            {
                int adj = graph[curr][i];

                if (!visited[adj])
                {
                    #pragma omp critical
                    {
                        s.push(adj);
                    }
                }
            }
        }
    }

    cout << endl;
}


// ======================= MAIN FUNCTION =======================
int main()
{
    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v;

        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u); // Undirected graph
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    // Call BFS
    parallelBFS(start);

    // Call DFS
    parallelDFS(start);

    return 0;
}