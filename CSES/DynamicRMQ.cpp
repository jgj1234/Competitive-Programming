#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <unordered_map>
#include <cmath>
#define pii pair<int,int>
#define ll long long
#define MOD 1000000007
using namespace std;
class SegmentTree{
public:
    vector<int> nums;
    vector<int> tree;
    SegmentTree(vector<int> arr){
        nums=arr;
        tree.resize(4*arr.size());
        build_tree(0,0,nums.size()-1);
    }
    int build_tree(int node, int left, int right){
        if (left==right){
            return tree[node]=nums[left];
        }
        int mid = (left+right)/2;
        return tree[node]=min(build_tree(2*node+1,left,mid),build_tree(2*node+2,mid+1,right));
    }
    int update(int node, int pos, int value, int arrLeft, int arrRight){
        if (arrLeft==arrRight){
            nums[pos]=value;
            return tree[node]=value;
        }
        int mid = (arrLeft+arrRight)/2;
        int left = pos<=mid? update(2*node+1,pos,value,arrLeft,mid): tree[2*node+1];
        int right = pos>mid? update(2*node+2,pos,value,mid+1,arrRight):tree[2*node+2];
        return tree[node]=min(left,right);
    }
    int query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight < left){
            return INT_MAX-1;
        }
        if (arrLeft>=left && arrRight<=right){
            return tree[node];
        }
        int mid = (arrLeft+arrRight)/2;
        int l = query(2*node+1,left,right,arrLeft,mid);
        int r = query(2*node+2,left,right,mid+1,arrRight);
        return min(l,r);
    }
};
int main(){
    int n,q;
    cin>>n>>q;
    vector<int> nums (n);
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
            segTree.update(0,k-1,u,0,n-1);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<segTree.query(0,l-1,r-1,0,n-1)<<endl;
        }
    }
 
}