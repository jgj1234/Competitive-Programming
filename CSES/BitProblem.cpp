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
const int MAXN = 200005, MAX_BIT = 21;
ll nums[MAXN], sub[1<<MAX_BIT], super[1<<MAX_BIT];
void solve(int cas){  
    int n; cin>>n;
    for (int i = 0; i < n; i++) cin>>nums[i];
    memset(sub, 0, sizeof sub); memset(super, 0, sizeof super);
    for (int i = 0; i < n; i++){
        sub[nums[i]]++; super[nums[i]]++;
    }
    for (int i = 0; i < MAX_BIT; i++){
        for (int mask = 0; mask < (1<<MAX_BIT); mask++){
            if (mask&(1<<i)) sub[mask] += sub[mask^(1<<i)];
        }
    }
    for (int i = 0; i < MAX_BIT; i++){
        for (int mask = (1<<MAX_BIT)-1; mask > 0; mask--){
            if ((mask&(1<<i))==0) super[mask] += super[mask|(1<<i)];
        }
    }
    for (int i = 0; i < n; i++){
        cout << sub[nums[i]] << " " << super[nums[i]] << " " << n - sub[((1<<MAX_BIT)-1)^nums[i]] << '\n';
    }
}

int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}