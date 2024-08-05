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
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<int> prefixXOR(n);
    int xr = 0;
    map<int,vector<int>> mp;
    for (int i = 0; i < n; i++){
        xr^=nums[i];
        prefixXOR[i]=xr;
        mp[xr].emplace_back(i);
    }
    while (q--){
        int l,r;
        cin>>l>>r;
        --l;--r;
        int sub = prefixXOR[r];
        if (l!=0) sub^=prefixXOR[l-1];
        if (!sub){
            cout<<"YES"<<endl;
            continue;
        }
        int bef = (l==0?0:prefixXOR[l-1]);
        int t1 = sub^bef;
        if (mp.find(t1)==mp.end()){
            cout<<"NO"<<endl;
            continue;
        }
        int lp = 0; 
        int rp = mp[t1].size() - 1;
        while (lp<=rp){
            int mid = (lp+rp)>>1;
            if (mp[t1][mid]<l){
                lp=mid+1;
            }
            else{
                rp=mid-1;
            }
        }
        if (mp[t1][lp]>=r||mp[t1][lp]<l){
            cout<<"NO"<<endl;
            continue;
        }
        int pos1 = mp[t1][lp];
        int t2 = prefixXOR[mp[t1][lp]]^sub;
        if (mp.find(t2)==mp.end()){
            cout<<"NO"<<endl;
            continue;
        }
        lp = 0; rp = mp[t2].size()-1;
        while (lp<=rp){
            int mid = (lp+rp)>>1;
            if (mp[t2][mid]>r){
                rp=mid-1;
            }
            else{
                lp=mid+1;
            }
        }
        if (rp<0 || mp[t2][rp]<=pos1||mp[t2][rp]>r){
            cout<<"NO"<<endl;
        }
        else{
            //cout<<pos1<<" "<<mp[t2][rp]<<" "<<l<<" "<<r<<endl;
            cout<<"YES"<<endl;
        }
    }
    cout<<endl;
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