#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct Matrix {
    vector<vector<ll>> mat;
    int n;
    Matrix(int num) {
        n = num;
        mat.resize(n, vector<ll>(n));
    }

    static Matrix I(int sz) {
        Matrix identity(sz);
        for (int i = 0; i < sz; ++i) identity.mat[i][i] = 1;
        return identity;
    }

    vector<ll>& operator[](size_t idx) { return mat[idx]; }
    const vector<ll>& operator[](size_t idx) const { return mat[idx]; }

    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                if (mat[i][k] == 0) continue;
                ll aik = mat[i][k];
                for (int j = 0; j < n; ++j) {
                    res.mat[i][j] = (res.mat[i][j] + aik * other.mat[k][j]) % (MOD - 1);
                }
            }
        }
        return res;
    }

    Matrix& operator*=(const Matrix& other) {
        *this = (*this) * other;
        return *this;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix res(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                res.mat[i][j] = (mat[i][j] + other.mat[i][j]) % MOD;
        return res;
    }

    Matrix& operator+=(const Matrix& other) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                mat[i][j] = (mat[i][j] + other.mat[i][j]) % MOD;
        return *this;
    }

    Matrix expo(long long k) const {
        Matrix res = I(n);
        Matrix mult = *this;
        while (k) {
            if (k & 1) res *= mult;
            mult *= mult;
            k >>= 1;
        }
        return res;
    }

    ll nth_term(long long k, const vector<ll>& start) const {
        Matrix bef = expo(k);
        ll res = 0;
        int sz = start.size();
        for (int i = 0; i < sz; ++i) {
            res = (res + (start[i] * bef.mat[0][i]) % (MOD - 1)) % (MOD - 1);
        }
        return res;
    }
};
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
void solve(int cas){
    ll n,f1,f2,f3,c;cin>>n>>f1>>f2>>f3>>c;
    set<ll> facs;
    map<ll,ll> f1fac, f2fac, f3fac, cfac;
    for (int i = 2; i * i <= f1; i++){
        if (f1 % i == 0){
            facs.insert(i);
            while (f1 % i == 0){
                f1fac[i]++;
                f1 /= i;
            }
        }
    }
    if (f1 > 1){
        facs.insert(f1);
        f1fac[f1]++;
    }
    for (int i = 2; i * i <= f2; i++){
        if (f2 % i == 0){
            facs.insert(i);
            while (f2 % i == 0){
                f2fac[i]++;
                f2 /= i;
            }
        }
    }
    if (f2 > 1){
        facs.insert(f2);
        f2fac[f2]++;
    }
    for (int i = 2; i * i <= f3; i++){
        if (f3 % i == 0){
            facs.insert(i);
            while (f3 % i == 0){
                f3fac[i]++;
                f3 /= i;
            }
        }
    }
    if (f3 > 1){
        facs.insert(f3);
        f3fac[f3]++;
    }
    for (int i = 2; i * i <= c; i++){
        if (c % i == 0){
            facs.insert(i);
            while (c % i == 0){
                cfac[i]++;
                c /= i;
            }
        }
    }
    if (c > 1){
        facs.insert(c);
        cfac[c]++;
    }
    ll res = 1;
    for (ll x: facs){
        vector<ll> start = {f3fac[x], f2fac[x], f1fac[x], 2, 2};
        Matrix mat(5);
        mat[0][0] = 1; mat[0][1] = 1; mat[0][2] = 1; mat[0][3] = cfac[x];
        mat[1][0] = 1; mat[2][1] = 1;
        mat[3][3] = 1; mat[3][4] = 1;
        mat[4][4] = 1;
        ll tot_times = mat.nth_term(n - 3, start);
        res *= binpow(x, tot_times, MOD);
        res %= MOD;
    }
    cout << res << '\n';
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