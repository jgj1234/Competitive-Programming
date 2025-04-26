#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 200005;
vector<ll> g[N];
bool dead[N];
int sz[N];
tuple<ll,ll,ll> best[N]; //mx1, mx1sub, mx2
vector<tuple<ll,ll,ll>> anc[N]; //ancestor, subtree of ancestor, dist to anc
int dfs_1(int node, int parent){
    sz[node] = 1;
    for (int neighbor: g[node]){
        if (neighbor!=parent && !dead[neighbor]){
            sz[node] += dfs_1(neighbor, node);
        }
    }
    return sz[node];
}
int dfs_centroid(int node, int parent, int tot){
    for (int neighbor: g[node]){
        if (neighbor!=parent && !dead[neighbor] && sz[neighbor] > tot/2) return dfs_centroid(neighbor, node, tot);
    }
    return node;
}
void dfs(int node, int par, int cent, int subt, int depth){
    anc[node].emplace_back(make_tuple(cent, subt, depth));
    for (int neighbor: g[node]){
        if (neighbor!=par && !dead[neighbor]){
            dfs(neighbor,node,cent,subt,depth+1);
        }
    }
}
void Go(int node){
    //cout << "NODE: " << node << '\n';
    dfs_1(node, node);
    int cent = dfs_centroid(node, node, sz[node]);
    dead[cent] = true;
    for (int neighbor: g[cent]){
        if (!dead[neighbor]){
            dfs(neighbor, cent, cent, neighbor, 1);
        }
    }
    for (int neighbor: g[cent]){
        if (!dead[neighbor]){
            Go(neighbor);
        }
    }
}
void solve(int cas){
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);
    int q; cin>>q;
    for (int i = 0; i < q; i++){
        best[i] = make_tuple(-1,-1,-1);
    }
    vector<pair<ll,ll>> nums(q);
    vector<ll> roots;
    int ct = 0;
    for (int i = 0; i < q; i++){
        char c; cin>>c;
        int b; cin>>b; --b;
        nums[i].first = (c=='B');
        nums[i].second = (c=='B' ? ct : b);
        if (c=='B' && b!=-2){
            g[b].emplace_back(ct);
            g[ct].emplace_back(b);
        }
        else if (c=='B'){
            roots.emplace_back(ct);
        }
        if (c=='B'){
            ct++;
        }
    }
    for (ll x: roots) Go(x);
    for (auto [type, node]: nums){
        if (type){
            for (auto [a, s, d]: anc[node]){
                auto [mx1, mx1sub, mx2] = best[a];
                if (s==mx1sub){
                    best[a] = make_tuple(max(mx1, d), mx1sub, mx2);
                }
                else{
                    if (d > mx1){
                        best[a] = make_tuple(d, s, mx1);
                    }
                    else if (d > mx2){
                        best[a] = make_tuple(mx1, mx1sub, d);
                    }
                }
            }
            auto [mx1, mx1sub, mx2] = best[node];
            if (mx1==-1){
                best[node] = make_tuple(0,node,mx2);
            }
            else if (mx2==-1){
                best[node] = make_tuple(mx1, mx1sub,0);
            }
        }
        else{
            ll res = 0;
            auto [m1,m1s,m2] = best[node];
            if (m1!=-1) res = m1;
            for (auto [a, s, d]: anc[node]){
                auto [mx1, mx1sub, mx2] = best[a];
                if (s==mx1sub && mx2!=-1){
                    res = max(res, d + mx2);
                }
                if (s!=mx1sub && mx1!=-1){
                    res = max(res, d + mx1);
                }
            }
            cout << res << '\n';
        }
    }
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