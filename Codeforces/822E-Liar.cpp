#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> d;
const ll b = 431414;
const ll mod = MOD;
const int N = 100005, X = 31;
ll pw[N], inv[N], b1[N], b2[N], dp[N][X];
ll bp(ll a, ll bb){
    ll res = 1, curr = a;
    while (bb){
        if (bb&1){
            res = (res * curr)%mod;
        }
        curr = (curr * curr)%mod;
        bb >>= 1;
    }
    return res;
}
void solve(int cas){
    int n; cin>>n;
    string s; cin>>s;
    int m; cin>>m;
    string t; cin>>t;
    int x; cin>>x;
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = (pw[i - 1] * b)%mod;
    for (int i = 0; i < N; i++){
        inv[i] = bp(pw[i], mod - 2); 
    }
    for (int i = 0; i < n; i++){
        b1[i] = (pw[i + 1] * (s[i] - 'a'))%mod;
        if (i){
            b1[i] = (b1[i] + b1[i - 1])%mod;
        }
    }
    for (int i = 0; i < m; i++){
        b2[i] = (pw[i + 1] * (t[i] - 'a'))%mod;
        if (i){
            b2[i] = (b2[i] + b2[i - 1])%mod;
        }
    }
    auto getS = [&] (int l, int r) -> ll{
        ll sm = (b1[r] - (l > 0 ? b1[l - 1] : 0)+ mod)%mod;
        return (sm * inv[l])%mod;
    };
    auto getT = [&] (int l, int r) -> ll{
        ll sm = (b2[r] - (l > 0 ? b2[l - 1] : 0) + mod)%mod;
        return (sm * inv[l])%mod;
    };
    auto lcp = [&] (int i, int j) -> int{
        if (s[i] != t[j]) return 0;
        int lp = 1, rp = min(m - 1 - j, n - 1 - i);
        while (lp <= rp){
            int mid = (lp + rp)/2;
            if (getS(i, i + mid) == getT(j, j + mid)){
                lp = mid + 1;
            }
            else{
                rp = mid - 1;
            }
        }
        return lp;
    };
    //dp[i][j] = Farthest in t we could get with s[i..n] left with j strings took
    for (int i = 0; i < n; i++){
        for (int j = 0; j < x; j++){
            dp[i][j] = INT_MIN;
        }
    }
    dp[0][x] = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= x; j++){
            if (dp[i][j] == INT_MIN) continue;
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            if (j && dp[i][j] != m){
                int y = lcp(i, dp[i][j]);
                if (y)
                    dp[i + y][j - 1] = max(dp[i + y][j - 1], dp[i][j] + y);
            }
        }
    }
    for (int i = 0; i <= x; i++){
        if (dp[n][i] == m){
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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