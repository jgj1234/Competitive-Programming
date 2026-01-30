#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 1005;
int pi[N], nxt[N][26], dp[N][100];
void solve(int cas){  
    int m; cin >> m;
    string s; cin>>s;
    int n = s.size();
    for (int i = 1, j = 0; i < n; i++){
        while (j > 0 && s[j] != s[i]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    for (int i = 0; i < n; i++){
        if (i > 0){
            for (int j = 0; j < 26; j++){
                nxt[i][j] = nxt[pi[i - 1]][j];
            }
        }
        nxt[i][s[i] - 'A'] = i + 1;
    }
    for (int i = 0; i < n; i++) dp[m][i] = 1;
    for (int i = m - 1; i >= 0; i--){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < 26; k++){
                if (nxt[j][k] != n){
                    dp[i][j] += dp[i + 1][nxt[j][k]];
                    if (dp[i][j] >= MOD) dp[i][j] -= MOD;
                }
            }
        }
    }
    ll res = 1;
    for (int i = 0; i < m; i++) res = (res * 26) % MOD;
    res = (res - dp[0][0] + MOD) % MOD;
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