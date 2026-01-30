#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000009
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
template<int MODX>
struct ModInt {
  unsigned x;
  ModInt() : x(0) { }
  ModInt(signed sig) : x(((sig%MODX)+MODX)%MODX) { }
  ModInt(signed long long sig) : x(((sig%MODX)+MODX)%MODX) { }
  int get() const { return (int)x; }
  ModInt pow(ll p) { ModInt res = 1, a = *this; while (p) { if (p & 1) res *= a; a *= a; p >>= 1; } return res; }
  
  ModInt &operator+=(ModInt that) { if ((x += that.x) >= MODX) x -= MODX; return *this; }
  ModInt &operator-=(ModInt that) { if ((x += MODX - that.x) >= MODX) x -= MODX; return *this; }
  ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MODX; if (x < 0) x += MODX; return *this; }
  ModInt &operator/=(ModInt that) { return (*this) *= that.pow(MODX - 2); }
  
  ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
  ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
  ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
  ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
  bool operator<(ModInt that) const { return x < that.x; }
  friend ostream& operator<<(ostream &os, ModInt a) { os << a.x; return os; }
};
typedef ModInt<MOD> mint;
const int N = 300005;
int n,m;
ll nums[N];
mint fib[N], pref[N], tree[N<<2], l1[N<<2], l2[N<<2];
void build_tree(int node, int left, int right){
    if (left == right){
        tree[node] = nums[left];
        return;
    }
    int mid = (left + right)/2;
    build_tree(2*node+1,left,mid);
    build_tree(2*node+2,mid+1,right);
    tree[node] = tree[2*node+1] + tree[2*node+2];
}
void push(int node, int left, int right){
    if (left == right){
        tree[node] += l1[node];
        l1[node] = l2[node] = 0;
        return;
    }
    ll sz = right - left + 1;
    mint ad = (l1[node]*fib[sz]) + (l2[node]*pref[sz-1]);
    tree[node] += ad;
    l1[2*node+1] += l1[node];
    l2[2*node+1] += l2[node];
    if (left + 1 == right){
        l1[2*node+2] += l2[node];
    }
    else{
        int diff = (left + right)/2 - left + 1;
        l1[2*node+2] += l1[node]*fib[diff-1] + l2[node]*fib[diff];
        l2[2*node+2] += l1[node]*fib[diff] + l2[node]*fib[diff+1];
    }
    l1[node] = l2[node] = 0;
}
void upd(int node, int l, int r, int al, int ar){
    if (l1[node].x) push(node, al, ar);
    if (al > r || ar < l) return;
    if (al >= l && ar <= r){
        if (al == ar){
            tree[node] += fib[al - l + 1];
            return;
        }
        l1[node] = fib[al - l + 1]; l2[node] = fib[al - l + 2];
        push(node, al, ar);
        return;
    }
    int mid = (al + ar)/2;
    upd(2*node+1,l,r,al,mid);
    upd(2*node+2,l,r,mid+1,ar);
    tree[node] = tree[2*node+1] + tree[2*node+2];
}
mint query(int node, int l, int r, int al, int ar){
    if (l1[node].x) push(node, al, ar);
    if (al >= l && ar <= r) return tree[node];
    if (al > r || ar < l) return 0;
    int mid = (al + ar)/2;
    mint left = query(2*node+1,l,r,al,mid);
    mint right = query(2*node+2,l,r,mid+1,ar);
    return left + right;
}
void solve(int cas){  
    cin>>n>>m;
    fib[1] = 1;
    for (int i = 2; i < N; i++) fib[i] = (fib[i-1] + fib[i-2]);
    for (int i = 1; i < N; i++) pref[i] = fib[i] + pref[i-1];
    for (int i = 0; i < n; i++) cin>>nums[i];
    build_tree(0,0,n-1);
    for (int i = 0; i < m; i++){
        int t, l, r; cin >> t >> l >> r;
        --l; --r;
        if (t == 1){
            upd(0,l,r,0,n-1);
        }
        else{
            cout << query(0,l,r,0,n-1) << '\n';
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