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
    int n; cin>>n;
    vector<ll> a(n), d(n);
    for (auto& x: a) cin>>x;
    for (auto& x: d) cin>>x;
    set<ll> alive;
    for (int i = 0; i < n; i++) alive.insert(i);
    vector<ll> res(n);
    set<ll> last;
    for (int i = 0; i < n; i++){
        ll curr = 0;
        if (i + 1 < n){
            curr += a[i+1];
        }
        if (i) curr += a[i-1];
        if (curr > d[i]){
            last.insert(i);
            alive.erase(i);
        }
    }
    res[0] = last.size();
    for (int i = 1; i < n; i++){
        set<ll> nlast;
        for (int x: last){
            if (alive.size()==0 || x > *alive.rbegin() || x < *alive.begin()) continue;
            auto greater = alive.lower_bound(x);
            if (greater==alive.begin()) continue;
            auto lower = prev(greater);
            ll left = a[*greater], right = a[*lower];
            if (*lower != *alive.begin()){
                left += a[*(prev(lower))];
            }
            if (*greater  != *alive.rbegin()){
                right += a[*(next(greater))];
            }
            if (left > d[*lower]){
                nlast.insert(*lower);
            }
            if (right > d[*greater]){
                nlast.insert(*greater);
            }
        }
        for (int x: nlast){
            alive.erase(x);
        }
        res[i] = nlast.size();
        last = nlast;
    }
    for (int i = 0; i < n; i++) cout << res[i] << " \n"[i==n-1];
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