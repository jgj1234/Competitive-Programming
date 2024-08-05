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
    vector<int> nums;
    vector<ll> tree;
    vector<ll> lazy;
    SegmentTree(vector<int> arr){
        nums=arr;
        lazy.resize(4*arr.size());
        tree.resize(4*arr.size());
        build_tree(0,0,arr.size()-1);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node]=(ll)nums[left];
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
    }
    void update(int node, int left, int right, int arrLeft, int arrRight, ll x){
        if (lazy[node]!=0){
            if(arrLeft!=arrRight){
                lazy[2*node+1]+=lazy[node];
                lazy[2*node+2]+=lazy[node];
            }
            else{
                tree[node]+=lazy[node];
            }
            lazy[node]=0;
        }
        if (arrRight<left || arrLeft>right){
            return;
        }
        if (arrLeft>=left && arrRight<=right){
            if(arrLeft!=arrRight){
                lazy[2*node+1]+=x;
                lazy[2*node+2]+=x;
            }
            else{
                tree[node]+=x;
            }
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        update(2*node+1,left,right,arrLeft,mid,x);
        update(2*node+2,left,right,mid+1,arrRight,x);
    }
    ll query(int node, int left, int right, int index){
        if (lazy[node]!=0){
            if(left!=right){
                lazy[2*node+1]+=lazy[node];
                lazy[2*node+2]+=lazy[node];
            }
            else{
                tree[node]+=lazy[node];
            }
            lazy[node]=0;
        }
        if (left==right && left==index){
            return tree[node];
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            return query(2*node+1,left,mid,index);
        }
        return query(2*node+2,mid+1,right,index);
    }
};
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    SegmentTree segTree(nums);
    for (int i = 0; i < q; i++){
        int t;
        cin>>t;
        if (t==1){
            ll a,b,u;
            cin>>a>>b>>u;
            segTree.update(0,a-1,b-1,0,n-1,u);
        }
        else{
            int x;
            cin>>x;
            cout<<segTree.query(0,0,n-1,x-1)<<endl;
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