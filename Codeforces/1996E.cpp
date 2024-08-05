#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
#include <cmath>
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
    string s;
    cin>>s;
    vector<ll> dp(s.size());
    vector<ll> pref(s.size());
    map<ll,ll> ct;
    
    for (int i = 0; i < s.size(); i++){
        if (i>0){
            dp[i]+=dp[i-1];
            pref[i]+=pref[i-1];
        }
        if (s[i]=='0'){
            pref[i]--;
        }
        else{
            pref[i]++;
        }
        if (pref[i]==0){
            dp[i]+=(s.size()-i);
            dp[i]%=MOD;
        }
        dp[i]+=(ct[pref[i]])*(s.size()-i);
        ct[pref[i]]+=(i+2);
        dp[i]%=MOD;
    }
    cout<<dp[s.size()-1]<<endl;
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
}