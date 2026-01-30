#include <bits/stdc++.h>
#ifdef DEBUG
    #include "debug.h"
#else
    #define debug(...)
#endif
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
void solve(int cas){ 
    int n; cin >> n;
    vector<string> words(n);
    for (auto& a: words) cin >> a;
    string res = words[0];
    for (int i = 1; i < n; i++){
        int m = words[i].size(), l = res.size();
        vector<int> pi(m);
        for (int j = 1, p = 0; j < m; j++){
            while (p > 0 && words[i][p] != words[i][j]) p = pi[p - 1];
            if (words[i][p] == words[i][j]) p++;
            pi[j] = p;
        }
        int p = 0;
        for (int j = max(l - m, 0); j < l; j++){
            while (p > 0 && res[j] != words[i][p]) p = pi[p - 1];
            if (res[j] == words[i][p]) p++;
        }
        res += words[i].substr(p, m - p);
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