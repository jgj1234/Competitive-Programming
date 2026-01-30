#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 1e6 + 5;
int pi[N], fast_pi[N][26];
void solve(int cas){  
    string s,t; cin >> s >> t;
    int n = s.size(), m = t.size();
    for (int i = 1, j = 0; i < m; i++){
        while (j > 0 && t[i] != t[j]) j = pi[j - 1];
        if (t[i] == t[j]) j++;
        pi[i] = j;
    }
    for (int i = 0; i < m; i++){
        fast_pi[i][t[i] - 'a'] = i + 1;
        if (i > 0){
            for (int j = 0; j < 26; j++){
                if (fast_pi[i][j] == 0) fast_pi[i][j] = fast_pi[pi[i - 1]][j];
            }
        }
    }
    vector<int> dp(m);
    for (int i = n - 1; i >= 0; i--){
        vector<int> ndp(m);
        for (int j = 0; j < m; j++){
            if (s[i] != '?'){
                int nxt = fast_pi[j][s[i] - 'a'];
                if (nxt == m){
                    ndp[j] = 1 + dp[pi[m - 1]];
                }
                else{
                    ndp[j] =  dp[nxt];
                }
            }
            else{
                for (int k = 0; k < 26; k++){
                    int nxt = fast_pi[j][k];
                    if (nxt == m){
                        ndp[j] = max(ndp[j], 1 + dp[pi[m - 1]]);
                    }
                    else{
                        ndp[j] = max(ndp[j], dp[nxt]);
                    }
                }
            }
        }
        dp = move(ndp);
    }
    cout << dp[0] << '\n';
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