#include <bits/stdc++.h>
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
    vector<int> tree;
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void upd(int node, int left, int right, int pos, int v){
        if (left==right){
            tree[node] = v;
            return;
        }
        int mid = (left+right)>>1;
        if (pos <= mid){
            upd(2*node+1,left,mid,pos,v);
        }
        else{
            upd(2*node+2,mid+1,right,pos,v);
        }
        tree[node] = tree[2*node+1] + tree[2*node+2];
    }
    int query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft > right || arrRight < left) return 0;
        if (arrLeft >= left && arrRight <= right) return tree[node];
        int mid = (arrLeft + arrRight) >> 1;
        return query(2*node+1,left,right,arrLeft,mid) + query(2*node+2,left,right,mid+1,arrRight);
    }
};
void solve(int cas){
    int n; cin>>n;
    vector<ll> colors(n);
    for (auto& a: colors) cin>>a;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++){
        int a,b; cin>>a>>b;
        --a;--b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    int tim = 0;
    vector<int> start(n), end(n), id(n), answer(n);
    auto dfs = [&] (auto&& self, int node, int parent) -> void{
        start[node] = tim++;
        id[start[node]] = node;
        for (int neighbor: g[node]){
            if (neighbor!=parent){
                self(self,neighbor,node);
            }
        }
        end[node] = tim;
    };
    dfs(dfs,0,0);
    SegmentTree segTree(tim);
    map<int,int> right;
    for (int i = tim - 1; i >= 0; i--){
        if (right.count(colors[id[i]])){
            segTree.upd(0,0,tim-1,right[colors[id[i]]], 0);
        }
        segTree.upd(0,0,tim-1,i,1);
        right[colors[id[i]]] = i;
        answer[id[i]] = segTree.query(0,i,end[id[i]] - 1,0,tim - 1);
    }
    for (int i = 0; i < n; i++){
        cout << answer[i] << " ";
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