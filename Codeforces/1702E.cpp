#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

bool isBipartite(int n, unordered_map<int, vector<int>>& nodeMap) {
    vector<int> colors(n, -1);
    for (int i = 0; i < n; ++i) {
        if (colors[i] == -1) {
            colors[i] = 0;
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (int neighbor : nodeMap[node]) {
                    if (colors[neighbor] == colors[node]) {
                        return false;
                    }
                    if (colors[neighbor] == -1) {
                        colors[neighbor] = colors[node] ^ 1;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    int num_tests;
    cin >> num_tests;
    for (int _ = 0; _ < num_tests; ++_) {
        int n;
        cin >> n;
        unordered_map<int, vector<int>> nodeMap;
        bool sameEdge = false;
        for (int i = 0; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            if (u == v) {
                sameEdge = true;
            }
            nodeMap[u - 1].push_back(v - 1);
            nodeMap[v - 1].push_back(u - 1);
        }
        if (sameEdge) {
            cout << "NO" << endl;
            continue;
        }
        for (auto& pair : nodeMap) {
            if (pair.second.size() > 2) {
                cout << "NO" << endl;
                goto next_test;
            }
        }
        if (isBipartite(n, nodeMap)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        next_test:;
    }
    return 0;
}