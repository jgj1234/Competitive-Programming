#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pli pair<long long,int>
#define pibb pair<int,<bool,bool>>
#define ll long long
#define MOD 1000000007
using namespace std;
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> problems(n);
    for (int i = 0; i < n; i++) cin>>problems[i];
    vector<int> models(m);
    for (int i = 0; i < m; i++) cin>>models[i];
    vector<int> functions (k);
    for (int i = 0; i < k; i++) cin>>functions[i];
    sort(models.begin(),models.end());
    sort(functions.begin(),functions.end());
    int i1 = 0; int i2 = 1;
    for (int i = 2; i < n; i++){
        if (problems[i]-problems[i-1] > problems[i2]-problems[i1]){
            i1 = i-1;
            i2 = i;
        }
    }
    double target = ((double)problems[i2]+problems[i1])/2;
    ll closest = 0;
    for (int i = 0; i < m; i++){
        double needed = target - models[i];
        int lp = 0; int rp = k-1;
        int got = lp;
        while (lp<=rp){
            int mid = (lp+rp)>>1;
            if (abs(needed-functions[mid])<abs(needed-functions[got])){
                got = mid;
            }
            if (functions[mid]>needed){
                rp=mid-1;
            }
            else{
                lp=mid+1;
            }
        }
        if (abs(models[i]+functions[got]-target)<abs(closest-target)){
            closest = functions[got]+models[i];
        }
    }
    ll maxDiff = 0;
    for (int i = 1; i < n; i++){
        if (closest >= problems[i-1] && closest<=problems[i]){
            ll mx = max(closest-problems[i-1],problems[i]-closest);
            maxDiff = max(maxDiff,mx);
        }
        else{
            maxDiff = max(maxDiff,(ll)problems[i]-problems[i-1]);
        }
    }
    cout<<min(maxDiff,(ll)problems[i2]-problems[i1])<<endl;
}
int main(){
   int t;
   cin>>t;
   while (t--){
        solve();
   }
}