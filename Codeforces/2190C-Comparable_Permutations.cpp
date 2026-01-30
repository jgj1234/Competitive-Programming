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
    int n; cin>>n;
    auto Ask = [&] (int i, int j) -> int{
        if (i < 0 || j < 0){
            return -1;
        }
        cout << "? " << i << " " << j << endl;
        int x; cin>>x;
        return x;
    };

    int pos = n;
    while (pos > 1 && Ask(pos - 1, pos) == 1) pos--;
    if (pos == 1){
        cout << "! " << -1 << endl;
        return;
    }
    int seg2 = pos;
    --pos;
    while (pos > 1 && Ask(pos - 1, pos) == 0) --pos;
    if (pos == 1){
        cout << "! " << -1 << endl;
        return;
    }
    int left = pos - 1;
    int lp = seg2, rp = n;
    int right = n;
    vector<ll> res(n + 1);
    iota(all(res), 0);
    int p = pos;
    int l = seg2 - 1, r = seg2;
    while (l > left || r <= right){
        if (l > left && r <= right){
            if (Ask(l, r) == 1){
                res[p++] = l--;
            }
            else{
                res[p++] = r++;
            }
        }
        else if (l > left){
            res[p++] = l--;
        }
        else{
            res[p++] = r++;
        }
    }
    lp = pos, rp = right;
    while (lp <= rp){
        int mid = (lp + rp) / 2;
        if (Ask(left, res[mid]) == 0){
            lp = mid + 1;
        }
        else{
            rp = mid - 1;
        }
    }
    swap(res[left], res[lp]);
    cout << "! ";
    for (int i = 1; i <= n; i++) cout << res[i] << " ";
    cout << endl;
}
int main(){
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