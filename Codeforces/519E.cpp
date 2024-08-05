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
struct TreeTable{ //Assumes 0 is the root and parents are for nodes 1 to n - 1
    vector<vector<int>> table;
    int lg;
    TreeTable(int n, vector<int> par){
        int max_log = 32 - __builtin_clz(n);
        lg = max_log;
        table.resize(n,vector<int> (max_log,-1));
        for (int i = 0; i < n - 1; i++){
            table[i + 1][0] = par[i];
        }
        for (int bit = 1; bit < max_log; bit++){
            for (int i = 1; i < n; i++){
                if (table[i][bit-1]!=-1){
                    table[i][bit] = table[table[i][bit-1]][bit-1];
                }
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
};
void solve(){
    int n;
    cin>>n;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<int> par(n-1,-1);
    vector<int> depths(n);
    vector<int> sz(n);
    auto dfs = [&] (auto&& self, int node, int parent, int depth) -> int{
        if (node!=0){
            par[node-1]=parent;
        }
        depths[node]=depth;
        int res = 1;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                res+=self(self,neighbor,node,depth+1);
            }
        }
        return sz[node]=res;
    };
    dfs(dfs,0,0,0);
    TreeTable tt(n,par);
    int m;
    cin>>m;
    while (m--){
        int x,y;
        cin>>x>>y;
        --x;--y;
        if(x==y){
            cout<<n<<endl;
            continue;
        }
        if (depths[x]>depths[y]){
            swap(x,y);
        }
        int l = tt.lca(x,y,depths);
        int dist = depths[x]+depths[y]-2*depths[l];
        if (dist%2==1){
            cout<<0<<endl;
            continue;
        }
        int adist = depths[x]-depths[l];
        int bdist = depths[y]-depths[l];
        int mid = dist/2;
        if (adist>mid){
            int anc = tt.kth(x,mid);
            cout<<sz[anc]-sz[tt.kth(x,mid-1)]<<endl;
        }
        else if (adist<mid){
            int anc = tt.kth(y,mid);
            cout<<sz[anc]-sz[tt.kth(y,mid-1)]<<endl;
        }
        else{
            int anc = tt.kth(x,mid-1);
            int anc1 = tt.kth(y,mid-1);
            cout<<n-sz[anc]-sz[anc1]<<endl;
        }
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