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

void solve(int cas){
    ll n;
    cin>>n;
    vector<vector<int>> nodeMap(n);
    vector<int> deg(n);
    for (int i = 0; i < n -1 ; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
        deg[a]++;deg[b]++;
    }
    queue<pii> q;
    q.push(pii(0,0));
    vector<ll> dists (n, -1); dists[0] = 0;
    while (!q.empty()){
        auto [node, dist] = q.front(); q.pop();
        for (int neighbor: nodeMap[node]){
            if (dists[neighbor]==-1){
                dists[neighbor] = dist + 1;
                q.push(pii(neighbor,dists[neighbor]));
            }
        }
    }
    vector<ll> calc(n);
    vector<vector<ll>> dl (n);
    vector<ll> leaves;
    for (int i = 1; i < n; i++){
        if (deg[i]==1){
            dl[dists[i]].emplace_back(i);
            leaves.emplace_back(dists[i]);
        }
    }
    for (int distance = 1; distance < n - 1; distance++){
        for (int node: dl[distance]){
            q.push(pii(node,0));
        }
        ll r = 0;
        while (!q.empty()){
            auto [node, dist] = q.front(); q.pop();
            deg[node]--;
            r++;
            for (int neighbor: nodeMap[node]){
                deg[neighbor]--;
                if (deg[neighbor]==1 && neighbor!=0){
                    q.push(pii(neighbor,dist+1));
                }
            }
        }
        calc[distance+1] +=r;
    }
    for (int i = 1; i < calc.size(); i++) calc[i]+=calc[i-1];
    vector<ll> sz(n);
    vector<ll> d(n);
    auto dfs = [&] (auto&& self, int node, int parent, int depth) -> ll{
        ll s = 1;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                s+=self(self,neighbor,node,depth+1);
            }
        }
        d[depth] += s - 1;
        return sz[node] = s;
    };
    dfs(dfs,0,0,0);
    ll res = LLONG_MAX;
    for (int i = 0; i < n; i++){
        res = min(res, d[i] + calc[i]);
    }
    cout<<res<<endl;
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