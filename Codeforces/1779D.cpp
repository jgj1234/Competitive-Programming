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
void solve(int cas){ 
    int n; cin>>n;
    vector<ll> a(n), b(n);
    for (auto& x: a) cin>>x;
    for (auto& x: b) cin>>x;
    int x; cin>>x;
    vector<ll> raz(x);
    for (auto& m: raz) cin>>m;
    for (int i = 0; i < n; i++){
        if (a[i] < b[i]){
            cout << "NO\n";
            return;
        }
    }
    map<ll,vector<ll>> mp;
    for (int i = 0; i < n; i++){
        if (a[i]!=b[i]){
            mp[b[i]].emplace_back(i);
        }
    }
    map<ll,ll> ct;
    for (int i = 0; i < x; i++){
        ct[raz[i]]++;
    }
    SparseTable st(b, [] (const ll& u, const ll& v){
        return max(u,v);
    });
    for (auto& [num, pv]: mp){
        int need = 1;
        for (int j = 1; j < pv.size(); j++){
            if (st.get(pv[j-1], pv[j]) > num){
                need++;
            }
        }
        if (need > ct[num]){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
