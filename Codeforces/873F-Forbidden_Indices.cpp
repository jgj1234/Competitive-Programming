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
const int N = 4e5 + 5;
int p[N], c[N], tp[N], tc[N], ct[N], lcp[N], pos[N];
void solve(int cas){ 
    int n; cin >> n;
    string s, forb; cin >> s >> forb;
    reverse(all(s));
    reverse(all(forb));
    s += "$";
    forb += "1";
    n++;
    for (int i = 0; i < n; i++) ct[s[i]]++;
    for (int i = 1; i < 512; i++) ct[i] += ct[i - 1];
    for (int i = 0; i < n; i++){
        p[--ct[s[i]]] = i;
    }
    int classes = 1;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++){
        if (s[p[i]] != s[p[i - 1]]){
            classes++;
        }
        c[p[i]] = classes - 1;
    }
    for (int k = 1; k < n; k <<= 1){
        for (int i = 0; i < n; i++){
            tp[i] = p[i] - k;
            if (tp[i] < 0) tp[i] += n;
        }
        fill(ct, ct + classes, 0);
        for (int i = 0; i < n; i++){
            ct[c[i]]++;
        }
        for (int i = 1; i < classes; i++) ct[i] += ct[i - 1];
        for (int i = n - 1; i >= 0; i--){
            p[--ct[c[tp[i]]]] = tp[i];
        }
        for (int i = 0; i < n; i++) tc[i] = c[i];
        c[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++){
            if ((tc[p[i]] != tc[p[i - 1]]) || (tc[(p[i] + k) % n] != tc[(p[i - 1] + k) % n])){
                classes++;
            }
            c[p[i]] = classes - 1;
        }
    }
    for (int i = 0; i < n; i++){
        pos[p[i]] = i;
    }
    int pointer = 0;
    for (int i = 0; i < n; i++){
        if (pos[i] == n - 1){
            pointer = 0;
            continue;
        }
        int nxt = p[pos[i] + 1];
        while (i + pointer < n && nxt + pointer < n && s[i + pointer] == s[nxt + pointer]) pointer++;
        lcp[pos[i]] = pointer;
        pointer = max(pointer - 1, 0);
    }
    vector<ll> arr;
    int mn = 1e9;
    for (int i = 0; i < n - 1; i++){
        mn = min(mn, lcp[i]);
        if (forb[p[i + 1]] == '0'){
            arr.emplace_back(mn);
            mn = 1e9;
        }
    }
    vector<pair<ll,ll>> stk;
    ll res = 0;
    for (int i = 0; i < n - 1; i++){
        if (forb[i] == '0'){
            res = n - 1 - i;
            break;
        }
    }
    if (res == 0){
        cout << 0 << '\n';
        return;
    }
    for (int i = 0; i < arr.size(); i++){
        int stretch = i;
        while (!stk.empty() && stk.back().first >= arr[i]){
            auto [h, idx] = stk.back(); stk.pop_back();
            stretch = idx;
            res = max(res, h * (i - idx + 1));
        }
        stk.emplace_back(arr[i], stretch);
    }
    while (!stk.empty()){
        auto [h, idx] = stk.back(); stk.pop_back();
        res = max(res, h * ((int) arr.size() - idx + 1));
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