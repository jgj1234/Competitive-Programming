#include <bits/stdc++.h>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct SegmentTree{
    vector<vector<pair<ll,ll>>> graph;
    vector<pii> bounds;
    vector<int> mp, par;
    SegmentTree(int n){
        graph.resize(4*n);
        mp.resize(n);
        bounds.resize(4*n);
        par.resize(4*n,-1);
        build_tree(0,0,0,n-1);
    }
    void build_tree(int node, int parent, int left, int right){
        if (node!=0){
            par[node] = parent;
        }
        bounds[node] = pii(left,right);
        if (left==right){
            mp[left] = node;
            graph[node].emplace_back(pair<ll,ll>(parent,0LL));
            return;
        }
        graph[node].emplace_back(pair<ll,ll>(2*node+1, 0LL));
        graph[node].emplace_back(pair<ll,ll>(2*node+2, 0LL));
        if (node!=0){
            graph[node].emplace_back(pair<ll,ll> (parent,0LL));
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1, node, left, mid);
        build_tree(2*node+2,node, mid+1,right);
    }
    void update1(int node, int left, int right, int arrLeft, int arrRight, int from, int weight){
        if (arrLeft > right || arrRight < left) return;
        if (arrLeft>=left && arrRight <= right){
            graph[from].emplace_back(pair<ll,ll> (node,weight));
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        update1(2*node+1,left,right,arrLeft,mid,from,weight);
        update1(2*node+2,left,right,mid+1,arrRight,from,weight);
    }
    void update2(int node, int left, int right, int arrLeft, int arrRight, int from, int weight) {
        if (arrLeft > right || arrRight < left) return;
        if (arrLeft>=left && arrRight <= right){
            graph[node].emplace_back(pair<ll,ll> (from,weight));
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        update2(2*node+1,left,right,arrLeft,mid,from,weight);
        update2(2*node+2,left,right,mid+1,arrRight,from,weight);
    }
};
void solve(int cas){
    int n, q, s;
    cin>>n>>q>>s;
    --s;
    SegmentTree segTree(n);
    while (q--){
        int t;
        cin>>t;
        if (t==1){
            int v,u,w;
            cin>>v>>u>>w;
            --v;--u;
            segTree.update1(0,u,u,0,n-1,segTree.mp[v], w);
        }
        else if (t==2){
            int v,l,r,w;
            cin>>v>>l>>r>>w;
            --v;--l;--r;
            segTree.update1(0,l,r,0,n-1,segTree.mp[v], w);
        }
        else{
            int v,l,r,w;
            cin>>v>>l>>r>>w;
            --v;--l;--r;
            segTree.update2(0,l,r,0,n-1,segTree.mp[v], w);
        }
    }
    vector<vector<ll>> res(4*n,vector<ll>(2,-1));
    priority_queue<pair<ll,pair<ll,ll>>, vector<pair<ll,pair<ll,ll>>>, greater<pair<ll,pair<ll,ll>>>> heap;
    heap.push(pair<ll,pair<ll,ll>>(0LL,pair<ll,ll>(segTree.mp[s], true)));
    res[segTree.mp[s]][1] = 0;
    while (!heap.empty()){
        auto [weight, x] = heap.top(); heap.pop();
        auto [node, cz] = x;
        if (res[node][cz] < weight) continue;
        for (auto [neighbor, cost]: segTree.graph[node]){
            if (cost==0 && neighbor > node && !cz) continue;
            if (cost==0 && neighbor < node){
                if (res[neighbor][0]==-1 || res[neighbor][0] > weight + cost){
                    res[neighbor][0] = weight + cost;
                    heap.push(pair<ll,pair<ll,ll>> (weight + cost, pair<ll,ll> (neighbor, false)));
                }
                continue;
            }
            if (res[neighbor][1]==-1 || res[neighbor][1] > weight + cost){
                res[neighbor][1] = weight + cost;
                heap.push(pair<ll,pair<ll,ll>> (weight + cost, pair<ll,ll> (neighbor, true)));
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (res[segTree.mp[i]][0]==-1 && res[segTree.mp[i]][1]==-1){
            cout<<-1<<" ";
            continue;
        }
        else if (res[segTree.mp[i]][0]==-1){
            cout<<res[segTree.mp[i]][1]<<" ";
        }
        else if (res[segTree.mp[i]][1]==-1){
            cout<<res[segTree.mp[i]][1]<<" ";
        }
        else{
            cout<<min(res[segTree.mp[i]][0], res[segTree.mp[i]][1])<<" ";
        }
    }
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}