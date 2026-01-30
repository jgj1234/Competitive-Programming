#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 100005;
int nums[N], l[N], r[N], ee[N], jumps[N];
void solve(int cas){
    int n,m; cin>>n>>m;
    for (int i = 0; i < n; i++) cin>>nums[i];
    int sq = (int) sqrt(n) + 1;
    for (int i = 0; i < n; i += sq){
        int e = min(n - 1, i + sq - 1);
        for (int j = e; j >= i; j--){
            l[j] = i;
            r[j] = e;
            int nxt = j + nums[j];
            if (nxt > e){
                jumps[j] = 1;
                ee[j] = j;
            }
            else{
                jumps[j] = 1 + jumps[nxt];
                ee[j] = ee[nxt];
            }
        }
    }
    while (m--){
        int t; cin>>t;
        if (t == 0){
            int a,b; cin>>a>>b;
            --a;
            nums[a] = b;
            for (int j = a;; j--){
                int nxt = j + nums[j];
                if (nxt > r[j]){
                    jumps[j] = 1;
                    ee[j] = j;
                }
                else{
                    jumps[j] = 1 + jumps[nxt];
                    ee[j] = ee[nxt];
                }
                if (j == l[j]) break;
            }
        }
        else{
            int a; cin>>a;--a;
            int tot_jumps = 0, last = -1;
            while (1){
                tot_jumps += jumps[a];
                if (ee[a] + nums[ee[a]] >= n){
                    last = ee[a];
                    break;
                }
                else{
                    a = ee[a] + nums[ee[a]];
                }
            }
            cout << last + 1 << " " << tot_jumps << '\n';
        }
    }
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