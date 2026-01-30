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
    int size(){return (int) vec.size();}
    void add_front(T x){vec.emplace_back(x);}
    T& operator [](const int& x) {return rbegin(vec)[x];}
};
void solve(int cas){
    int n; cin>>n;
    vector<vector<ll>> g(n);
    for (int i = 0; i < n - 1; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vector<MergeVector<ll>> ct(n), sm(n);
    auto dfs = [&] (auto&& self, int node, int parent, ll depth) -> ll{
        ll res = 0;
        for (int neighbor: g[node]){
            if (neighbor!=parent){
                res += self(self,neighbor,node,depth+1);
                if (ct[neighbor].size() > ct[node].size()){
                    swap(ct[node], ct[neighbor]);
                    swap(sm[node], sm[neighbor]);
                }
                for (ll i = ct[neighbor].size() - 1; i >= 0; i--){
                    ll curr = ct[neighbor][i];
                    if (i + 1 < ct[neighbor].size()) curr -= ct[neighbor][i+1];
                    if (i + 1 < ct[node].size()){
                        res += (2*(i+1)-1)*curr*ct[node][i+1];
                    }
                    ll pref = sm[node][0], ctbef = ct[node][0];
                    if (i + 1 < sm[node].size()){
                        pref -= sm[node][i+1];
                        ctbef -= ct[node][i+1];
                    }
                    pref -= 2*depth*ctbef;
                    res += pref*curr;
                }
                for (int i = ct[neighbor].size()-1; i>=0; i--){
                    ct[node][i] += ct[neighbor][i];
                }
                for (int i = sm[neighbor].size()-1; i >= 0; i--){
                    sm[node][i] += sm[neighbor][i];
                }
            }
        }
        ll act = 1, asmm = 2*depth-1;
        if (ct[node].size()){
            act += ct[node][0];
            asmm += sm[node][0];
        }
        ct[node].add_front(act);
        sm[node].add_front(asmm);
        return res;
    };
    cout << dfs(dfs,0,0,0) << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}