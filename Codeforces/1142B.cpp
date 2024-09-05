#include <bits/stdc++.h>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
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
template <typename T, typename F>
class SparseTable {
 public:
  int n;
  vector<vector<T>> mat;
  F func;
 
  SparseTable(const vector<T>& a, const F& f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
 
  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};
void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    vector<ll> perm(n), a(m);
    for (int i = 0; i < n; i++) cin>>perm[i];
    for (int i = 0; i < m; i++) cin>>a[i];
    vector<ll> nxt(n+1);
    for (int i = 0; i < n; i++){
        nxt[perm[i]] = perm[(i+1)%n];
    }
    int lg = 32 - __builtin_clz(m);
    vector<int> occ(n+1,-1);
    vector<vector<int>> jump(m,vector<int>(lg,-1));
    for (int i = m - 1; i>=0; i--){
        if (occ[nxt[a[i]]]!=-1){
            jump[i][0] = occ[nxt[a[i]]];
        }
        occ[a[i]] = i;
    }
    for (int j = 1; j < lg; j++){
        for (int i = 0; i < m; i++){
            if (jump[i][j-1]!=-1){
                jump[i][j] = jump[jump[i][j-1]][j-1];
            }
        }
    }
    vector<ll> mn(m,INT_MAX);
    for (int i = 0; i < m; i++){
        int curr = i;
        for (int j = 0; j < lg; j++){
            if (((n-1)&(1<<j)) && curr!=-1){
                curr = jump[curr][j];
            }
        }
        if (curr!=-1){
            mn[i] = curr;
        }
    }
    SparseTable st(mn, [] (const ll& a, const ll& b){
        return min(a,b);
    });
    while (q--){
        int l,r;
        cin>>l>>r;
        --l;--r;
        if (st.get(l,r)<=r){
            cout<<1;
        }
        else{
            cout<<0;
        }
    }
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    while (t--){
        solve();
    }
}