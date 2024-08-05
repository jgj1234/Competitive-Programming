#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>

#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

struct UnionFind{
   vector<int> par;
   vector<int> rank;
   UnionFind(int n){
      par.resize(n,-1);
      rank.resize(n);
   }
   int find(int u){
      if (par[u]==-1) return u;
      return par[u]=find(par[u]);
   }
   void unionn(int u, int v){
      int uPar=find(u);
      int vPar=find(v);
      if (uPar==vPar) return;
      if (rank[uPar]==rank[vPar]) rank[uPar]++;
      if (rank[uPar]>rank[vPar]){
         par[vPar]=uPar;
      }
      else{
         par[uPar]=vPar;
      }
   }
};
void solve(){
   int n;
   cin>>n;
   vector<int> a(n);
   for (int i = 0; i < n; i++) cin>>a[i];
   UnionFind uf(n);
   unordered_map<int,int> mp;
   for (int i = 0; i < n; i++){
      int msk=a[i]>>2;
      if (mp.find(msk)!=mp.end()){
         uf.unionn(i,mp[msk]);
      }
      else{
         mp[msk]=i;
      }
   }
   unordered_map<int,vector<int>> mp2;
   for (int i = 0; i < n; i++){
       int x = uf.find(i);
      if (mp2.find(x)==mp2.end()){
         mp2[x]={a[i]};
      }
      else{
         mp2[x].emplace_back(a[i]);
      }
   }
   for (auto [key,v]: mp2){
      sort(mp2[key].begin(),mp2[key].end(),greater<int>());
   }
   vector<int> res (n);
   for (int i = 0; i < n; i++){
       int x = uf.find(i);
      res[i]=mp2[x].back();
      mp2[x].pop_back();
   }
   for (int i = 0; i < n;i++){
      cout<<res[i]<<" ";
   }
   cout<<endl;
}
int main(){
   int t;
   cin>>t;
   while (t--){
      solve();
   }
}