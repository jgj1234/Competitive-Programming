#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pli pair<long long,int>
#define pibb pair<int,<bool,bool>>
#define ll long long
#define MOD 1000000007
using namespace std;
class SegmentTree{
public:
    vector<int> nums;
    vector<ll> tree;
    SegmentTree(vector<int> arr){
        nums=arr;
        tree.resize(4*arr.size());
        build_tree(0,0,arr.size()-1);
    }
    ll build_tree(int node, int left, int right){
        if (left==right){
            return tree[node]=nums[left];
        }
        int mid = (left+right)/2;
        return tree[node]=build_tree(2*node+1,left,mid)+build_tree(2*node+2,mid+1,right);
    }
    ll update(int node, int left, int right, int pos, int val){
        if (left==right){
            return tree[node]=val;
        }
        int mid = (left+right)/2;
        ll l = pos<=mid?update(2*node+1,left,mid,pos,val):tree[2*node+1];
        ll r = pos>mid?update(2*node+2,mid+1,right,pos,val):tree[2*node+2];
        return tree[node]=l+r;
    }
    ll query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight < left){
            return 0;
        }
        if (arrLeft>=left && arrRight<=right){
            return tree[node];
        }
        int mid = (arrLeft+arrRight)/2;
        return query(2*node+1,left,right,arrLeft,mid) + query(2*node+2,left,right,mid+1,arrRight);
    }
};
int main(){
    int n,q;
    cin>>n>>q;
    vector<int> nums(n);
    for (int i = 0; i < n; i++){
        cin>>nums[i];
    }
    SegmentTree segTree(nums);
    for (int i = 0; i < q; i++){
        int t;
        cin>>t;
        if (t==1){
            int k,u;
            cin>>k>>u;
            segTree.update(0,0,n-1,k-1,u);
        }
        else{
            int l,r;
            cin>>l>>r;
            ll res = segTree.query(0,l-1,r-1,0,n-1);
            cout<<res<<endl;
        }
    }
}