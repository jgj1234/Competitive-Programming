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
        return tree[node]=build_tree(2*node+1,left,mid)&build_tree(2*node+2,mid+1,right);
    }
    int query(int node, int left, int right, int arrLeft, int arrRight){
        if (left > arrRight || right < arrLeft){
            return -1;
        }
        if (arrLeft>=left && arrRight<=right){
            return tree[node];
        }
        int mid = (arrLeft + arrRight)/2;
        int l = query(2*node+1, left,right,arrLeft,mid);
        int r = query(2*node+2,left,right,mid+1,arrRight);
        if (l!=-1 && r!=-1){
            return l&r;
        }
        else if (l!=-1){
            return l;
        }
        return r;
    }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> bitMap(32,vector<int>(n,0));
    vector<vector<int>> queries;
    for (int i = 0; i < m; i++){
        int l,r,q;
        cin>>l>>r>>q;
        for (int j = 0; j < 31; j++){
            if ((q&(1<<j))!=0){
                bitMap[j][l-1]++;
                if (r < n){
                    bitMap[j][r]--;
                }
            }
        }
        queries.push_back({l,r,q});
    }
    vector<int> nums(n);
    for (int bit = 0; bit < 32; bit++){
        for (int i = 0; i < n; i++){
            if (i > 0) bitMap[bit][i]+=bitMap[bit][i-1];
            if (bitMap[bit][i]>0){
                nums[i]|=(1<<bit);
            }
        }
    }
    SegmentTree segTree(nums);
    bool ans = false;
    for (const auto& query: queries){
        if (segTree.query(0,query[0]-1,query[1]-1,0,n-1)!=query[2]){
            ans = true;
            cout<<"NO"<<endl;
            break;
        }
    }
    if (!ans){
        cout<<"YES"<<endl;
        for (int i = 0; i < nums.size(); i++){
            cout<<nums[i]<<" ";
        }
    }
}