#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 200005;
int tree[4 * N], nums[N];
vector<int> pos[N], occs[N];
int n,q;
void upd(int node, int left, int right, int pos, int val){
    if (left == right){
        tree[node] = val;
        return;
    }
    int mid = (left + right) / 2;
    if (pos <= mid){
        upd(2 * node + 1, left, mid, pos, val);
    }
    else{
        upd(2 * node + 2, mid + 1, right, pos, val);
    }
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}
int bef(int node, int left, int right, int pos){
    if (right <= pos) return tree[node];
    if (left > pos) return 0;
    int mid = (left + right) / 2;
    return bef(2 * node + 1, left, mid, pos) + bef(2 * node + 2, mid + 1, right, pos);
}
int query(int node, int left, int right, int k){
    if (k > tree[node]) return n;
    if (left == right) return left;
    int mid = (left + right) / 2;
    if (tree[2 * node + 1] >= k){
        return query(2 * node + 1, left, mid, k);
    }
    return query(2 * node + 2, mid + 1, right, k - tree[2 * node + 1]);
}
void solve(int cas){  
    cin>>n>>q;
    for (int i = 0; i < n; i++) cin >> nums[i];
    for (int i = 1; i <= n; i++){
        pos[i].resize((n + i - 1) / i + 1);
    }
    for (int i = 1; i <= n; i++){
        pos[i][1] = 0;
    }
    for (int i = 0; i < n; i++){
        occs[nums[i]].emplace_back(i);
    }
    for (int i = 0; i < n; i++){
        upd(0, 0, n - 1, i, 1);
    }
    for (int level = 2; level <= n; level++){
        for (int k = 1; k <= n; k++){
            if (pos[k].size() <= level) break;
            if (pos[k][level - 1] == n){
                pos[k][level] = n;
                continue;
            }
            int b = bef(0, 0, n - 1, pos[k][level - 1] - 1);
            int nxt = min(n, query(0, 0, n - 1, k + b) + 1);
            pos[k][level] = nxt;
        }
        for (int x: occs[level - 1]){
            upd(0, 0, n - 1, x, 0);
        }
    }
    while (q--){
        int i, x; cin >> i >> x;
        --i;
        int lp = 1, rp = (n + x - 1) / x;
        while (lp <= rp){
            int mid = (lp + rp) / 2;
            if (pos[x][mid] <= i){
                lp = mid + 1;
            }
            else{
                rp = mid - 1;
            }
        }
        if (rp <= nums[i]){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
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