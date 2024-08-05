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
 

struct Node{
    ll maxSuffix = 0;
    ll maxPrefix = 0;
    ll maxSum = 0;
    ll sum = 0;
};
struct SegmentTree{
    vector<int> nums;
    vector<Node> tree;
    SegmentTree(vector<int> arr){
        nums = arr;
        tree.resize(4*arr.size());
        build_tree(0,0,arr.size()-1);
    }
    void merge(Node& left, Node& right, Node& main){
        main.maxSum=max(left.maxSum,right.maxSum);
        main.maxSum=max(main.maxSum,left.maxSuffix+right.maxPrefix);
        main.maxPrefix=max(left.maxPrefix,left.sum+right.maxPrefix);
        main.maxSuffix=max(right.maxSuffix,right.sum+left.maxSuffix);
        main.sum=right.sum+left.sum;
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node].maxSum=nums[left];
            tree[node].maxPrefix=nums[left];
            tree[node].maxSuffix=nums[left];
            tree[node].sum = nums[left];
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        merge(tree[2*node+1],tree[2*node+2],tree[node]);
    }
    void update(int node, int left, int right, int index, int x){
        if(left==right){
            tree[node].maxSum=x;
            tree[node].maxPrefix=x;
            tree[node].maxSuffix=x;
            tree[node].sum=x;
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            update(2*node+1,left,mid,index,x);
        }
        else{
            update(2*node+2,mid+1,right,index,x);
        }
        merge(tree[2*node+1],tree[2*node+2],tree[node]);
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> nums(n);
    for (int i  = 0; i < n; i++){
        cin>>nums[i];
    }
    SegmentTree segTree(nums);
    for (int q = 0; q < m; q++){
        int i,v;
        cin>>i>>v;
        segTree.update(0,0,n-1,i-1,v);
        cout<<max(segTree.tree[0].maxSum,(ll)0)<<endl;
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