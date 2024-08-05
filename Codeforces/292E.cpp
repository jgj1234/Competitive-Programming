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
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
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
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
struct SegmentTree{
    vector<int> a;
    vector<int> b;
    vector<int> tree;
    SegmentTree(vector<int> nums1, vector<int> nums2){
        a=nums1; b=nums2;
        tree.resize(4*a.size());
        build_tree(0,0,a.size()-1);
    }
    void build_tree(int node, int left, int right){
        tree[node]=-1;
        if (left==right){
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
    }
    void update(int node, int a1, int a2, int b1, int b2, int arrLeft, int arrRight){
        if (arrLeft>b2 || arrRight<b1) return;
        int mid = (arrLeft+arrRight)>>1;
        if (tree[node]!=-1){
            if (arrLeft!=arrRight){
                tree[2*node+1]=tree[node];
                tree[2*node+2]=tree[node]+mid-arrLeft+1;
                tree[node]=-1;
            }
        }
        if (arrLeft>=b1 && arrRight<=b2){
            tree[node]=arrLeft-b1+a1;
            return;
        }
        update(2*node+1,a1,a2,b1,b2,arrLeft,mid);
        update(2*node+2,a1,a2,b1,b2,mid+1,arrRight);
    }
    int query(int node, int arrLeft, int arrRight, int index){
        if (arrLeft==arrRight){
            if (tree[node]==-1) return b[arrLeft];
            return a[tree[node]];
        }
        int mid = (arrLeft+arrRight)>>1;
        if (tree[node]!=-1){
            tree[2*node+1]=tree[node];
            tree[2*node+2]=tree[node]+mid-arrLeft+1;
            tree[node]=-1;
        }
        if (index<=mid){
            return query(2*node+1,arrLeft,mid,index);
        }
        else{
            return query(2*node+2,mid+1,arrRight,index);
        }
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin>>a[i];
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin>>b[i];
    SegmentTree segTree(a,b);
    while (m--){
        int t;
        cin>>t;
        if (t==1){
            int x,y,k;
            cin>>x>>y>>k;
            --x;--y;
            segTree.update(0,x,x+k-1,y,y+k-1,0,n-1);
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