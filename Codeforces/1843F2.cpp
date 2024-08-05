#include <iostream>
#include <vector>
#include <string>
#include <cstring>
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
struct Info{
    ll maxs,mins,maxpref,maxsuf,minpref,minsuf,s,parent;
    Info(){}
    Info(ll w, ll p){
        maxs=w;mins=w;maxpref=w;maxsuf=w;minpref=w;minsuf=w;s=w;parent=p;
    }
};
Info m(Info& bot, Info& top){
    Info main;
    main.s = bot.s+top.s;
    main.maxs = max(max(bot.maxs,top.maxs),bot.maxsuf+top.maxpref);
    main.mins = min(min(bot.mins,top.mins),bot.minsuf+top.minpref);
    main.maxpref = max(bot.maxpref, bot.s+top.maxpref);
    main.maxsuf = max(top.maxsuf,top.s+bot.maxsuf);
    main.minpref = min(bot.minpref,bot.s+top.minpref);
    main.minsuf = min(top.minsuf,top.s+bot.minsuf);
    main.parent = top.parent;
    return main;
}
int kth(int node, int k,vector<vector<Info>>& table){
        int curr = node;
        for (int i = 30; i>=0; i--){
            if ((k&(1<<i))!=0){
                curr = table[curr][i].parent;
                if (curr==-1) return -1;
            }
        }
        return curr;
}
int lca(int a, int b, vector<int>& depths,vector<vector<Info>>& table, int lg){
        if (depths[a]<depths[b]){
            swap(a,b);
        }
        int diff = depths[a]-depths[b];
        int c = kth(a,diff,table);
        if (b==c) return c;
        for (int i = lg - 1; i>=0 ; i--){
            if (table[c][i].parent!=table[b][i].parent){
                c = table[c][i].parent;
                b = table[b][i].parent;
            }
        }
        return table[c][0].parent;
}
void solve(){
    int n;
    cin>>n;
    vector<int> weights = {1};
    vector<int> depths = {0};
    vector<int> par;
    vector<vector<int>> queries;
    for (int i = 0; i < n; i++){
        char c;
        cin>>c;
        if (c=='+'){
            int v,x;
            cin>>v>>x;
            --v;
            depths.emplace_back(depths[v]+1);
            par.emplace_back(v);
            weights.emplace_back(x);
        }
        else{
            int u,v,k;
            cin>>u>>v>>k;
            --u;--v;
            queries.emplace_back(vector<int> {u,v,k});
        }
    }
    n = weights.size();
    int lg = 32 - __builtin_clz(n);
    vector<vector<Info>> lift (n,vector<Info> (lg));
    lift[0][0].parent=-1;
    for (int i = 1; i < n; i++){
        lift[i][0] = Info(weights[par[i-1]],par[i-1]);
    }
    for (int j = 1; j < lg; j++){
        for (int i = 0; i < n; i++){
            if (lift[i][j-1].parent==-1){
                lift[i][j].parent=-1;
                lift[i][j] = lift[i][j-1];
            }
            else{
                lift[i][j] = m(lift[i][j-1],lift[lift[i][j-1].parent][j-1]);
            }
        }
    }
    for (int x = 0; x < queries.size(); x++){
        int u = queries[x][0], v = queries[x][1], k = queries[x][2];
        if (k==0){
            cout<<"YES"<<endl;
            continue;
        }
        if (depths[u]>depths[v]) swap(u,v);
        int l = lca(u,v,depths,lift,lg);
        
        if (u==l){
            int vdiff = depths[v]-depths[u];
            int p = v>0?par[v-1]:-1;
            Info i1 = Info(weights[v],p);
            int curr = v;
            for (int i = lg - 1; i>=0; i--){
                if (vdiff&(1<<i)){
                    i1 = m(i1,lift[curr][i]);
                    curr=lift[curr][i].parent;
                }
            }
            if (k>=i1.mins && k<= i1.maxs){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
            continue;
        }
        int p = u>0?par[u-1]:-1;
        Info i1 = Info(weights[u],p);
        int udiff = depths[u]-depths[l];
        int curr = u;
        for (int i = lg - 1; i>=0; i--){
            if (udiff&(1<<i)){
                Info i2 = m(i1,lift[curr][i]);
                i1 = i2;
                curr=lift[curr][i].parent;
            }
        }
        p = v>0?par[v-1]:-1;
        Info i2 = Info(weights[v],p);
        int vdiff = max(0,depths[v]-depths[l]-1);
        curr = v;
        for (int i = lg - 1; i>=0; i--){
            if (vdiff&(1<<i)){
                Info i3 = m(i2,lift[curr][i]);
                i2 = i3;
                curr = lift[curr][i].parent;
            }
        }
        int mn = min(min(i1.mins,i2.mins),i1.minsuf+i2.minsuf);
        int mx = max(max(i1.maxs,i2.maxs),i1.maxsuf+i2.maxsuf);
        if (k>=mn && k<=mx){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
        
    }
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   cin>>t;
   while (t--){
      solve();
   }
}