#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
template<typename T>
struct MergeVector{
    vector<T> vec;
    MergeVector(){}
    int sz(){return (int) vec.size();}
    void add_front(int x){vec.emplace_back(x);}
    T& operator [](const int& x) {return rbegin(vec)[x];}
};
vector<ll> g[200005];
void solve(int cas){
    int n,k1,k2; cin>>n>>k1>>k2;
    for (int i = 1; i <= n - 1; i++){
        ll u,v;
        cin >> u >> v;
        --u;--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vector<MergeVector<ll>> nums(n);
    auto dfs = [&] (auto&& self, int node, int parent) -> ll{
        ll res = 0;
        for (int neighbor: g[node]){
            if (neighbor!=parent){
                res += self(self,neighbor,node);
                if (nums[neighbor].sz() > nums[node].sz()) swap(nums[neighbor],nums[node]);
                for (int i = 0; i < min(nums[neighbor].sz(), k2 - 1); i++){
                    int start = max(0, k1 - (i+1) - 1);
                    if (start < nums[node].sz()){
                        int end = k2 - (i + 1);
                        ll curr = nums[neighbor][i];
                        if (i + 1 < nums[neighbor].sz()) curr -= nums[neighbor][i+1];
                        ll diff = nums[node][start];
                        if (end< nums[node].sz())  diff -= nums[node][end];
                        res += curr*diff;
                    }
                }
                for (int i = 0; i < nums[neighbor].sz(); i++){
                    nums[node][i] += nums[neighbor][i];
                }
            }
        }
        ll ad = 0;
        if (nums[node].sz()) ad = nums[node][0];
        nums[node].add_front(1 + ad); 
        if (k1 < nums[node].sz()){
            ll a1 = nums[node][k1];
            if (k2 + 1 < nums[node].sz()) a1 -= nums[node][k2+1];
            res += a1;
        }
        return res;
    };
    cout << dfs(dfs,0,0) << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    //cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}
