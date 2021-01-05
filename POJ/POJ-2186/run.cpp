// problem: [POJ-2186](https://vjudge.net/problem/POJ-2186)

#include <iostream>
#include <vector>
#include <cstring>
#include <map>

using namespace std;

const int MAX_N = 10010;

int N, M;
vector<int> G[MAX_N];   // Graph
vector<int> tG[MAX_N];  // Transposed Graph, invert edge direction
bool used[MAX_N];  // for Depth First Search
vector<int> finishOrder;
int scc[MAX_N];  // strongly connected component
int sccCount[MAX_N];  // vertex count in each strongly connected component

int inDegree[MAX_N];
int outDegree[MAX_N];

// Depth First Search
void DFS(int u) {
    used[u] = true;
    for (int i = 0; i < G[u].size(); i++) {
        if (!used[G[u][i]])
            DFS(G[u][i]);
    }
    finishOrder.push_back(u);
}


// Depth First Search on Transposed Graph
void tDFS(int u, int tag) {
    used[u] = true;
    scc[u] = tag;
    for (int i = 0; i < tG[u].size(); i++) {
        if (!used[tG[u][i]])
            tDFS(tG[u][i], tag);
    }
}


// Strongly Connected Component
int SCC() {
    memset(used, 0, N * sizeof(bool));
    for (int i = 0; i < N; i++) {
        if (!used[i])
            DFS(i);
    }
    
    int num_scc = 0;
    memset(used, 0, N * sizeof(bool));
    for (int i = finishOrder.size() - 1; i >= 0; i--) {
        if (!used[finishOrder[i]]) {
            tDFS(finishOrder[i], num_scc);
            num_scc++;
        }
    }

    return num_scc;
}


int main() {
    int a, b;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        G[a - 1].push_back(b - 1);
        tG[b - 1].push_back(a - 1);
    }

    int num_scc = SCC();
    memset(sccCount, 0, num_scc * sizeof(int));
    memset(inDegree, 0, num_scc * sizeof(int));
    memset(outDegree, 0, num_scc * sizeof(int));
    for (int i = 0; i < N; i++) {
        sccCount[scc[i]] += 1;
        for (int j = 0; j < G[i].size(); j++) {
            if (scc[i] != scc[G[i][j]]) {
                // calculate in-degree and out-degree between storngly connected component
                outDegree[scc[i]]++;
                inDegree[scc[G[i][j]]]++;
            }
        }
    }

    int ans = 0;
    bool foundZeroOutDegree = false;
    for (int i = 0; i < num_scc; i++) {
        if (outDegree[i] == 0) {
            if (foundZeroOutDegree) {
                // multi zero out-degree strongly connected component
                ans = 0;
                break;
            }

            if (inDegree[i] == 0 && num_scc > 1) {
                // the graph is unconnected
                ans = 0;
                break;
            }

            foundZeroOutDegree = true;
            ans = sccCount[i];
        }
    }
    cout << ans << endl;

    return 0;
}
