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
    ll n,m; cin>>n>>m;
    vector<ll> a(n);
    for (auto& x: a) cin>>x;
    for (int i = 1; i < n; i++){
        if (a[i] > a[i-1] || a[i-1]%a[i]!=0){
            cout << 0 << '\n';
            return;
        }
    }
    vector<ll> ways(n); ways[0] = 1;
    vector<ll> facts;
    ll d = 2;
    ll curr = a[0];
    while (d*d <= a[0] && curr > 1){
        while (curr%d==0){
            curr/=d;
            facts.emplace_back(d);
        }
        d++;
    }
    if (curr!=1){
        facts.emplace_back(curr);
    }
    for (int i = 1; i < n; i++){
        vector<ll> missing;
        ll curr = a[i];
        for (int fact: facts){
            if (curr%fact!=0 && (missing.size()==0 || fact!=missing.back())){
                missing.emplace_back(fact);
            }
            else if (curr%fact==0){
                curr/=fact;
            }
        }
        ll sz = missing.size();
        ll currWays = (m/a[i])%MOD2;
        for (int mask = 1; mask < (1<<sz); mask++){
            int x = __builtin_popcount(mask);
            ll l = a[i];
            for (int j = 0; j < sz; j++){
                if ((mask>>j)&1){
                    l*=missing[j];
                }
            }
            if (x&1){
                currWays = ((currWays - m/l)+MOD2)%MOD2;
            }
            else{
                currWays = (currWays+m/l)%MOD2;
            }
        }
        ways[i] = currWays;
        vector<ll> nfacts;
        for (int fact: facts){
            if (a[i]%fact==0){
                a[i]/=fact;
                nfacts.emplace_back(fact);
            }
        }
        swap(facts, nfacts);
    }
    ll res = 1;
    for (int i = 1; i < n; i++){
        res = (res*ways[i])%MOD2;
    }
    cout << res << '\n';
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