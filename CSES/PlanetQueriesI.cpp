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
struct jumpDAG{
    int table[200005][30];
    jumpDAG(vector<int>& dest){
        for (int i = 0; i < dest.size(); i++){
            table[i][0] = dest[i];
        }
        for (int j = 1; j < 30; j++){
            for (int i = 0; i < dest.size(); i++){
                table[i][j] = table[table[i][j-1]][j-1];
            }
        }
    }
    int query(int node, int k){
        for (int i = 29; i>=0; i--){
            if ((k&(1<<i))){
                node = table[node][i];
            }
        }
        return node;
    }
};
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> tp(n);
    for (int i = 0; i < n; i++){
        int x;
        cin>>x;
        tp[i] = x-1;
    }
    jumpDAG dg (tp);
    while (q--){
        int x,k;
        cin>>x>>k;--x;
        cout<<dg.query(x,k)+1<<endl;
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