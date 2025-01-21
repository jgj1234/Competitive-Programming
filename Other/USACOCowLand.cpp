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
        tree.resize(4*n);
        lazy.resize(4*n);
        nums = arr;
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
    void push(int node, int arrLeft, int arrRight){
        if (arrLeft==arrRight){
            tree[node] ^= lazy[node];
        }
        else{
            lazy[2*node+1] ^= lazy[node];
            lazy[2*node+2] ^= lazy[node];
        }
        lazy[node] = 0;
    }
    void upd(int node, int left, int right, int arrLeft, int arrRight, int diff){
        if (lazy[node]){
            push(node, arrLeft, arrRight);
        }
        if (arrLeft > right || arrRight < left) return;
        if (arrLeft >= left && arrRight <= right){
            lazy[node] ^= diff;
            push(node, arrLeft, arrRight);
            return;
        }
        int mid = (arrLeft + arrRight) >> 1;
        upd(2*node+1,left,right,arrLeft,mid,diff);
        upd(2*node+2,left,right,mid+1,arrRight,diff);
    }
    ll query(int node, int left, int right, int pos){
        if (lazy[node]){
            push(node, left,right);
        }
        if (left==right){
            return tree[node];
        }
        int mid = (left + right) >> 1;
        if (pos <= mid){
            return query(2*node+1,left,mid,pos);
        }
        return query(2*node+2,mid+1,right,pos);
    }
};
ifstream in("cowland.in");
ofstream out("cowland.out");
void solve(int cas){
    int n,q; in>>n>>q;
    vector<ll> nums(n);
    for (auto& a: nums) in>>a;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++){
        int a,b; in>>a>>b;
        --a;--b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    vector<ll> pref(n), id(n), start(n), end(n), par(n), depths(n);
    vector<vector<ll>> jump(n, vector<ll> (20));
    int tim = 0;
    auto dfs = [&] (auto&& self, int node, int parent, ll xr, int depth) -> void{
        xr^=nums[node];
        if (node){
            par[node-1] = parent;
        }
        depths[node] = depth;
        jump[node][0] = parent;
        for (int i = 1; i < 20; i++){
            jump[node][i] = jump[jump[node][i-1]][i-1];
        }
        pref[tim] = xr;
        start[node] = tim++;
        id[start[node]] = node;
        for (int neighbor: g[node]){
            if (neighbor!=parent){
                self(self,neighbor,node,xr,depth+1);
            }
        }
        end[node] = tim;
    };
    dfs(dfs,0,0,0,0);
    auto anc = [&] (int u, int v) -> bool{
        return start[u] <= start[v] && end[u] >= end[v];
    };
    auto lca = [&] (int u, int v) -> int{
        if (depths[v] < depths[u]) swap(u,v);
        if (anc(u, v)) return u;
        for (int i = 19; i >= 0; i--){
            if (!anc(jump[u][i], v)){
                u = jump[u][i];
            }
        }
        return jump[u][0];
    };
    SegmentTree segTree(n, pref);
    while (q--){
        int t; in>>t;
        if (t==1){
            int i,v; in>>i>>v;
            --i;
            segTree.upd(0,start[i],end[i]-1,0,n-1, v^nums[i]);
            nums[i] = v;
        }
        else{
            int u,v; in>>u>>v;
            --u;--v;
            int l = lca(u,v);
            ll uXor = segTree.query(0,0,n-1,start[u]);
            ll vXor = segTree.query(0,0,n-1,start[v]);
            ll lXor = segTree.query(0,0,n-1,start[l]);
            out << ((uXor^lXor)^(vXor^lXor)^nums[l]) << '\n';
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