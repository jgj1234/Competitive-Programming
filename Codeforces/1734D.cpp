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
void solve(int cas){
    ll n,k; cin>>n>>k;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    --k;
    if (k==0 || k==n-1){
        cout <<"YES\n"; return;
    }
    vector<ll> pref(n), suff(n);
    ll pmx = 0, last = k, curr = 0;
    queue<vector<ll>> prefq, suffq;
    for (int i = k - 1; i >= 0; i--){
        curr += nums[i];
        pref[i] = curr;
        if (curr >= pmx){
            ll mn = 0, l = (last==k ? 0 : pref[last]);
            for (int j = i + 1; j < last; j++){
                mn = min(mn, pref[j] - l);
            }
            prefq.push(vector<ll> {i,mn, curr - pmx});
            last = i;
            pmx = curr;
        }
    }
    ll smx = 0;
    last = 0, curr = 0;
    for (int i = k + 1; i < n; i++){
        curr += nums[i];
        suff[i] = curr;
        if (curr >= smx){
            ll mn = 0, l = (last==0?0: suff[last]);
            for (int j = i - 1; j > last; j--){
                mn = min(mn, suff[j] - l);
            }
            suffq.push(vector<ll> {i, mn, curr - smx});
            last = i;
            smx = curr;
        }
    }
    ll currHealth = nums[k], lp = k, rp = k;
    while (1){
        if (lp==0 || rp==n-1){
            cout << "YES\n";
            return;
        }
        assert(currHealth >= 0);
        if (!prefq.empty() && currHealth + prefq.front()[1] >= 0){
            ll npos = prefq.front()[0], add = prefq.front()[2]; prefq.pop();
            currHealth += add;
            lp = npos;
        }
        else if (!suffq.empty() && currHealth + suffq.front()[1] >= 0){
            ll npos = suffq.front()[0], add = suffq.front()[2]; suffq.pop();
            currHealth+=add;
            rp = npos;
        }
        else{
            ll c1 = currHealth;
            for (int j = lp - 1; j >= 0; j--){
                c1 += nums[j];
                if (c1 < 0) break;
                if (j==0){
                    cout << "YES\n"; return;
                }
            }
            for (int j = rp + 1; j < n; j++){
                currHealth += nums[j];
                if (currHealth < 0) break;
                if (j==n-1){
                    cout << "YES\n"; return;
                }
            }
            cout << "NO\n";
            return;
        }
    }
}

int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}