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
    int lp = 2, rp = 999;
    while (lp<rp){
        ll diff = (rp-lp)/3;
        ll mid1 = lp+diff, mid2 = lp+2*diff;
        cout<<"? "<<mid1<<" "<<mid2<<endl;
        fflush(stdout);
        ll x; cin>>x;
        if (x==mid1*mid2){
            lp = mid2 + 1;
        }
        else if (x==mid1*(mid2+1)){
            lp = mid1 + 1;
            rp = mid2;
        }
        else{
            rp = mid1;
        }
        //cout<<lp<<" "<<rp<<endl;
    }
    cout<<"! "<<lp<<endl;
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