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
    }
    void update(int node, int left, int right, int index){
        if (left==right){
            tree[node]++;
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid) update(2*node+1,left,mid,index);
        else update(2*node+2,mid+1,right,index);
        tree[node]++;
    }
    int less(int node, int left, int right, int index){
        if (left>=index) return 0;
        if (right<index) return tree[node];
        int mid = (left+right)>>1;
        return less(2*node+1,left,mid,index)+less(2*node+2,mid+1,right,index);
    }
    int greater(int node, int left, int right, int index){
        if (right<=index) return 0;
        if (left>index) return tree[node];
        int mid = (left+right)>>1;
        return greater(2*node+1,left,mid,index)+greater(2*node+2,mid+1,right,index);
    }
};
void solve(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<int> sorted(nums.begin(),nums.end());
    sort(sorted.begin(),sorted.end());
    unordered_map<int,int> mp;
    for (int i = 0; i < n; i++) mp[sorted[i]]=i;
    vector<pair<ll,ll>> r (n);
    SegmentTree segTree(n);
    for (int i = 0; i < n; i++){
        r[i].first=segTree.greater(0,0,n-1,mp[nums[i]]);
        segTree.update(0,0,n-1,mp[nums[i]]);
    }
    for (int i = n - 1; i>=0; i--){
        r[i].second = segTree.less(0,0,n-1,mp[nums[i]])-mp[nums[i]];
        segTree.update(0,0,n-1,mp[nums[i]]);
    }
    ll res = 0;
    for (int i = 0; i < n; i++){
        res+=r[i].first*r[i].second;
    }
    cout<<res<<endl;
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