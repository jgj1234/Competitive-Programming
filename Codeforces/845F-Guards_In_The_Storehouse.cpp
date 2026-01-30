#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
void solve(int cas){
    int n,m; cin>>n>>m;
    vector<string> grid(n);
    for (auto& a: grid) cin>>a;
    if (n < m){
        vector<string> n1(m, string(n, '.'));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                n1[j][i] = grid[i][j];
            }
        }
        swap(n1, grid);
        swap(n, m);
    }
    //num_cols <= 15
    //dp[i][j][col_mask][row_took][had_empty]
    int dp[n + 1][m + 1][1<<m][2][2];
    for (int i = 0; i < (1 << m); i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                dp[n][0][i][j][k] = 1;
            }
        }
    }
    for (int i = n - 1; i >= 0; i--){
        for (int j = m - 1; j >= 0; j--){
            for (int mask = 0; mask < (1 << m); mask++){
                bool mbit = mask&(1<<j), reset = j == m - 1;
                int nr = j ==  m - 1 ? i + 1: i, nc = (j + 1)%m;
                for (int k = 0; k < 2; k++){
                    for (int l = 0; l < 2; l++){
                        if (grid[i][j] == 'x'){
                            dp[i][j][mask][k][l] = dp[nr][nc][mask^((1&mbit) << j)][0][l];
                            continue;
                        }
                        bool had = mbit || (k == 1);
                        if (had){
                            dp[i][j][mask][k][l] = dp[nr][nc][mask][k && !reset][l] + dp[nr][nc][mask | (1 << j)][!reset][l];
                        }
                        else{
                            if (l == 0){
                                dp[i][j][mask][k][l] = dp[nr][nc][mask][k && !reset][1] + dp[nr][nc][mask | (1 << j)][!reset][l];
                            }
                            else{
                                dp[i][j][mask][k][l] = dp[nr][nc][mask | (1 << j)][!reset][l];
                            }
                        }
                        if (dp[i][j][mask][k][l] >= MOD) dp[i][j][mask][k][l] -= MOD;
                    }
                }
            }
        }
    }
    cout << dp[0][0][0][0][0] << '\n';
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