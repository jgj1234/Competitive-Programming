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
    string s, pat; cin >> s >> pat;
    string t = pat + "#" + s;
    int n = t.size(), m = s.size(), lt = pat.size();
    int l = 0, r = 0;
    vector<int> z(n);
    for (int i = 1; i < n; i++){
        z[i] = max(0, min(z[i - l], r - i + 1));
        while (i + z[i] < n && t[i + z[i]] == t[z[i]]){
            l = i;
            r = i + z[i];
            z[i]++;
        }
    }
    int ct = 0;
    for (int i = 0; i < m; i++){
        if (z[lt + i + 1] == lt) ct++;
    }
    cout << ct << '\n';
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