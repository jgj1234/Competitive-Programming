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
    int n,d,h;
    cin>>n>>d>>h;
    if (h*2<d||h>d||(h==1 && d==1 && n!=2)){
        cout<<-1<<endl;
        return;
    }
    set<int> s;
    for (int i = 1; i < n; i++) s.insert(i);
    vector<vector<int>> nodeMap(n);
    int currNode = 0;
    int first = -1;
    for (int i = 0; i < h; i++){
        int nxt = *s.begin();
        nodeMap[currNode].emplace_back(nxt);
        currNode = nxt;
        if (first==-1) first = currNode;
        s.erase(nxt);
    }
    currNode = 0;
    for (int i = 0; i < d-h; i++){
        int nxt = *s.begin();
        nodeMap[currNode].emplace_back(nxt);
        currNode=nxt;
        s.erase(nxt);
    }
    if (h!=d) first = 0;
    for (int x: s){
        nodeMap[first].emplace_back(x);
    }
    for (int i = 0; i < n; i++){
        for (int j: nodeMap[i]){
            cout<<i+1<<" "<<j+1<<endl;
        }
    }
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