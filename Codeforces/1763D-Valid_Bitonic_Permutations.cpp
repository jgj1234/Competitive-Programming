#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
ll comb[105][105];
void solve(int cas){  
    int n,i,j,x,y; cin>>n>>i>>j>>x>>y;
    --i;--j;
    if (x == n){
        if (i == 0){
            cout << 0 << '\n';
            return;
        }
        cout << (comb[y - 1][n - 1 - j] * comb[n - 1 - y][j - i - 1])%MOD << '\n';
        return;
    }
    if (y == n){
        if (j == n - 1){
            cout << 0 << '\n';
            return;
        }
        cout << (comb[x - 1][i] * comb[n - 1 - x][j - i - 1]) % MOD << '\n';
        return;
    }
    ll ends = 0;
    if (x < y){
        if (i > x - 1){
            cout << 0 << '\n';
            return;
        }
        int remj = n - 1 - j - (x - 1 - i);
        if (remj < 0){
            cout << 0 << '\n';
            return;
        }
        ends = (comb[x - 1][i] * comb[y - x - 1][remj])%MOD;
    }
    else{
        if (n - 1 - j > y - 1){
            cout << 0 << '\n';
            return;
        }
        int remi = i - (y - 1 - (n - 1 - j));
        if (remi < 0){
            cout << 0 << '\n';
            return;
        }
        ends = (comb[y - 1][n - 1 - j] * comb[x - y - 1][remi])%MOD;
    }
    ll res = 0;
    for (int k = 1; k < n - 1; k++){
        if ((k < i && x < y) || (k > j && x > y) || (k == i) || (k == j)) continue;
        if (k < i){
            res += ((comb[x - y - 1][j - i - 1] * comb[y - 1][n - 1 - j])%MOD * comb[n - 1 - x][i - k - 1])%MOD;
            if (res >= MOD) res -= MOD;
        }
        else if (k > j){
            res += ((comb[x - 1][i] * comb[y - x - 1][j - i - 1]) % MOD * comb[n - 1 - y][k - j - 1])%MOD;
            if (res >= MOD) res -= MOD;
        }
        else{
            if (y - 1 < n - 1 - j) continue;
            if ((x < y && y - 1 - (i + 1) < 0) || (x > y && x - 1 - (n - j) < 0)) continue;
            int unpicked = max(x, y) - (i + 1 + n - j);
            int rem = n - 1 - max(x, y);
            if (unpicked < 0) continue;
            if (x > y){
                int disty = j - k - 1;
                if (unpicked > disty) continue;
                disty -= unpicked;
                res += (ends * comb[rem][disty])%MOD;
                if (res >= MOD) res -= MOD;
            }
            else{
                int distx = k - i - 1;
                if (unpicked > distx) continue;
                distx -= unpicked;
                res += (ends * comb[rem][distx])%MOD;
                if (res >= MOD) res -= MOD;
            }
        }
    }
    cout << res << '\n';
}
void pre(){
    comb[0][0] = 1;
    for (int i = 1; i < 105; i++){
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++){
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
        }
    }
}
int main(){
    pre();
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