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
            tree[node] += lazy[node];
        }
        else{
            lazy[2*node+1] += lazy[node];
            lazy[2*node+2] += lazy[node];
        }
        lazy[node] = 0;
    }
    void upd(int node, int left, int right, int arrLeft, int arrRight, int diff){
        if (lazy[node]){
            push(node, arrLeft, arrRight);
        }
        if (arrLeft > right || arrRight < left) return;
        if (arrLeft >= left && arrRight <= right){
            lazy[node] = diff;
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
void solve(int cas){
    int n,q; cin>>n>>q;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++){
        int a,b; cin>>a>>b;
        --a;--b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    int tim = 0;
    vector<int> start(n), end(n), id(n), answer(n);
    vector<ll> pref(n);
    auto dfs = [&] (auto&& self, int node, int parent, ll ps) -> void{
        ps += nums[node];
        pref[node] = ps;
        start[node] = tim++;
        id[start[node]] = node;
        for (int neighbor: g[node]){
            if (neighbor!=parent){
                self(self,neighbor,node, ps);
            }
        }
        end[node] = tim;
    };
    dfs(dfs,0,0,0);
    SegmentTree segTree(tim, pref);
    while (q--){
        int t; cin>>t;
        if (t==1){
            ll s,x; cin>>s>>x;
            --s;
            segTree.upd(0,start[s],end[s]-1,0,n-1,x-nums[s]);
            nums[s] = x;
        }
        else{
            int s; cin>>s; --s;
            cout << segTree.query(0,0,n-1,s) << '\n';
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