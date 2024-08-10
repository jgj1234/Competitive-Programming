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
const ll MAX_N = 300006, MAX_LG = 19;
ll jump[MAX_N][MAX_LG], tons[MAX_N], price[MAX_N];
vector<vector<int>> nodeMap(MAX_N);
int kth(int node, int k){
    for (int i = 0; i < MAX_LG; i++){
        if (k&(1<<i)){
            node = jump[node][i];
        }
    }
    return node;
}
void solve(){
    ll q,a,c;
    cin>>q>>a>>c;
    tons[0] = a; price[0] = c;
    int ind = 0;
    while (q--){
        int t; cin>>t;
        ind++;
        if (t==1){
            ll p, ai, ci;
            cin>>p>>ai>>ci;
            tons[ind]=ai;price[ind]=ci; jump[ind][0]=p;
            for (int j = 1; j < MAX_LG;j++){
                jump[ind][j]=jump[jump[ind][j-1]][j-1];
            }
        }
        else{
            int v,w;
            cin>>v>>w;
            if (tons[v]==0){
                cout<<0<<" "<<0<<endl;
                continue;
            }
            int rp = v;
            for (int i = MAX_LG-1;i>=0;i--){
                if (tons[jump[rp][i]]!=0){
                    //cout<<tons[jump[rp][i]]<<endl;
                    rp=jump[rp][i];
                }
            }
            ll spent = 0;
            ll gold = 0;
            while (tons[rp] && gold<w){
                ll lft = w-gold;
                ll x = min(lft,tons[rp]);
                spent+=price[rp]*x;
                tons[rp]-=x;
                gold+=x;
                rp=v;
                for (int x = MAX_LG - 1; x>=0 ; x--){
                    if (tons[jump[rp][x]]>0) rp = jump[rp][x];
                }
            }
            cout<<gold<<" "<<spent<<endl;
        }
        fflush(stdout);
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