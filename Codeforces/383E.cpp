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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll dp[1<<24];
void solve(int cas){  
    int n; cin>>n;
    memset(dp,0,sizeof dp);
    for (int i = 0; i < n; i++){
        string s; cin>>s;
        int mask = (1<<(s[0]-'a'))|(1<<(s[1]-'a'))|(1<<(s[2]-'a'));
        dp[mask^((1<<24)-1)]++;
    }
    for (int i = 0; i < 24; i++){
        for (int mask = (1<<24) - 1; mask >= 0; mask--){
            if ((mask&(1<<i))==0){
                dp[mask] += dp[mask|(1<<i)];
            }
        }
    }
    ll res = 0;
    for (int i = 0; i < (1<<24); i++){
        res^=(n - dp[i])*(n - dp[i]);
    }
    cout << res << '\n';
    
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}