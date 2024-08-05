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
struct SegmentTree{
    vector<int> tree;
    vector<int> lazy;
    SegmentTree(int n){
        tree.resize(4*n);
        lazy.resize(4*n);
    }
    void update(int node, int left, int right, int arrLeft, int arrRight, int val){
        //cout<<node<<" "<<left<<" "<<right<<" "<<arrLeft<<" "<<arrRight<<" "<<val<<endl;
        if (lazy[node]!=0){
            tree[node]=max(tree[node],lazy[node]);
            if (arrLeft!=arrRight){
                lazy[2*node+1]=max(lazy[2*node+1],lazy[node]);
                lazy[2*node+2]=max(lazy[2*node+2],lazy[node]);
            }
            lazy[node]=0;
        }
        if (arrLeft>right || arrRight<left) return;
        if (arrLeft>=left && arrRight<=right){
            tree[node]=max(tree[node],val);
            if (arrLeft!=arrRight){
                lazy[2*node+1]=max(lazy[2*node+1],val);
                lazy[2*node+2]=max(lazy[2*node+2],val);
            }
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        update(2*node+1,left,right,arrLeft,mid,val);
        update(2*node+2,left,right,mid+1,arrRight,val);
        tree[node]=max(tree[2*node+1],tree[2*node+2]);
    }
    int query(int node, int left, int right, int arrLeft, int arrRight){
        if (lazy[node]!=0){
            tree[node]=max(tree[node],lazy[node]);
            if (arrLeft!=arrRight){
                lazy[2*node+1]=max(lazy[2*node+1],lazy[node]);
                lazy[2*node+2]=max(lazy[2*node+2],lazy[node]);
            }
            lazy[node]=0;
        }
        if (arrLeft>right || arrRight<left) return 0;
        if (arrLeft>=left && arrRight<=right) return tree[node];
        int mid = (arrLeft+arrRight)>>1;
        int res = max(query(2*node+1,left,right,arrLeft,mid),query(2*node+2,left,right,mid+1,arrRight));
        tree[node]=max(tree[2*node+1],tree[2*node+2]);
        return res;
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<pii> cats (m);
    for (int i = 0; i < m; i++){
        cin>>cats[i].first>>cats[i].second;
    }
    sort(cats.begin(),cats.end());
    vector<int> pref (n+1);
    SegmentTree segTree(n);
    for (int i = 0; i < m; i++){
        pref[cats[i].first-1]+=1;
        pref[cats[i].second]-=1;
        segTree.update(0,cats[i].first-1,cats[i].second-1,0,n-1,cats[i].second);
    }
    for (int i = 1; i < pref.size(); i++){
        pref[i]+=pref[i-1];
    }
    vector<int> dp (n+1,-1);
    auto dfs = [&] (auto self, int i) ->int{
        if (i>=n) return 0;
        if (dp[i]!=-1) return dp[i];
        int nt = self(self,i+1);
        if (pref[i]==0){
            return dp[i]=nt;
        }
        int ub = segTree.query(0,i,i,0,n-1);
        return dp[i]=max(nt,pref[i]+self(self,ub));
    };
    cout<<dfs(dfs,0)<<endl;
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