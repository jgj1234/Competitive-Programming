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

void solve(int cas){ 
    int n,m; cin>>n>>m;
    vector<vector<pair<ll,ll>>> g(n);
    for (int i = 0; i < m; i++){
        ll a,b,c; cin>>a>>b>>c;
        --a;--b;
        g[a].emplace_back(make_pair(b,c));
    }
    vector<ll> dp(n, LLONG_MAX);
    dp[0] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> heap;
    vector<vector<ll>> ins(n);
    vector<ll> ind(n);
    heap.push(make_pair(0,0));
    while (!heap.empty()){
        auto [weight, node] = heap.top(); heap.pop();
        if (weight > dp[node]) continue;
        if (node==n-1) break;
        for (auto [neighbor, cost]: g[node]){
            if (weight + cost < dp[neighbor]){
                dp[neighbor] = weight + cost;
                heap.push(make_pair(dp[neighbor], neighbor));
                ins[neighbor].clear();
                ins[neighbor].emplace_back(node);
                ind[neighbor] = 1;
            }
            else if (weight + cost == dp[neighbor]){
                ins[neighbor].emplace_back(node);
                ind[neighbor]++;
            }
        }
    }
    vector<ll> ind1(all(ind));
    while (!heap.empty()) heap.pop();
    vector<ll> ways(n);
    ways[0] = 1;
    vector<vector<ll>> g1(n);
    for (int i = 0; i < n; i++){
        for (int x: ins[i]){
            g1[x].emplace_back(i);
        }
    }
    queue<int> q;
    q.push(0);
    while (!q.empty()){
        int node = q.front(); q.pop();
        if (node==n-1) break;
        for (int neighbor: g1[node]){
            ind[neighbor]--;
            ways[neighbor] = (ways[neighbor] + ways[node])%MOD;
            if (ind[neighbor]==0){
                q.push(neighbor);
            }
        }
    }
    vector<ll> dp1(n, LLONG_MAX); dp1[0] = 0;
    heap.push(make_pair(0,0));
    while (!heap.empty()){
        auto [weight, node] = heap.top(); heap.pop();
        if (weight > dp1[node]) continue;
        if (node==n-1) break;
        for (int neighbor: g1[node]){
            if (weight + 1 < dp1[neighbor]){
                dp1[neighbor] = weight + 1;
                heap.push(make_pair(dp1[neighbor],neighbor));
            }
        }
    }
    while (!q.empty()) q.pop();
    q.push(0);
    vector<ll> dp2(n);
    while (!q.empty()){
        int node = q.front(); q.pop();
        for (int neighbor: g1[node]){
            ind1[neighbor]--;
            dp2[neighbor] = max(dp2[neighbor], 1 + dp2[node]);
            if (ind1[neighbor]==0){
                q.push(neighbor);
            }
        }
    }
    cout << dp[n-1] << ' ' << ways[n-1] << ' ' << dp1[n-1] << ' ' << dp2[n-1] << '\n';
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