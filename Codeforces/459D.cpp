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
#pragma GCC optimize("O3")
struct SegmentTree{
    vector<int> tree;
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void update(int node, int left, int right, int index, int val){
        if (left==right){
            tree[node]+=val;
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            update(2*node+1,left,mid,index,val);
        }
        else{
            update(2*node+2,mid+1,right,index,val);
        }
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    ll query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight<left) return 0;
        if (arrLeft>=left && arrRight<=right) return tree[node];
        int mid = (arrLeft+arrRight)>>1;
        return query(2*node+1,left,right,arrLeft,mid)+query(2*node+2,left,right,mid+1,arrRight);
    }
};
void solve(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    SegmentTree segTree(n+1);
    unordered_map<int,int> pref, sfx;
    for (int i = n - 1; i>=0; i--){
        sfx[nums[i]]++;
        segTree.update(0,0,n-1,sfx[nums[i]],1);
    }
    ll res = 0;
    for (int i = 0; i < n; i++){
        pref[nums[i]]++;
        segTree.update(0,0,n-1,sfx[nums[i]],-1);
        sfx[nums[i]]--;
        res+=segTree.query(0,0,pref[nums[i]]-1,0,n-1);
    }
    cout<<res<<endl;
    
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   // cin>>t;
   while (t--){
      solve();
   }
}