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
    vector<int> tree;
    SegmentTree(int n){
        tree.resize(4*n);
        build_tree(0,0,n-1);
    }
    int build_tree(int node, int left, int right){
        if (left==right){
            return tree[node]=1;
        }
        int mid = (left+right)>>1;
        return tree[node]=build_tree(2*node+1,left,mid)+build_tree(2*node+2,mid+1,right);
    }
    int query(int node, int left, int right, int k){
        if (left==right){
            tree[node]--;
            return left;
        }
        int mid = (left+right)>>1;
        tree[node]--;
        if (k>tree[2*node+1]){
            return query(2*node+2,mid+1,right,k-tree[2*node+1]);
        }
        return query(2*node+1,left,mid,k);
    }
};
void solve(){
    int n;
    cin>>n;
    vector<int> nums(n);
    SegmentTree segTree (n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<int> order(n);
    for (int i = 0; i < n; i++) cin>>order[i];
    for (int i = 0; i < n; i++){
        cout<<nums[segTree.query(0,0,n-1,order[i])]<<" ";
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