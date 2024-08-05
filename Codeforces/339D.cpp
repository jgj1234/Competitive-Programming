#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <cmath>
#define pii pair<int,int>
#define ll long long
using namespace std;
class SegmentTree{
    vector<int> nums;
    vector<int> tree;
    bool isOdd;
    ll build_tree(int node,int left, int right, bool isOdd){
        if (left==right){
            return tree[node]=nums[left];
        }
        int mid =(left+right)/2;
        ll l=build_tree(2*node+1,left,mid,!isOdd);
        ll r=build_tree(2*node+2,mid+1,right,!isOdd);
        if (isOdd){
            tree[node]=l|r;
        }
        else{
            tree[node]=l^r;
        }
        return tree[node];
    }
    int update(int node, int index, int value, int arrLeft, int arrRight, bool isOdd){
        if (index < arrLeft || index > arrRight){
            return tree[node];
        }
        if (arrLeft == arrRight){
            return tree[node] = value;
        }
        int mid = (arrLeft + arrRight)/2;
        int left = index<=mid ? update(2*node+1,index,value,arrLeft,mid,!isOdd):tree[2*node+1];
        int right = index > mid ? update(2*node+2,index,value,mid+1,arrRight, !isOdd):tree[2*node+2];
        if (isOdd){
            tree[node]=left|right;
        }
        else{
            tree[node]=left^right;
        }
        return tree[node];
    }
public:
    SegmentTree(const vector<int> arr, bool odd){
        nums=arr;
        isOdd=odd;
        tree.resize(4*nums.size());
        build_tree(0,0,nums.size()-1,odd);
    }
    void updateHelper(int index, int val){
        cout<<update(0,index-1,val,0,nums.size()-1,isOdd)<<endl;
    }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<int> nums (1<<n);
    for (int i = 0;i<(1<<n);i++){
        cin>>nums[i];
    }
    bool isOdd=n%2==1;
    SegmentTree segTree(nums,isOdd);
    for (int i = 0; i < m; i++){
        int p,b;
        cin>>p>>b;
        segTree.updateHelper(p,b);
    }
}