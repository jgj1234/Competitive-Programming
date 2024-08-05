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
#define MOD (int)1e9+7
using namespace std;
class UnionFind{
public:
    vector<int> par;
    vector<int> rank;
    UnionFind(int n){
        par.resize(n,-1);
        rank.resize(n);
    }
    int find(int u){
        if (par[u]==-1){
            return u;
        }
        par[u]=find(par[u]);
        return par[u];
    }
    void unionn(int uPar, int vPar){
        if (rank[uPar]==rank[vPar]){
            rank[uPar]++;
        }
        if (rank[uPar]>=rank[vPar]){
            par[vPar]=uPar;
        }
        else{
            par[uPar]=vPar;
        }
    }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> roads(m);
    for (int i = 0; i < m; i++){
        int u,v,c;
        cin>>u>>v>>c;
        roads[i]={u-1,v-1,c};
    }
    sort(roads.begin(),roads.end(),[] (const vector<int>& a, const vector<int>& b){
        return a[2]<b[2];
    });
    UnionFind uf(n);
    int count = 0;
    ll res = 0;
    for (auto road: roads){
        int uPar=uf.find(road[0]);
        int vPar=uf.find(road[1]);
        if (uPar==vPar) continue;
        count++;
        uf.unionn(uPar,vPar);
        res+=road[2];
        if (count==n-1) break;
    }
    if (count==n-1){
        cout<<res;
    }
    else{
        cout<<"IMPOSSIBLE";
    }
}