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
struct Info{
    ll at, best, bestNode;
    Info(){at = 0; best = 0; bestNode = 0;}
    Info(ll a, ll b, ll c){
        at = a;
        best = b;
        bestNode = c;
    }
};
void solve(int cas){  
    int n; cin>>n;
    vector<vector<ll>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b; cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    int lg = 32 - __builtin_clz(n);
    vector<vector<Info>> jump(n, vector<Info> (lg));
    vector<int> depths(n), d1(n);
    auto dfs = [&] (auto&& self, int node, int parent, int depth) -> int{
        int mx1 = 0, mx1i = 0, mx2 = 0, mx2i = 0, ct = 0;
        d1[node] = depth;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                ct++;
                int d = 1 + self(self,neighbor,node, depth + 1);
                if (d > mx1){
                    mx2 = mx1;
                    mx2i = mx1i;
                    mx1i = neighbor;
                    mx1 = d;
                }
                else if (d > mx2){
                    mx2 = d;
                    mx2i = neighbor;
                }
            }
        }
        //cout << node + 1 << " " << mx1 << " " << mx2 << endl;
        if (ct){
            depths[node] = mx1;
            for (int neighbor: nodeMap[node]){
                if (neighbor!=parent){
                    if (neighbor==mx1i){
                        jump[neighbor][0] = Info(node, (ct==1?1:1+mx2), node);
                    }
                    else{
                        jump[neighbor][0] = Info(node, 1 + mx1, node);
                    }
                }
            }
        }
        return mx1;
    };
    dfs(dfs,0,0,0);
    for (int j = 1; j < lg; j++){
        for (int i = 0; i < n; i++){
            jump[i][j].at = jump[jump[i][j-1].at][j-1].at;
            jump[i][j].best = jump[i][j-1].best;
            jump[i][j].bestNode = jump[i][j-1].bestNode;
            if (d1[i] - d1[jump[i][j-1].at] + jump[jump[i][j-1].at][j-1].best >= jump[i][j].best){
                jump[i][j].best = d1[i] - d1[jump[i][j-1].at] + jump[jump[i][j-1].at][j-1].best;
                jump[i][j].bestNode = jump[jump[i][j-1].at][j-1].bestNode;
            }
        }
    }
    int q; cin>>q;
    vector<ll> res(q);
    for (int i = 0; i < q; i++){
        int v,k; cin>>v>>k;
        --v;
        ll ans = depths[v];
        ll curr = v;
        for (int j = 20; j >= 0; j--){
            if ((k>>j)&1){
                
                ans = max(ans, jump[curr][j].best + d1[v] - d1[curr]);
                curr = jump[curr][j].at;
            }
        }
        res[i] = ans;
    }
    for (int i = 0; i < q; i++) cout << res[i] << " \n"[i==q-1];
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