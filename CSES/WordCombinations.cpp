#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 5005, M = 1000001;
int dp[N];
int trie[M][26];
int e[M];
int p = 1;
void solve(int cas){  
    string s; cin >> s;
    int n = s.size();
    s = "#" + s;
    int k; cin >> k;
    vector<string> st(k);
    for (auto& a: st) cin >> a;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < 26; j++){
            trie[i][j] = -1;
            e[i] = 0;
        }
    }
    for (int i = 0; i < k; i++){
        int curr = 0;
        for (int j = st[i].size() - 1; j >= 0; j--){
            if (trie[curr][st[i][j] - 'a'] == -1){
                trie[curr][st[i][j] - 'a'] = p++;
            }
            curr = trie[curr][st[i][j] - 'a'];
        }
        e[curr] = 1;
    }
    dp[0] = 1;
    for (int i = 1; i <= n; i++){
        int p = 0;
        for (int j = i; j >= 1; j--){
            if (trie[p][s[j] - 'a'] == -1){
                break;
            }
            p = trie[p][s[j] - 'a'];
            if (e[p]){
                dp[i] += dp[j - 1];
                if (dp[i] >= MOD) dp[i] -= MOD;
            }
        }
    }
    cout << dp[n] << '\n';
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