#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 200005;
int nums[N], tree[N << 2][2][2][2];
ll mx;
void Merge(int node, int lnode, int rnode){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                tree[node][i][j][k] = -1;
            }
        }
    }
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                if (j + k == 2) continue;
                for (int l = 0; l < 2; l++){
                    if (tree[lnode][0][i][j] != -1 && tree[rnode][0][k][l] != -1){
                        tree[node][0][i][l] = max(tree[node][0][i][l], tree[lnode][0][i][j] + tree[rnode][0][k][l]);
                    }
                    if (tree[lnode][1][i][j] != -1 && tree[rnode][1][k][l] != -1){
                        tree[node][1][i][l] = max(tree[node][1][i][l], tree[lnode][1][i][j] + tree[rnode][1][k][l]);
                    }
                    if (tree[lnode][0][i][j] != -1 && tree[rnode][1][k][l] != -1){
                        tree[node][1][i][l] = max(tree[node][1][i][l], tree[lnode][0][i][j] + tree[rnode][1][k][l]);
                    }
                    if (tree[lnode][1][i][j] != -1 && tree[rnode][0][k][l] != -1){
                        tree[node][1][i][l] = max(tree[node][1][i][l], tree[lnode][1][i][j] + tree[rnode][0][k][l]);
                    }
                }
            }
        }
    }
}
void Upd(int node, int left, int right, int pos){
    if (left == right){
        tree[node][nums[pos] == mx][1][1] = 1;
        return;
    }
    int mid = (left + right) / 2;
    if (pos <= mid){
        Upd(2 * node + 1, left, mid, pos);
    }
    else{
        Upd(2 * node + 2, mid + 1, right, pos);
    }
    Merge(node, 2 * node + 1, 2 * node + 2);
}
void solve(int cas){  
    int n; cin>>n;
    for (int i = 0; i < n * 4; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                for (int l = 0; l < 2; l++){
                    if (j == 0 && (l + k == 0)){
                        tree[i][j][k][l] = 0;
                        continue;
                    }
                    tree[i][j][k][l] = -1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) cin >> nums[i];
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&] (int i, int j) { return nums[i] > nums[j]; });
    mx = nums[ord[0]];
    ll res = 2 * mx + 1;
    for (int i = 0; i < n; i++){
        Upd(0, 0, n - 1, ord[i]);
        int mx_count = -1;
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                mx_count = max(mx_count, tree[0][1][j][k]);
            }
        }
        res = max(res, nums[ord[i]] + mx + mx_count);
    }
    cout << res << '\n';
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