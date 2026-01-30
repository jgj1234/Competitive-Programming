#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
void solve(int cas){
    //takes less operations to set a lower bit
    int n,q; cin>>n>>q;
    vector<int> nums(n);
    for (auto& a: nums) cin>>a;
    ll o = 0;
    for (int i = 0; i < n; i++) o |= nums[i];
    vector<ll> ans(33);
    ans[32] = LLONG_MAX;
    int ct = __builtin_popcount(o);
    for (int i = ct + 1; i < 32; i++){
        int lb = 0;
        ans[i] = ans[i - 1];
        while (o & (1LL << lb)) lb++;
        for (int j = lb; j >= 0; j--){
            assert(lb <= 31);
            if (o & (1 << j)) continue;
            int pos = 0;
            for (int k = 1; k < n; k++){
                ll c1 = (1LL << j) - (nums[pos] % (1LL << j));
                ll c2 = (1LL << j) - (nums[k] % (1LL << j));
                if (c1 > c2) pos = k;
            }
            ll cost = (1LL << j) - (nums[pos] % (1LL << j));
            ans[i] += cost;
            nums[pos] += cost;
            o = 0;
            for (int k = 0; k < n; k++) o |= nums[k];
        }
    }
    while (q--){
        int b; cin>>b;
        int curr = 0;
        while (ans[curr] <= b) curr++;
        cout << curr - 1 << '\n';
    }
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