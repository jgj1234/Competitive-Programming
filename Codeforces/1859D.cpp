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
struct UnionFind{
    vector<ll> par, rank, mx;
    UnionFind(int n, vector<vector<ll>>& nums){
        par.resize(4*n,-1); rank.resize(4*n); mx.resize(4*n);
        for (int i = 0; i < n; i++){
            mx[i] = nums[i][3];
        }
    };
    int find(int u){
        if (par[u]==-1) return u;
        return par[u] = find(par[u]);
    }
    void unionn(int u, int v){
        int uPar = find(u), vPar = find(v);
        if (uPar==vPar) return;
        if (rank[uPar] == rank[vPar]) rank[uPar]++;
        if (rank[uPar] > rank[vPar]){
            par[vPar] = uPar;
            mx[uPar] = max(mx[uPar], mx[vPar]);
        }
        else{
            par[uPar] = vPar;
            mx[vPar] = max(mx[vPar], mx[uPar]);
        }
    }
};
void solve(int cas){
    int n; cin>>n;
    vector<vector<ll>> nums(n, vector<ll> (4)); //l,r,a,b;
    for (int i = 0; i < n; i++){
        cin>>nums[i][0]>>nums[i][1]>>nums[i][2]>>nums[i][3];
    }
    auto cmp = [&] (vector<ll>& f, vector<ll>& s) -> bool{
        if (f[0]!=s[0]){
            return f[0] < s[0];
        }
        if (f.size()!=s.size()){
            return f.size() > s.size();
        }
        return f[1] > s[1];
    };
    sort(all(nums), cmp);
    UnionFind uf(n, nums);
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> bheap;
    for (int i = 0; i < n; i++){
        while (!bheap.empty() && bheap.top().first < nums[i][0]) bheap.pop();
        if (!bheap.empty()){
            uf.unionn(i, bheap.top().second);
        }
        bheap.push(pair<ll,ll> (nums[i][3], i));
    }
    vector<vector<ll>> a;
    for (int i = 0; i < n; i++){
        a.emplace_back(vector<ll>{nums[i][0],nums[i][1],i});
    }
    int q; cin>>q;
    for (int i = 0; i < q; i++){
        ll x; cin>>x;
        a.emplace_back(vector<ll>{x,i});
    }
    sort(all(a),cmp);
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> heap;
    priority_queue<pair<ll,ll>> curr;
    vector<bool> vis(n);
    vector<ll> res(q);
    for (int i = 0; i < a.size(); i++){
        while (!heap.empty() && heap.top().first < a[i][0]){
            vis[heap.top().second] = false;
            heap.pop();
        }
        while (!curr.empty() && !vis[curr.top().second]) curr.pop();
        if (a[i].size()==2){
            if (heap.empty()){
                res[a[i][1]] = a[i][0];
            }
            else{
                res[a[i][1]] = max(a[i][0],curr.top().first);
            }
        }
        else{
            heap.push(pair<ll,ll>(a[i][1], a[i][2]));
            curr.push(pair<ll,ll>(uf.mx[uf.find(a[i][2])],a[i][2]));
            vis[a[i][2]] = true;
        }
    }
    for (int i = 0; i < q; i++){
        cout<<res[i]<<" \n"[i==q-1];
    }
}

int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}