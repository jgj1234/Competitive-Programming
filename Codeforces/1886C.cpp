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
    string s;
    cin>>s;
    ll pos;
    cin>>pos;
    vector<int> stk;
    int sz = s.size();
    set<int> removed;
    for (int i = 0; i < s.size(); i++){
        while (stk.size()>0 && s[i]<s[stk[stk.size()-1]]){
            if (pos-sz<=0){
                int ct = 0;
                for (int i = 0; i < s.size(); i++){
                    if (removed.find(i)!=removed.end()) continue;
                    ct++;
                    if (ct==pos){
                        cout<<s[i];
                        return;
                    }
                }
            }
            removed.insert(stk.back());
            stk.pop_back();
            pos-=sz; sz--;
        }
        stk.emplace_back(i);
    }
    while (stk.size()>0){
        if (pos-sz<=0){
                int ct = 0;
                for (int i = 0; i < s.size(); i++){
                    if (removed.find(i)!=removed.end()) continue;
                    ct++;
                    if (ct==pos){
                        cout<<s[i];
                        return;
                    }
                }
            }
            removed.insert(stk.back());stk.pop_back();
            pos-=sz; sz--;
    }
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