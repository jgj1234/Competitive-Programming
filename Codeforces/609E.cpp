#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
#include <cmath>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
struct DSU{
    vector<int> par;
    vector<int> rank;
    DSU(int n){
        par.resize(n,-1);
        rank.resize(n);
    }
    int find(int u){
        if (par[u]==-1) return u;
        return par[u] = find(par[u]);
    }
    void unite(int u, int v){
        if (rank[u]==rank[v]) rank[u]++;
        if (rank[u]>rank[v]){
            par[v]=u;
        }
        else{
            par[u] = v;
        }
    }
};
struct TreeTable{ //Assumes 0 is the root and parents are for nodes 1 to n - 1
    vector<vector<int>> table;
    vector<vector<int>> mw;
    int lg;
    TreeTable(int n, vector<int>& par,vector<int>& weight){
        int max_log = 32 - __builtin_clz(n);
        lg = max_log;
        table.resize(n,vector<int> (max_log));
        mw.resize(n,vector<int> (max_log));
        for (int i = 0; i < n - 1; i++){
            table[i + 1][0] = par[i];
            mw[i+1][0] = weight[i];
        }
        for (int bit = 1; bit < max_log; bit++){
            for (int i = 1; i < n; i++){
                table[i][bit] = table[table[i][bit-1]][bit-1];
                mw[i][bit] = max(mw[i][bit-1],mw[table[i][bit-1]][bit-1]);
            }
        }
    }
    void getDepths(int node, int parent, int depth, vector<int>& res, vector<vector<int>>& nodeMap){
        res[node] = depth;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                getDepths(neighbor,node,depth+1,res,nodeMap);
            }
        }
    }
    int kth(int node, int k){
        int curr = node;
        for (int i = 30; i>=0; i--){
            if ((k&(1<<i))!=0){
                curr = table[curr][i];
                if (curr==-1) return -1;
            }
        }
        return curr;
    }
    int lca(int a, int b, vector<int>& depths){
        if (depths[a]<depths[b]){
            swap(a,b);
        }
        int diff = depths[a]-depths[b];
        int c = kth(a,diff);
        if (b==c) return c;
        for (int i = lg - 1; i>=0 ; i--){
            if (table[c][i]!=table[b][i]){
                c = table[c][i];
                b = table[b][i];
            }
        }
        return table[c][0];
    }
    int query(int node, int k){
        int mx = 0;
        for (int i = 0; i < lg; i++){
            if (k&(1<<i)){
                mx = max(mx,mw[node][i]);
                node = table[node][i];
            }
        }
        return mx;
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    auto cmp = [&] (const pair<pii,int>& f, const pair<pii,int>& s){
        return f.second<s.second;
    };
    vector<pair<pii,int>> edges(m);
    for (int i = 0; i < m; i++){
        cin>>edges[i].first.first>>edges[i].first.second>>edges[i].second;
        edges[i].first.first--;
        edges[i].first.second--;
    }
    vector<pair<pii,int>> copy(all(edges));
    sort(all(copy),cmp);
    DSU uf (n);
    ll res = 0;
    int ct = 0;
    set<pair<pii,int>> s;
    for (const auto& [p,w]: copy){
        auto [u,v] = p;
        int uPar = uf.find(u);
        int vPar = uf.find(v);
        if (uPar==vPar) continue;
        ct++;
        res+=w;
        s.insert({pii(u,v),w});
        uf.unite(uPar,vPar);
        if (ct==n-1) break;
    }
    vector<vector<pii>> nodeMap(n);
    for (const auto& [p,w]: s){
        auto [u,v] = p;
        nodeMap[u].emplace_back(v,w);
        nodeMap[v].emplace_back(u,w);
    }
    vector<int> par (n-1,-1);
    vector<int> weight(n-1,-1);
    vector<int> depth(n);
    auto dfs = [&] (auto&& self, int node, int parent, int d, int pw)->void{
        if (node!=0){
            par[node-1] = parent;
            weight[node-1] = pw;
        }
        depth[node] = d;
        for (auto [neighbor, w]: nodeMap[node]){
            if (neighbor!=parent){
                self(self,neighbor,node,d+1,w);
            }
        }
    };
    dfs(dfs,0,0,0,0);
    TreeTable tt(n,par,weight);
    for (const auto& [p,w]: edges){
        auto [u,v] = p;
        if (s.count(pair<pii,int>(pii(u,v),w))){
            cout<<res<<endl;
            continue;
        }
        int l = tt.lca(u,v,depth);
        int ud = depth[u]-depth[l];
        int mx = tt.query(u,ud);
        int vd = depth[v]-depth[l];
        mx = max(mx,tt.query(v,vd));
        cout<<res-mx+w<<endl;
    }
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   //cin>>t;
   while (t--){
      solve();
   }
}