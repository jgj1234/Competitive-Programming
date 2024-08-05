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
    vector<int> nums;
    vector<ll> tree;
    SegmentTree(vector<int>& arr){
        nums = arr;
        tree.resize(4*nums.size());
        build_tree(0,0,nums.size()-1);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node]=nums[left]; return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    void update(int node, int left, int right, int index, int val){
        if (left==right){
            tree[node]=val; return;
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
   int n,q;
    cin>>n>>q;
    vector<int> values(n);
    for (int i = 0; i < n; i++) cin>>values[i];
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<int> sz (n);
    vector<int> mp(n);
    vector<int> flat(n);
    int pos = 0;
    auto dfs = [&] (auto self, int node, int parent) -> int{
        flat[pos]=values[node];
        mp[node]=pos++;
        int res = 1;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                res+=self(self,neighbor,node);
            }
        }
        return sz[node]=res;
    };
    dfs(dfs,0,-1);
    SegmentTree segTree(flat);
    while (q--){
        int t;
        cin>>t;
        if (t==1){
            int s,x;
            cin>>s>>x;
            --s;
            segTree.update(0,0,n-1,mp[s],x);
        }
        else{
            int s;
            cin>>s;
            --s;
            cout<<segTree.query(0,mp[s],mp[s]+sz[s]-1,0,n-1)<<endl;
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