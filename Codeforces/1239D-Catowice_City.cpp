#include <bits/stdc++.h>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 1000005;
vector<int> g[N], rev[N], order;
bool vis[N];
int col[N], deg[N];
int c = 0;
void dfs1(int node){
    vis[node] = true;
    for (int neighbor: g[node]){
        if (!vis[neighbor]){
            dfs1(neighbor);
        }
    }
    order.emplace_back(node);
}
void dfs2(int node){
    vis[node] = true;
    col[node] = c;
    for (int neighbor: rev[node]){
        if (!vis[neighbor]){
            dfs2(neighbor);
        }
    }
}
void solve(int cas){
    int n,m; cin>>n>>m;
    for (int i = 0; i < n; i++){
        g[i].clear();
        rev[i].clear();
        vis[i] = false;
        deg[i] = 0;
        col[i] = 0;
        c = 0;
    }
    for (int i = 0; i < m; i++){
        int a,b; cin>>a>>b;
        --a;--b;
        if (a != b){
            g[a].emplace_back(b);
            rev[b].emplace_back(a);
        }
    }
    for (int i = 0; i < n; i++){
        if (!vis[i]) dfs1(i);
    }
    for (int i = 0; i < n; i++) vis[i] = false;
    while (!order.empty()){
        int x = order.back(); order.pop_back();
        if (!vis[x]){
            dfs2(x);
            c++;
        }
    }
    if (c == 1){
        cout << "No\n";
        return;
    }
    for (int i = 0; i < n; i++){
        for (int x: g[i]){
            if (col[x] != col[i]){
                deg[col[x]]++;
            }
        }
    }
    cout << "Yes\n";
    int found = -1;
    for (int i = 0; i < c; i++){
        if (deg[i]==0){
            found = i;
            break;
        }
    }
    assert(found != -1);
    vector<int> jury, cats;
    for (int i = 0; i < n; i++){
        if (col[i] == found){
            cats.emplace_back(i+1);
        }
        else{
            jury.emplace_back(i + 1);
        }
    }
    cout << jury.size() << " " << cats.size() << '\n';
    for (auto& x: jury) cout << x << " ";
    cout << '\n';
    for (auto& x: cats) cout << x << " ";
    cout << '\n';
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