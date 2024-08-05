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
        build_tree(0,0,arr.size()-1);
    }
    int build_tree(int node, int left, int right){
        if (left==right){
            return tree[node]=nums[left];
        }
        int mid = (left+right)/2;
        return tree[node]=max(build_tree(2*node+1,left,mid),build_tree(2*node+2,mid+1,right));
    }
    pii query(int node, int sz, int left, int right){
        if (left == right){
            tree[node]-=sz;
            return {tree[node],left};
        }
        int mid = (left+right)/2;
        if (tree[2*node+1]>=sz){
            pii l = query(2*node+1,sz,left,mid);
            tree[node]=max(tree[2*node+2],l.first);
            return {tree[node],l.second};
        }
        else{
            pii r = query(2*node+2,sz,mid+1,right);
            tree[node]=max(r.first,tree[2*node+1]);
            return {tree[node],r.second};
        }
    }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<int> arr (n);
    for (int i = 0; i < n; i++){
        cin>>arr[i];
    }
    SegmentTree segTree(arr);
    for (int i = 0; i < m; i++){
        int group;
        cin>>group;
        if (group > segTree.tree[0]){
            cout<<0<<" ";
        }
        else{
            pii res = segTree.query(0,group,0,n-1);
            cout<<res.second+1<<" ";
        }
    }
}