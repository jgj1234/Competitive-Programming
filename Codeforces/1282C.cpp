#include <bits/stdc++.h>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
void solve(){
    ll n,t,a,b;
    cin>>n>>t>>a>>b;
    vector<pair<ll,ll>> prob(n);
    for (int i = 0; i < n; i++) cin>>prob[i].second;
    for (int i = 0; i < n; i++) cin>>prob[i].first;
    sort(all(prob));
    vector<ll> ez(n), h(n);
    ll s = 0;
    for (int i = 0; i < n; i++){
        if (prob[i].second==0){
            s+=a;
        }
        else{
            s+=b;
        }
    }
    if (s<=t){
        cout<<n<<endl;
        return;
    }
    for (int i = n - 2; i>=0; i--){
        ez[i] = (prob[i+1].second==0)+ez[i+1];
        h[i] = (prob[i+1].second==1) + h[i+1];
    }
    ll currTime = 0;
    vector<ll> dp(n);
    for (int i = 0; i < n; i++){
        if (currTime>=t) break;
        if (currTime >= prob[i].first){
            if (prob[i].second==0){
                currTime+=a;
            }
            else{
                currTime+=b;
            }
            continue;
        }
        ll diff = prob[i].first - currTime - 1;
        ll currProbs = i;
        ll ezfit = diff/a;
        currProbs+=min(ezfit, ez[i]);
        diff-=min(ezfit,ez[i])*a;
        ll hardfit = diff/b;
        currProbs+=min(hardfit,h[i]);
        diff-=min(hardfit,h[i])*b;
        dp[i] = currProbs;
        if (prob[i].second==0){
            currTime+=a;
        }
        else{
            currTime+=b;
        }
    }
    cout<<*max_element(all(dp))<<endl;
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    while (t--){
        solve();
    }
    return 0;
}