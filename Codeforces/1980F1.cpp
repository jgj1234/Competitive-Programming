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
    ll n,m,k;
    cin>>n>>m>>k;
    vector<pii> fountains(k);
    for (int i = 0; i < k; i++){
        int x,y;
        cin>>x>>y;
        fountains[i]=pii(x-1,y-1);
    }
    vector<pii> stk;
    vector<pii> copy (fountains.begin(),fountains.end());
    sort(copy.begin(),copy.end());
    for (int i = 0; i < k; i++){
        if (stk.size()>0 && copy[i].first==stk[stk.size()-1].first) continue;
        while (stk.size()>0 && copy[i].second<=stk[stk.size()-1].second) stk.pop_back();
        stk.emplace_back(copy[i]);
    }
    int lastRow = -1;
    set<pii> r;
    ll mx = 0;
    for (int i = 0; i < stk.size(); i++){
        mx+=(ll)(stk[i].first-lastRow)*(stk[i].second);
        lastRow = stk[i].first;
        r.insert(stk[i]);
    }
    mx+=(n-1-stk[stk.size()-1].first)*(m);
    cout<<mx<<endl;
    vector<int> res(k);
    for (int i = 0; i < k; i++){
        if (r.find(fountains[i])!=r.end()){
            res[i]=1;
        }
    }
    for (int i = 0; i < k; i++){
        cout<<res[i]<<" ";
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