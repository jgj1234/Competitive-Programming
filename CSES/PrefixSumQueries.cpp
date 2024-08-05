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
struct Node{
    ll maxPrefix = 0;
    ll maxSuffix = 0;
    bool isNull = false;
    ll sum = 0;
    Node(){}
};
struct SegmentTree{
    vector<Node> tree;
    vector<int> nums;
    SegmentTree(vector<int> arr){
        nums = arr;
        tree.resize(4*nums.size());
        build_tree(0,0,nums.size()-1);
    }
    void mergeNodes(Node& left, Node& right, Node& main){
        main.sum = left.sum+right.sum;
        main.maxPrefix = max(left.maxPrefix, left.sum+right.maxPrefix);
        //main.maxPrefix = max(0LL,main.maxPrefix);
        main.maxSuffix = max(right.maxSuffix,right.sum+left.maxSuffix);
        //main.maxSuffix = max(0LL,main.maxSuffix);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node].maxPrefix = nums[left];
            tree[node].maxSuffix = nums[left];
            tree[node].sum = nums[left];         
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        mergeNodes(tree[2*node+1],tree[2*node+2],tree[node]);
    }
    void update(int node, int left, int right, int index, int val){
        if (left==right){
            tree[node].maxPrefix = val;
            tree[node].maxSuffix =val;
            tree[node].sum = val;
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            update(2*node+1,left,mid,index,val);
        }
        else{
            update(2*node+2,mid+1,right,index,val);
        }
        mergeNodes(tree[2*node+1],tree[2*node+2],tree[node]);
    }
    Node query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight<left){
            Node n; n.isNull = true;
            return n;
        }
        if (arrLeft>=left&&arrRight<=right) return tree[node];
        int mid = (arrLeft+arrRight)>>1;
        Node l = query(2*node+1,left,right,arrLeft,mid);
        Node r = query(2*node+2,left,right,mid+1,arrRight);
        if (l.isNull) return r;
        if (r.isNull) return l;
        Node m;
        mergeNodes(l,r,m);
        return m;
    }
};
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    SegmentTree segTree(nums);
    while (q--){
        int t;
        cin>>t;
        if (t==1){
            int k,u;
            cin>>k>>u;
            segTree.update(0,0,n-1,k-1,u);
        }
        else{
            int a,b;
            cin>>a>>b;
            ll mp = segTree.query(0,a-1,b-1,0,n-1).maxPrefix;
            cout<<max(mp,0LL)<<endl;
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