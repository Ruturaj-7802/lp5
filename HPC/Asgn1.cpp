#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vec){
        V = vec;
        adj.resize(V);
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void parallelBFS(int source){
        vector<bool> visited(adj.size(), false);
        queue<int> q;
        visited[source] = true;
        q.push(source);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            cout << u << " ";
            #pragma omp parallel for
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i];
                if (!visited[v]) {
                    #pragma omp critical
                    {
                        if (!visited[v]) {
                            visited[v] = true;
                            q.push(v);
                        }
                    }
                }
            }
        }
    }

    void parallelDFSUtil(int v, vector<bool> &visited){
        visited[v] = true;
        cout << v << " ";

        #pragma omp parallel for
        for (int i=0; i<adj[v].size(); i++){
            int u = adj[v][i];
            if(!visited[u]){
                parallelDFSUtil(u, visited);
            }
        }
    }

    void parallelDFS(int source){
        vector<bool> visited(adj.size(), false);
        parallelDFSUtil(source, visited);
    }
};


int main(){
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "Parallel Breadth First Search (BFS) starting from vertex 0: ";
    g.parallelBFS(0);
    cout << endl;

    cout << "Parallel Depth First Search (DFS) starting from vertex 0:";
    g.parallelDFS(0);
    cout << endl;

    return 0;
}