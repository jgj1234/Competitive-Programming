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
public:
    vector<int> nums;
    vector<pair<ll,pair<ll,ll>>> tree; //stores gcd, minimum,minimumCount
    SegmentTree(vector<int> arr){
        nums=arr;
        tree.resize(4*nums.size());
        build_tree(0,0,nums.size()-1);
    }
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    pair<int,pair<int,int>> combinePairs(pair<int,pair<int,int>> l,pair<int,pair<int,int>> r){
        int newGCD=gcd(l.first,r.first);
        int newMinimum=min(l.second.first,r.second.first);
        int newCount=0;
        if (l.second.first==newMinimum){
            newCount+=l.second.second;
        }
        if (r.second.first==newMinimum){
            newCount+=r.second.second;
        }
        return {newGCD,{newMinimum,newCount}};
    }
    pair<int,pair<int,int>> build_tree(int node, int left, int right){
        if (left==right){
            return tree[node]={nums[left],{nums[left],1}};
        }
        int mid = (left+right)/2;
        pair<int,pair<int,int>> l= build_tree(2*node+1,left,mid);
        pair<int,pair<int,int>> r= build_tree(2*node+2,mid+1,right);
        return tree[node]=combinePairs(l,r);
    }
    pair<int,pair<int,int>> query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight<left){
            return {-1,{-1,-1}};
        }
        if (arrLeft>=left && arrRight<=right){
            return tree[node];
        }
        int mid = (arrLeft+arrRight)/2;
        pair<int,pair<int,int>> l = query(2*node+1,left,right,arrLeft,mid);
        pair<int,pair<int,int>> r = query(2*node+2,left,right,mid+1,arrRight);
        if (l.first!=-1 && r.first!=-1){
            return combinePairs(l,r);
        }
        else if(l.first!=-1){
            return l;
        }
        return r;
    }
};
int main(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++){
        cin>>nums[i];
    }
    SegmentTree segTree(nums);
    int t;
    cin>>t;
    while(t--){
        int l,r;
        cin>>l>>r;
        pair<int,pair<int,int>> q=segTree.query(0,l-1,r-1,0,n-1);
        if (q.first>=q.second.first){
            cout<<(r-l+1)-q.second.second<<endl;
        }
        else{
            cout<<r-l+1<<endl;
        }
    }
}