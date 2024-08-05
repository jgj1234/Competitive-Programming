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
    int minLeft = 0;
    int minRight = 0;
    int left = 0;
    int right = 0;
    bool isNull = false;
    Node(){}
};
struct SegmentTree{
    vector<Node> tree;
    SegmentTree(vector<int>& arr){
        tree.resize(4*arr.size());
        build_tree(0,0,arr.size()-1,arr);
    }
    void merge(Node& leftNode, Node& rightNode, Node& main){
        main.minLeft = min(leftNode.minLeft,rightNode.minLeft+(rightNode.left-leftNode.left));
        main.minRight = min(rightNode.minRight, leftNode.minRight+(rightNode.right-leftNode.right));
    }
    void build_tree(int node, int left, int right,vector<int>& nums){
        tree[node].left=left;
        tree[node].right=right;
        if (left==right){
            tree[node].minLeft = nums[left];
            tree[node].minRight = nums[left];
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid,nums);
        build_tree(2*node+2,mid+1,right,nums);
        merge(tree[2*node+1],tree[2*node+2],tree[node]);
    }
    void update(int node, int left, int right, int index, int price){
        if (left==right){
            tree[node].minLeft=price;
            tree[node].minRight=price;
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            update(2*node+1,left,mid,index,price);
        }
        else{
            update(2*node+2,mid+1,right,index,price);
        }
        merge(tree[2*node+1],tree[2*node+2],tree[node]);
        
    }
    Node query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight<left){
            Node a = Node();
            a.isNull = true;
            return a;
        }
        if (arrLeft>=left && arrRight<=right) return tree[node];
        int mid = (arrLeft+arrRight)>>1;
        Node l = query(2*node+1,left,right,arrLeft,mid);
        Node r = query(2*node+2,left,right,mid+1,arrRight);
        if (l.isNull) return r;
        if (r.isNull) return l;
        Node m = Node();
        merge(l,r,m);
        m.left = l.left;
        m.right = r.right;
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
            int k,x;
            cin>>k>>x;
            segTree.update(0,0,n-1,k-1,x);
        }
        else{
            int k;
            cin>>k;
            Node prefix = segTree.query(0,0,k-1,0,n-1);
            Node suffix = segTree.query(0,k-1,n-1,0,n-1);
            cout<<min(prefix.minRight,suffix.minLeft)<<endl;
        }
    }
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