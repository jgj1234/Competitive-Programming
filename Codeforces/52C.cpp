#include <iostream>
#include <vector>
#include <sstream>
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
struct LazySegmentTree{
   vector<ll> tree;
   vector<ll> lazy;
   vector<int> nums;
   LazySegmentTree(vector<int> arr){
       nums=arr;
      tree.resize(4*nums.size());
      lazy.resize(4*nums.size());
      build_tree(0,0,nums.size()-1);
   }
   ll build_tree(int node, int left, int right){
      if(left==right){
         return tree[node]=nums[left];
      }
      int mid = (left+right)>>1;
      return tree[node]=min(build_tree(2*node+1,left,mid),build_tree(2*node+2,mid+1,right));
   }
   ll update(int node, int l, int r, int left, int right, ll v){
      if (lazy[node]!=0){
         tree[node]+=lazy[node];
         if (left!=right){
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node];
         }
         lazy[node]=0;
      }
      if (left > r || right < l){
         return tree[node];
      }
      if (left>=l && right<=r){
         tree[node]+=v;
         if (left!=right){
            lazy[2*node+1]+=v;
            lazy[2*node+2]+=v;
         }
         return tree[node];
      }
      int mid = (left+right)>>1;
      return tree[node]=min(update(2*node+1,l,r,left,mid,v),update(2*node+2,l,r,mid+1,right,v));
   }
   ll query(int node, int l, int r, int left, int right){
      if (lazy[node]!=0){
         tree[node]+=lazy[node];
         if (left!=right){
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node];
         }
         lazy[node]=0;
      }
      if (left > r || right < l){
         return LLONG_MAX;
      }
      if (left>=l && right<=r){
         return tree[node];
      }
      int mid = (left+right)>>1;
      return min(query(2*node+1,l,r,left,mid),query(2*node+2,l,r,mid+1,right));
   }
};
void solve(){
   int n,m;
   scanf("%d",&n);
   vector<int> nums(n);
   for (int i = 0; i < n; i++){
       scanf("%d",&nums[i]);
   }
   scanf("%d",&m);
   cin.ignore();
   LazySegmentTree segTree(nums);
   for (int i = 0; i < m; i++){
      string line;
      getline(cin,line);
      istringstream iss(line);
      vector<int> q;
      int num;
      while (iss>>num){
         q.emplace_back(num);
      }
      if (q.size()==2){
         int l = q[0];
         int r = q[1];
         if (l>r){
            ll m1 = segTree.query(0,l,nums.size()-1,0,nums.size()-1);
            ll m2 = segTree.query(0,0,r,0,nums.size()-1);
            cout<<min(m1,m2)<<endl;
         }
         else{
            ll res = segTree.query(0,l,r,0,nums.size()-1);
            cout<<res<<endl;
         }
      }
      else{
         int l = q[0]; int r = q[1]; int v = q[2];
         if (l > r){
            segTree.update(0,l,nums.size()-1,0,nums.size()-1,v);
            segTree.update(0,0,r,0,nums.size()-1,v);
         }
         else{
            segTree.update(0,l,r,0,nums.size()-1,v);
         }
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