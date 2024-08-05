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
struct SegmentTree{
    vector<ll> tree;
    SegmentTree(){}
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void update(int node, int left, int right, int index, ll value){
        if (left==right){
            tree[node]=value;
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            update(2*node+1,left,mid,index,value);
        }
        else{
            update(2*node+2,mid+1,right,index,value);
        }
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    ll query(int node, int left, int right, int index){
        if (left>index) return 0;
        if (right<=index) return tree[node];
        int mid = (left+right)>>1;
        return query(2*node+1,left,mid,index)+query(2*node+2,mid+1,right,index);
    }
    
};
void solve(){
    int n,k;
    cin>>n>>k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<SegmentTree> segTrees(k+1);
    for (int i = 0; i < k +1; i++) segTrees[i]=SegmentTree(n+1);
    for (int i = 0; i < n; i++){
        for (int x = k; x >= 1; x--){
            segTrees[x].update(0,0,n,nums[i],segTrees[x-1].query(0,0,n,nums[i]));
        }
        segTrees[0].update(0,0,n,nums[i],1);
    }
    cout<<segTrees[k].tree[0]<<endl;
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