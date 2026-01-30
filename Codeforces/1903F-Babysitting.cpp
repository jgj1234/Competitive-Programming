#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct twosat{
    vector<vector<int>> g;
    vector<int> col, low, tin, stk, tree;
    vector<bool> in;
    int timer = 1, scc = 0;
    int curr;
    twosat(int n){
        g.resize(4*n);
        col.resize(4*n);
        in.resize(4*n);
        low.resize(4*n);
        tin.resize(4*n);
        tree.resize(4*n);
        curr = n;
        build_tree(0,0,n-1);
    }
    void build_tree(int node, int l, int r){
        if (l == r){
            tree[node] = l;
            return;
        }
        int mid = (l + r)/2;
        build_tree(2*node+1,l,mid);
        build_tree(2*node+2,mid+1,r);
        tree[node] = curr++;
        add_disjunction(tree[2*node+1], false, tree[node], true);
        add_disjunction(tree[2*node+2], false, tree[node], true);
    }
    void add_segment(int node, int l, int r, int al, int ar, int x){
        if (al > r || ar < l) return;
        if (al >= l && ar <= r){
            add_disjunction(x, false, tree[node], false);
            return;
        }
        int mid = (al + ar)/2;
        add_segment(2*node+1,l,r,al,mid,x);
        add_segment(2*node+2,l,r,mid+1,ar,x);
    }
    void add_disjunction(int a, bool aa, int b, bool bb){
        g[2 * a + (aa ^ 1)].emplace_back(2 * b + bb);
        g[2 * b + (bb ^ 1)].emplace_back(2 * a + aa);
    }
    void dfs(int node){
        tin[node] = low[node] = timer++;
        in[node] = true;
        stk.emplace_back(node);
        for (int neighbor: g[node]){
            if (!tin[neighbor]){
                dfs(neighbor);
                low[node] = min(low[node], low[neighbor]);
            }
            else if (in[neighbor]) {
                low[node] = min(low[node], tin[neighbor]);
            }
        }
        if (low[node] == tin[node]){
            while (stk.back() != node){
                col[stk.back()] = scc;
                in[stk.back()] = false;
                stk.pop_back();
            }
            col[node] = scc++;
            in[node] = false;
            stk.pop_back();
        }
    }
    bool solve(){
        for (int i = 0; i < g.size(); i++){
            if (!tin[i]) dfs(i);
        }
        for (int i = 0; i < col.size(); i+=2){
            if (col[i] == col[i+1]) return false;
        }
        return true;
    }
};
void solve(int cas){
    int n,m; cin>>n>>m;
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        edges[i] = make_pair(u, v);
    }
    auto check = [&] (int mid) -> bool{
        twosat ts(n);
        for (auto& [u, v]: edges){
            ts.add_disjunction(u, true, v, true);
        }
        for (int i = 0; i < n; i++){
            int bef = max(0, i - mid + 1);
            if (bef < i){
                ts.add_segment(0,bef,i-1,0,n-1,i);
            }
            int aft = min(n - 1, i + mid - 1);
            if (i < aft){
                ts.add_segment(0,i+1,aft,0,n-1,i);
            }
        }
        return ts.solve();
    };
    int lp = 1, rp = n;
    while (lp <= rp){
        int mid = (lp + rp)/2;
        if (check(mid)){
            lp = mid + 1;
        }
        else{
            rp = mid - 1;
        }
    }
    cout << rp << '\n';
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