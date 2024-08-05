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
    int n;
    cin>>n;
    vector<ll> a(n),b(n);
    for (int i = 0; i < n; i++) cin>>a[i];
    for (int i = 0; i < n; i++) cin>>b[i];
    vector<pair<vector<ll>,vector<ll>>> groups = {pair<vector<ll>,vector<ll>> (a,b)};
    ll res = 0;
    for (int bit = 30; bit >= 0; bit--){
        bool bad = false;
        vector<pair<vector<ll>,vector<ll>>> nxt;
        for (auto& group: groups){
            auto& ag = group.first, bg = group.second;
            int azc = 0, aoc = 0, bzc = 0, boc = 0;
            int sz = ag.size();
            pair<vector<ll>,vector<ll>> ao, az;
            for (int i = 0; i < sz; i++){
                ll abit = ag[i]&(1<<bit);
                ll bbit = bg[i]&(1<<bit);
                if (abit){
                    ao.first.emplace_back(ag[i]);
                    aoc++;
                }
                else{
                    az.first.emplace_back(ag[i]);
                    azc++;
                }
                if (bbit){
                    az.second.emplace_back(bg[i]);
                    boc++;
                }
                else{
                    ao.second.emplace_back(bg[i]);
                    bzc++;
                }
            }
            if (azc!=boc){
                bad = true;
                break;
            }
            if (aoc){
                nxt.emplace_back(ao);
            }
            if (azc){
                nxt.emplace_back(az);
            }
        }
        if (!bad){
            res+=(1<<bit);
            groups = nxt;
        }
    }
    cout<<res<<endl;
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