//Problem Link: https://codeforces.com/contest/2001/problem/D
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
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
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
struct segmin{
    vector<int> nums;
    vector<pii> tree;
    segmin(vector<int>& arr){
        tree.resize(4*arr.size());
        nums = arr;
        build_tree(0,0,nums.size()-1);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node] = pii(nums[left],left);
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        if (tree[2*node+1].first<=tree[2*node+2].first){
            tree[node] = pii(tree[2*node+1].first,tree[2*node+1].second);
        }
        else{
            tree[node] = pii(tree[2*node+2].first,tree[2*node+2].second);
        }
    }
    void update(int node, int left, int right, int pos, int value){
        if (left==right){
            tree[node] = pii(value,pos);
            return;
        }
        int mid = (left+right)>>1;
        if (pos<=mid){
            update(2*node+1,left,mid,pos,value);
        }
        else{
            update(2*node+2,mid+1,right,pos,value);
        }
        if (tree[2*node+1].first<=tree[2*node+2].first){
            tree[node] = pii(tree[2*node+1].first,tree[2*node+1].second);
        }
        else{
            tree[node] = pii(tree[2*node+2].first,tree[2*node+2].second);
        }
    }
    pii query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight<left) return pii(INT_MAX,INT_MAX);
        if (arrLeft>=left && arrRight<=right) return tree[node];
        int mid = (arrLeft+arrRight)>>1;
        pii l = query(2*node+1,left,right,arrLeft,mid);
        pii r = query(2*node+2,left,right,mid+1,arrRight);
        if (l.first<=r.first){
            return l;
        }
        return r;
    }
};
struct segmax{
    vector<int> nums;
    vector<pii> tree;
    segmax(vector<int>& arr){
        tree.resize(4*arr.size());
        nums = arr;
        build_tree(0,0,nums.size()-1);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node] = pii(nums[left],left);
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        if (tree[2*node+1].first>=tree[2*node+2].first){
            tree[node] = pii(tree[2*node+1].first,tree[2*node+1].second);
        }
        else{
            tree[node] = pii(tree[2*node+2].first,tree[2*node+2].second);
        }
    }
    void update(int node, int left, int right, int pos, int value){
        if (left==right){
            tree[node] = pii(value,pos);
            return;
        }
        int mid = (left+right)>>1;
        if (pos<=mid){
            update(2*node+1,left,mid,pos,value);
        }
        else{
            update(2*node+2,mid+1,right,pos,value);
        }
        if (tree[2*node+1].first>=tree[2*node+2].first){
            tree[node] = pii(tree[2*node+1].first,tree[2*node+1].second);
        }
        else{
            tree[node] = pii(tree[2*node+2].first,tree[2*node+2].second);
        }
    }
    pii query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight<left) return pii(0,0);
        if (arrLeft>=left && arrRight<=right) return tree[node];
        int mid = (arrLeft+arrRight)>>1;
        pii l = query(2*node+1,left,right,arrLeft,mid);
        pii r = query(2*node+2,left,right,mid+1,arrRight);
        if (l.first>=r.first){
            return l;
        }
        return r;
    }
};
void solve(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    segmin seg1(nums); segmax seg2(nums);
    map<ll,vector<ll>> idx;
    for (int i = 0; i < n; i++) idx[nums[i]].emplace_back(i);
    set<int> mxidx;
    for (const auto& [k,v]: idx) mxidx.insert(v.back());
    vector<int> res (idx.size());
    int curr = 0;
    for (int i = 0; i < res.size(); i++){
        if (i%2==1){
            pii f = seg1.query(0,curr,*mxidx.begin(),0,n-1);
            res[i] = f.first;
            curr = f.second;
            for (int x = 0; x < idx[f.first].size(); x++){
                if (idx[f.first][x]>=curr){
                    seg1.update(0,0,n-1,idx[f.first][x],INT_MAX);
                    seg2.update(0,0,n-1,idx[f.first][x],0);
                }
            }
            mxidx.erase(idx[f.first].back());
        }
        else{
            pii f = seg2.query(0,curr,*mxidx.begin(),0,n-1);
            res[i] = f.first;
            curr = f.second;
            for (int x = 0; x < idx[f.first].size(); x++){
                if (idx[f.first][x]>=curr){
                    seg1.update(0,0,n-1,idx[f.first][x],INT_MAX);
                    seg2.update(0,0,n-1,idx[f.first][x],0);
                }
            }
            mxidx.erase(idx[f.first].back());
        }
    }
    cout<<res.size()<<endl;
    for (int i = 0; i < res.size(); i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   cin>>t;
   while (t--){
      solve();
   }
}