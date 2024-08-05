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
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    vector<vector<int>> grid (n,vector<int> (m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin>>grid[i][j];
        }
    }
    vector<string> caps(n);
    for (int i = 0; i < n; i++) cin>>caps[i];
    ll diff = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (caps[i][j]=='1'){
                diff+=grid[i][j];
            }
            else{
                diff-=grid[i][j];
            }
        }
    }
    vector<vector<int>> prefixSums(n,vector<int> (m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (caps[i][j]=='1') prefixSums[i][j]++;
            if (i>0){
                prefixSums[i][j]+=prefixSums[i-1][j];
            }
            if (j>0){
                prefixSums[i][j]+=prefixSums[i][j-1];
            }
            if (i>0 && j>0){
                prefixSums[i][j]-=prefixSums[i-1][j-1];
            }
        }
    }
    int g  = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i-k+1>=0 && j-k+1>=0){
                int ct = prefixSums[i][j];
                if (i-k>=0){
                    ct-=prefixSums[i-k][j];
                }
                if (j-k>=0){
                    ct-=prefixSums[i][j-k];
                }
                if (i-k>=0 && j-k>=0){
                    ct+=prefixSums[i-k][j-k];
                }
                g = gcd(g,ct-(k*k-ct));
            }
        }
    }
    diff = -diff;
    cout<<(((g!=0 && diff%g==0) || (diff==0))?"YES":"NO")<<endl;
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