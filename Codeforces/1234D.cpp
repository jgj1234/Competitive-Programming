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
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
using namespace std;
struct SegmentTree{
   string nums;
   vector<int> tree;
   SegmentTree(string arr){
      nums = arr;
      tree.resize(4*arr.size());
      build_tree(0,0,nums.size()-1);
   }
   int build_tree(int node, int left, int right){
      if(left==right){
         return tree[node]=(1<<(nums[left]-'a'));
      }
      int mid = (left+right)>>1;
      return tree[node]=build_tree(2*node+1,left,mid)|build_tree(2*node+2,mid+1,right);
   }
   int update(int node, int pos, char c, int left, int right){
      if(left>pos ||right<pos){
         return tree[node];
      }
      if (left==right){
         return tree[node]=(1<<(c-'a'));
      }
      int mid = (left+right)>>1;
      return tree[node]=update(2*node+1,pos,c,left,mid)|update(2*node+2,pos,c,mid+1,right);
   }
   int query(int node, int left, int right, int arrLeft, int arrRight){
      if (arrLeft>right || arrRight<left){
         return 0;
      }
      if (arrLeft>=left && arrRight<=right){
         return tree[node];
      }
      int mid = (arrLeft+arrRight)>>1;
      return query(2*node+1,left,right,arrLeft,mid)|query(2*node+2,left,right,mid+1,arrRight);
   }
};
void solve(){
   string s;
   cin>>s;
   SegmentTree segTree(s);
   int q;
   cin>>q;
   while (q--){
      int t;
      cin>>t;
      if (t==1){
         int pos; char c;
         cin>>pos>>c;
         segTree.update(0,pos-1,c,0,s.size()-1);
      }
      else{
         int l,r;
         cin>>l>>r;
         int res =segTree.query(0,l-1,r-1,0,s.size()-1);
         cout<<__builtin_popcount(res)<<endl;
      }
   }
}
int main(){
   int t=1;
   //cin>>t;
   while (t--){
      solve();
   }
}