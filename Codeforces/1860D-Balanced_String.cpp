#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
int dp[101][101][5001];
const int OFFSET = 2500;
void solve(int cas){  
    string s; cin>>s;
    int n = s.size();
    int zct = count(all(s), '0');
    int oct = n - zct;
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= zct; j++){
            for (int k = 0; k <= 5000; k++){
                dp[i][j][k] = 255;
            }
        }
    }
    dp[n][zct][OFFSET] = 0;
    for (int i = n - 1; i >= 0; i--){
        for (int j = 0; j <= min(zct, i); j++){
            int onesUsed = i - j;
            if (onesUsed > oct) continue;
            for (int k = 0; k <= 5000; k++){
                dp[i][j][k] = 255;
                int val = s[i] - '0';
                if (onesUsed != oct){
                    if (k - j >= 0 && dp[i + 1][j][k - j] != 255){
                        dp[i][j][k] = min(dp[i][j][k], (val ^ 1) + dp[i + 1][j][k - j]);
                    }
                }
                if (j != zct){
                    if (k + onesUsed <= 5000 && dp[i + 1][j + 1][k + onesUsed] != 255){
                        dp[i][j][k] = min(dp[i][j][k], val + dp[i + 1][j + 1][k + onesUsed]);
                    }
                }
            }
        }
    }
    cout << (dp[0][0][OFFSET] / 2) << '\n';
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