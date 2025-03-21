#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct Node{
    int mx = 0, mxi = 0;
    Node(){}
};
struct LazySegmentTree{
    vector<ll> lazy, nums, order;
    vector<Node> tree;
    LazySegmentTree(int n, vector<ll>& c, vector<ll>& o){
        nums = c;
        order = o;
        lazy.resize(4*n);
        tree.resize(4*n);
        build_tree(0,0,n-1);
    }
    void merge(Node& main, Node& left, Node& right){
        if (left.mx >= right.mx){
            main.mx = left.mx;
            main.mxi = left.mxi;
        }
        else{
            main.mx = right.mx;
            main.mxi = right.mxi;
        }
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node].mx = nums[left];
            tree[node].mxi = order[left];
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
    void push(int node, int left, int right){
        tree[node].mx += lazy[node];
        if (left!=right){
            lazy[2*node+1] += lazy[node];
            lazy[2*node+2] += lazy[node];
        }
        lazy[node] = 0;
    }
    void upd(int node, int left, int right, int arrLeft, int arrRight, int inc){
        if (lazy[node]) push(node, arrLeft, arrRight);
        if (arrLeft > right || arrRight < left) return;
        if (arrLeft >= left && arrRight <= right){
            tree[node].mx += inc;
            if (arrLeft != arrRight){
                lazy[2*node+1] += inc;
                lazy[2*node+2] += inc;
            }
            return;
        }
        int mid = (arrLeft + arrRight)>>1;
        upd(2*node+1,left,right,arrLeft,mid,inc);
        upd(2*node+2,left,right,mid+1,arrRight,inc);
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }    
    Node query(int node, int left, int right, int arrLeft, int arrRight) {
        if (lazy[node]) push(node, arrLeft, arrRight);
        if (arrLeft > right || arrRight < left){
            Node nd; nd.mx = -1;
            return nd;
        }
        if (arrLeft >= left && arrRight <= right){
            return tree[node];
        }
        Node res;
        int mid = (arrLeft + arrRight)>>1;
        Node l = query(2*node+1,left,right,arrLeft,mid), r = query(2*node+2,left,right,mid+1,arrRight);
        merge(res,l,r);
        return res;
    }
};
void solve(int cas){ 
    int n,q; cin>>n>>q;
    vector<ll> col(n);
    for (auto& a: col) cin>>a;
    vector<vector<ll>> g(n);
    for (int i = 0; i < n - 1; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vector<vector<ll>> jump(n, vector<ll> (20));
    vector<ll> tin(n), tout(n), depths(n), pref(n), ord(n);
    int tim = 0;
    auto dfs = [&] (auto&& self, int node, int parent, int depth, int p) -> void{
        tin[node] = tim++;
        ord[tin[node]] = node;
        if (col[node]==1) p++;
        pref[tin[node]] = p;
        depths[node] = depth;
        jump[node][0] = parent;
        for (int i = 1; i < 20; i++) jump[node][i] = jump[jump[node][i-1]][i-1];
        for (int neighbor: g[node]){
            if (neighbor!=parent){
                self(self,neighbor,node, depth+1,p);
            }
        }
        tout[node] = tim;
    };
    dfs(dfs,0,0,0,0);
    auto anc = [&] (int u, int v) -> bool{
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    };
    auto lca = [&] (int u, int v) -> int{
        if (depths[u] > depths[v]) swap(u, v);
        if (anc(u,v)) return u;
        for (int j = 19; j >= 0; j--){
            if (!anc(jump[u][j], v)) u = jump[u][j];
        }
        return jump[u][0];
    };
    auto kth = [&] (int u, int k) -> int{
        for (int j = 19; j >= 0; j--){
            if (k&(1<<j)) u = jump[u][j];
        }
        return u;
    };
    LazySegmentTree segTree(n, pref, ord);
    int cnt_black = accumulate(all(col), 0);
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>, greater<pair<ll,ll>>> min_depth;
    priority_queue<pair<ll,ll>> max_depth;
    for (int i = 0; i < n; i++){
        if (col[i]==1){
            min_depth.push(make_pair(depths[i], i));
            max_depth.push(make_pair(depths[i], i));
        }
    }
    while (q--){
        int x; cin>>x;
        --x;
        segTree.upd(0,tin[x],tout[x]-1,0,n-1,col[x]==0?1:-1);
        col[x]^=1;
        if (col[x]==0){
            cnt_black--;
        }
        else{
            cnt_black++;
        }
        if (col[x]==1){
            min_depth.push(make_pair(depths[x], x));
            max_depth.push(make_pair(depths[x], x));
        }
        while (!min_depth.empty() && col[min_depth.top().second]==0) min_depth.pop();
        while (!max_depth.empty() && col[max_depth.top().second]==0) max_depth.pop();
        if (cnt_black==0){
            cout << "No\n";
            continue;
        }
        else if (cnt_black==1){
            cout << "Yes\n";
            continue;
        }
        int l = min_depth.top().second, a = max_depth.top().second;
        if (!anc(l, a) || depths[a] - depths[l] + 1 > cnt_black){
            cout << "No\n";
            continue;
        }
        int lv = segTree.query(0,tin[l],tin[l],0,n-1).mx, av = segTree.query(0,tin[a],tin[a],0,n-1).mx;
        int turn1 = av - lv + 1;
        if (turn1==cnt_black){
            cout << "Yes\n";
            continue;
        }
        else if (turn1!=depths[a]-depths[l]+1){
            cout << "No\n";
            continue;
        }
        int skip = kth(a, depths[a] - depths[l] - 1);
        Node mx1 = segTree.query(0,tin[l],tin[skip]-1,0,n-1), mx2 = segTree.query(0,tout[skip],tout[l]-1,0,n-1);
        if (max(mx1.mx,mx2.mx)==lv){
            cout << "No\n";
            continue;
        }
        Node r;
        segTree.merge(r, mx1, mx2);
        int mx = r.mx, mxi = r.mxi;
        if (mx - lv!=depths[mxi]-depths[l]){
            cout << "No\n";
            continue;
        }
        assert(depths[mxi] > depths[l]);
        if ((mx + av - 2*lv + 1)== cnt_black){
            cout << "Yes\n";
        }
        else{
            cout << "No\n";
        }
    }
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