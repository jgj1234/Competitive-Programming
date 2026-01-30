#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 100005;
struct Matrix{
    ll mat[2][2];
    int n;
    Matrix(){mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;}
    Matrix(int num){
        n = num;
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
    Matrix I(int n){
        Matrix identity(n);
        for (int i = 0; i < n; i++) identity.mat[i][i] = 1;
        return identity;
    }
    ll* operator[](size_t idx) { 
        return mat[idx]; 
    }
    const ll* operator[](size_t idx) const { 
        return mat[idx]; 
    }

    Matrix operator*(const Matrix& other) const{
        Matrix res(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                for (int k = 0; k < n; k++){
                    res.mat[i][j] += (mat[i][k] * other[k][j]) % MOD;
                    if (res[i][j] >= MOD) res[i][j] -= MOD;
                }
            }
        }
        return res;
    }

    Matrix& operator*=(const Matrix& other) {
        *this = (*this) * other;
        return *this;
    }

    Matrix operator+(const Matrix& other) const{
        Matrix res(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                res[i][j] = mat[i][j] + other[i][j];
                if (res[i][j] >= MOD) res[i][j] -= MOD;
            }
        }
        return res;
    }
    Matrix& operator+=(const Matrix& other){
        *this = (*this) + other;
        return *this;
    }
    Matrix expo(ll k);

    ll nth_term(ll k, vector<ll>& start){
        //Start is a vector of first n terms in the recurrence. Advances start by k
        Matrix bef = expo(k);
        ll res = 0;
        int sz = start.size();
        for (int i = 0; i < sz; i++){
            res += (start[i] * bef[0][i]) % MOD;
            if (res >= MOD) res -= MOD;
        }
        return res;
    }
};
Matrix fpow[64];
Matrix fib(2);
pair<ll,ll> tree[4 * N];
ll lazy[4 * N];
int nums[N];
Matrix Matrix::expo(ll k){
    Matrix res = I(n);
    int ct = 0;
    while (k){
        if (k & 1){
            res *= ::fpow[ct];
        }
        ct++;
        k >>= 1;
    }
    return res;
}

void push(int node, int arrLeft, int arrRight){
    Matrix curr = fib.expo(lazy[node]);
    ll nf = ((curr[0][0] * tree[node].first)%MOD + (curr[0][1] * tree[node].second)%MOD)%MOD;
    ll ns = ((curr[1][0] * tree[node].first)%MOD + (curr[1][1] * tree[node].second)%MOD)%MOD;
    tree[node] = make_pair(nf, ns);
    if (arrLeft != arrRight){
        lazy[2 * node + 1] += lazy[node];
        lazy[2 * node + 2] += lazy[node];
    }
    lazy[node] = 0;
}
void build(int node, int left, int right){
    if (left == right){
        Matrix og = fib.expo(nums[left]);
        tree[node] = make_pair(og[0][1], og[1][1]);
        return;
    }
    int mid = (left + right) / 2;
    build(2 * node + 1, left, mid);
    build(2 * node + 2, mid + 1, right);
    tree[node].first = (tree[2 * node + 1].first + tree[2 * node + 2].first)%MOD;
    tree[node].second = (tree[2 * node + 1].second + tree[2 * node + 2].second)%MOD;
}
void upd(int node, int left, int right, int arrLeft, int arrRight, int x){
    if (lazy[node]) push(node, arrLeft, arrRight);
    if (arrLeft > right || arrRight < left) return;
    if (arrLeft >= left && arrRight <= right){
        lazy[node] = x;
        push(node, arrLeft, arrRight);
        return;
    }
    int mid = (arrLeft + arrRight) / 2;
    upd(2 * node + 1, left, right, arrLeft, mid, x);
    upd(2 * node + 2, left, right, mid + 1, arrRight, x);
    tree[node].first = (tree[2 * node + 1].first + tree[2 * node + 2].first)%MOD;
    tree[node].second = (tree[2 * node + 1].second + tree[2 * node + 2].second)%MOD;
}
ll query(int node, int left, int right, int arrLeft, int arrRight){
    if (lazy[node]) push(node, arrLeft, arrRight);
    if (arrLeft > right || arrRight < left) return 0;
    if (arrLeft >= left && arrRight <= right) return tree[node].first;
    int mid = (arrLeft + arrRight) / 2;
    ll l = query(2 * node + 1, left, right, arrLeft, mid), r = query(2 * node + 2, left, right, mid + 1, arrRight);
    tree[node].first = (tree[2 * node + 1].first + tree[2 * node + 2].first)%MOD;
    tree[node].second = (tree[2 * node + 1].second + tree[2 * node + 2].second)%MOD;
    ll res = (l + r);
    if (res >= MOD) res -= MOD;
    return res;
}
void solve(int cas){
    fib.mat[0][0] = 1;
    fib.mat[0][1] = 1;
    fib.mat[1][0] = 1;
    fib.mat[1][1] = 0;
    int n,m; cin>>n>>m;
    for (int i = 0; i < n; i++) cin >> nums[i];
    fpow[0] = fib;
    for (int i = 1; i < 64; i++) fpow[i] = fpow[i - 1] * fpow[i - 1];
    build(0, 0, n - 1);
    while (m--){
        int t; cin>>t;
        if (t == 1){
            int l,r,x; cin>>l>>r>>x;
            --l;--r;
            upd(0,l,r,0,n-1,x);
        }
        else{
            int l,r; cin>>l>>r;
            --l;--r;
            cout << query(0, l, r, 0, n - 1) << '\n';
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