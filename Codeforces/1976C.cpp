#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>

#include <cmath>
#define pii pair<int,int>
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
   int n,m;
    cin>>n>>m;
    vector<int> a(n+m+1);
    for (int i = 0; i < n+m+1;i++) cin>>a[i];
    vector<int> b(n+m+1);
    for (int i = 0; i < n+m+1; i++) cin>>b[i];
    int lastProgram = -1; int lastTest = -1;
    unordered_set<int> programmers;
    unordered_set<int> testers;
    ll sm = 0;
    for (int i = 0; i < n + m; i++){
        if (a[i]>b[i]){
            if (programmers.size()==n){
                testers.insert(i);
                if (lastProgram==-1) lastProgram=i;
                sm+=b[i];
            }
            else{
                programmers.insert(i);
                sm+=a[i];
            }
        }
        else{
            if (testers.size()==m){
                programmers.insert(i);
                if (lastTest==-1) lastTest=i;
                sm+=a[i];
            }
            else{
                testers.insert(i);
                sm+=b[i];
            }
        }
    }
    vector<ll> res(n+m+1);
    for (int i = 0; i < n + m; i++){
        ll temp = sm;
        if (programmers.find(i)!=programmers.end()){
            temp-=a[i];
            if (lastProgram!=-1){
                temp+=a[lastProgram]-b[lastProgram];
                temp+=b[n+m];
            }
            else{
                temp+=a[n+m];
            }
            res[i]=temp;
        }
        else{
            temp-=b[i];
            if (lastTest!=-1){
                temp+=b[lastTest]-a[lastTest];
                temp+=a[n+m];
            }
            else{
                temp+=b[n+m];
            }
            res[i]=temp;
        }
    }
    res[n+m]=sm;
    for (int i = 0; i < n+m+1; i++) cout<<res[i]<<" ";
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