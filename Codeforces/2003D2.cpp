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
ll get(ll l, ll r){
    return r*(r+1)/2 - l*(l-1)/2;
}
void solve(int cas){
    ll n,m; cin>>n>>m;
    vector<pair<ll,ll>> mx(n);
    ll high = 0;
    for (int i = 0; i < n; i++){
        int l; cin>>l;
        set<ll> f;
        for (int i = 0; i < l; i++){
            int x; cin>>x;
            f.insert(x);
        }
        ll curr = 0;
        while (f.count(curr)) curr++;
        mx[i].first = curr++;
        while (f.count(curr)) curr++;
        mx[i].second = curr;
        high = max(high, curr);
    }
    ll res = 0;
    if (high < m){
        res = get(high + 1, m);
    }
    sort(all(mx));
    //once at second stay at second
    vector<vector<ll>> mp (high + 1);
    vector<ll> ct(high + 1), nxt(high + 1, -1);
    for (int i = 0; i < n; i++){ 
        mp[mx[i].first].emplace_back(mx[i].second);
        ct[mx[i].first]++;
        if (i!=n-1){
            nxt[mx[i].first] = mx[i+1].first;
        }
    }
    vector<vector<ll>> dp1 (high + 1, vector<ll> (3,-1));
    auto dfs1 = [&] (auto&& self, int i, int state) -> ll{
        if (dp1[i][state]!=-1) return dp1[i][state];
        ll ans = i;
        if (state==1 && nxt[i]!=-1 && nxt[i]!=i) ans = self(self,nxt[i],1);
        if (ct[i] > 1  || state==0){
            for (int x: mp[i]) ans = max(ans, self(self, x, 0));
        }
        return dp1[i][state] = ans;
    };
    ll f = dfs1(dfs1, mx[0].first, 1);
    for (int i = 0; i <= min(high,m); i++){
        res+=max(f,dfs1(dfs1,i,0));
    }
    cout<<res<<'\n';
    
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