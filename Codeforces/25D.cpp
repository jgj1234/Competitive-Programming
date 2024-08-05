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
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
struct UnionFind{
    vector<int> par;
    vector<int> sz;
    vector<int> rank;
    vector<pii> e;
    set<int> pars;
    int cc;
    UnionFind(int n){
        cc = n;
        par.resize(n,-1);
        sz.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) pars.insert(i);
    }
    int find(int u){
        if (par[u]==-1) return u;
        return par[u]=find(par[u]);
    }
    void unionn(int u, int v){
        int uPar = find(u); int vPar = find(v);
        if (uPar==vPar){
            e.emplace_back(pii(u,v));
            return;
        }
        cc--;
        if (rank[uPar]==rank[vPar]) rank[uPar]++;
        if (rank[uPar]>rank[vPar]){
            pars.erase(vPar);
            sz[uPar]+=sz[vPar]; par[vPar]=uPar;
        }
        else{
            pars.erase(uPar);
            sz[vPar]+=sz[uPar]; par[uPar]=vPar;
        }
    }
};
void solve(){
    int n;
    cin>>n;
    UnionFind uf(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        uf.unionn(a,b);
    }
    int ct = uf.cc-1;
    cout<<ct<<endl;
    for (int i = 0; i < ct; i++){
        auto [a,b] = uf.e.back(); uf.e.pop_back();
        int x = -1;
        int aPar = uf.find(a);
        for (int par: uf.pars){
            if (par!=aPar){
                x=par;
                break;
            }
        }
        cout<<a+1<<" "<<b+1<<" "<<a+1<<" "<<x+1<<endl;
        uf.unionn(a,x);
    }
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   // cin>>t;
   while (t--){
      solve();
   }
}