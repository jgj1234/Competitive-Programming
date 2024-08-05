#include <iostream>
#include <vector>
#include <string>
#include <cstring>
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
    ll v;
    cin>>v;
    vector<int> dig(9);
    for (int i = 0; i < 9; i++) cin>>dig[i];
    int mn = 0;
    for (int i = 8; i > 0; i--){
        if (dig[i]<dig[mn]){
            mn = i;
        }
    }
    if (dig[mn]>v){
        cout<<-1<<endl;
        return;
    }
    string s (v/dig[mn],mn+1+'0');
    ll rem = v%dig[mn];
    for (int i = 8; i>=0; i--){
        dig[i]-=dig[mn];
    }
    int p = 0;
    for (int i = 8; i>mn;i--){
        int digit = i + 1;
        while (p<s.size() && rem-dig[i]>=0){
            s[p++]=digit+'0';
            rem-=dig[i];
        }
    }
    cout<<s<<endl;
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   //cin>>t;
   while (t--){
      solve();
   }
}