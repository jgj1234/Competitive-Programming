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
    int n;cin>>n;
    vector<ll> nums(n);for (int i = 0; i < n; i++) cin>>nums[i];
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a;cin>>a;
        nodeMap[a-1].emplace_back(i+1);
    }
    vector<ll> capacity (n);
    auto dfs = [&] (auto&& self, int node) -> ll{
        ll res = 0, sm = 0;
        bool leaf = true;
        for (int neighbor: nodeMap[node]){
            leaf = false;
            res+=self(self, neighbor);
            sm+=nums[neighbor];
        }
        if (leaf){
            capacity[node] = LLONG_MAX;
            return res;
        }
        if (sm>=nums[node]){
            capacity[node] = sm - nums[node];
            return res;
        }
        queue<pii> q;
        for (int neighbor: nodeMap[node]){
            q.push(pii(neighbor,1));
        }
        ll needed = nums[node] - sm;
        while (!q.empty()){
            auto [vtx, dist] = q.front(); q.pop();
            ll mn = min(capacity[vtx], needed);
            res+=mn*dist;
            capacity[vtx]-=mn;
            needed-=mn;
            if (needed==0) return res;
            for (int neighbor: nodeMap[vtx]){
                q.push(pii(neighbor,dist+1));
            }            
        }
        return res;
    };
    cout<<dfs(dfs,0)<<endl;
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