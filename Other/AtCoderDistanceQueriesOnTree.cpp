#include <bits/stdc++.h>
#include <fstream>
#define pii pair<int,int>
#define pb push_back
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct SegmentTree{
    vector<ll> tree, lazy, nums;
    SegmentTree(int n, vector<ll>& arr){
        nums = arr;
        lazy.resize(4*n);
        tree.resize(4*n);
        build_tree(0,0,n-1);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node] = nums[left];
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
    }
    void push(int node, int left, int right){
        if (left==right){
            tree[node] += lazy[node];
        }
        else{
            lazy[2*node+1] += lazy[node];
            lazy[2*node+2] += lazy[node];
        }
        lazy[node] = 0;
    }
    void upd(int node, int left, int right, int arrLeft, int arrRight, ll diff){
        if (lazy[node]){
            push(node, arrLeft, arrRight);
        }
        if (arrLeft > right || arrRight < left) return;
        if (arrLeft >= left && arrRight <= right){
            lazy[node] += diff;
            push(node, arrLeft, arrRight);
            return;
        }
        int mid = (arrLeft + arrRight) >> 1;
        upd(2*node+1,left,right,arrLeft,mid,diff);
        upd(2*node+2,left,right,mid+1,arrRight,diff);
    }
    ll get(int node, int left, int right, int pos){
        if (lazy[node]){
            push(node, left, right);
        }
        if (left==right){
            return tree[node];
        }
        int mid = (left+right)>>1;
        if (pos <= mid){
            return get(2*node+1,left,mid,pos);
        }
        else{
            return get(2*node+2,mid+1,right,pos);
        }
    }
    ll get(int pos){
        return get(0,0,nums.size()-1,pos);
    }
};
void solve(int cas){
    //distance between u and v = dist[u] + dist[v] - 2*dist[lca(u,v)]
    int n; cin>>n;
    vector<vector<tuple<int,int,int>>> g(n);
    vector<vector<int>> edges(n-1);
    for (int i = 0; i < n - 1; i++){
        int u,v,w; cin>>u>>v>>w;
        --u;--v;
        g[u].emplace_back(make_tuple(v,w,i));
        g[v].emplace_back(make_tuple(u,w,i));
        edges[i] = vector<int> {u,v,w};
    }
    int tim = 0;
    vector<ll> pref(n), start(n), end(n), id(n), depths(n);
    vector<vector<ll>> jump(n, vector<ll> (18));
    auto dfs = [&] (auto&& self, int node, int parent, int depth, ll sm, int parEdge) -> void{
        pref[tim] = sm;
        start[node] = tim++;
        depths[node] = depth;
        id[start[node]] = node;
        jump[node][0] = parent;
        if (node!=0 && edges[parEdge][1]!=node){
            swap(edges[parEdge][1], edges[parEdge][0]);
        }
        for (int i = 1; i < 18; i++){
            jump[node][i] = jump[jump[node][i-1]][i-1];
        }
        for (const auto& [neighbor, weight, idx]: g[node]){
            if (neighbor!=parent){
                self(self,neighbor, node, depth + 1, sm + weight, idx);
            }
        }
        end[node] = tim;
    };
    dfs(dfs,0,0,0,0,0);
    auto anc = [&] (int u, int v) -> bool{
        return start[u] <= start[v] && end[u] >= end[v];
    };
    auto lca = [&] (int u, int v) -> int{
        if (depths[u] > depths[v]) swap(u,v);
        if (anc(u,v)) return u;
        for (int i = 17; i >= 0; i--){
            if (!anc(jump[u][i],v)){
                u = jump[u][i];
            }
        }
        return jump[u][0];
    };
    SegmentTree seg(n, pref);
    auto dist = [&] (int u, int v) -> ll{
        return seg.get(start[u]) + seg.get(start[v]) - 2*seg.get(start[lca(u,v)]);
    };
    int q; cin>>q;
    while (q--){
        int t; cin>>t;
        if (t==1){
            int i,w; cin>>i>>w;
            --i;
            seg.upd(0,start[edges[i][1]],end[edges[i][1]]-1,0,n-1,w-edges[i][2]);
            edges[i][2] = w;
        }
        else{
            int u,v; cin>>u>>v;
            --u; --v;
            cout << dist(u,v) << '\n';
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