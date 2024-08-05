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
#define ppii pair<int, pair<int,int>>
#define ll long long
#define MOD 1000000007
using namespace std;

int main(){
    ll n,x,y;
    cin>>n>>x>>y;
    x--;y--;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n-1;i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].push_back(b);
        nodeMap[b].push_back(a);
    }
    vector<int> last (n,-1);
    queue<int> q;
    q.push(x);
    while (!q.empty()){
        int frt = q.front();
        q.pop();
        for (int neighbor: nodeMap[frt]){
            if (neighbor!=last[frt] && last[neighbor]==-1){
                q.push(neighbor);
                last[neighbor]=frt;
            }
        }
    }
    vector<int> path; //Contains all nodes on path from y to x
    int curr = y;
    while (curr!=x){
        path.push_back(curr);
        curr=last[curr];
    }
    path.push_back(x);
    auto dfs = [&] (auto self,int node, int parent)->ll{
        ll sz = 1;
        for (int neighbor : nodeMap[node]){
            if ((node==x && neighbor==path[path.size()-2]) || (node==y && neighbor==path[1]) || (neighbor==parent)) continue;
            sz+=self(self,neighbor,node);
        }
        return sz;
    };
    ll flower = dfs(dfs,x,-1);
    ll bee = dfs(dfs,y,-1);
    ll totalPaths = n*(n-1);
    totalPaths-=(flower*bee);
    cout<<totalPaths<<endl;
}