#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pli pair<long long,int>
#define ll long long
#define MOD 1000000007
using namespace std;

int main(){
    int n,m,k,s;
    cin>>n>>m>>k>>s;
    vector<vector<int>> nodeMap(n);
    vector<vector<int>> goods(k);
    for (int i = 0; i < n; i++){
        int a;
        cin>>a;
        goods[--a].push_back(i);
    }
    for (int i = 0; i < m; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].push_back(b);
        nodeMap[b].push_back(a);
    }
    vector<vector<int>> shortestPaths(n,vector<int>(k,INT_MAX));
    for (int i = 0; i < k; i++){
        queue<pii> q;
        for (int j = 0; j < goods[i].size();j++){
            q.push({goods[i][j],0});
            shortestPaths[goods[i][j]][i]=0;
        }
        while (!q.empty()){
            auto [node,moves]=q.front();
            q.pop();
            for (int neighbor:nodeMap[node]){
                if (shortestPaths[neighbor][i]==INT_MAX){
                    q.push({neighbor,moves+1});
                    shortestPaths[neighbor][i]=moves+1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        sort(shortestPaths[i].begin(),shortestPaths[i].end());
        ll res = 0;
        for (int j = 0; j < s; j++){
            res+=shortestPaths[i][j];
        }
        cout<<res<<" ";
    }

}