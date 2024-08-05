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
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
struct SegmentTree{
    vector<long double> tree;
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void update(int node, int left, int right, int index, long double value){
        if (left==right){
            tree[node]=max(tree[node],value);
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            update(2*node+1,left,mid,index,value);
        }
        else{
            update(2*node+2,mid+1,right,index,value);
        }
        tree[node]=max(tree[2*node+1],tree[2*node+2]);
    }
    long double query(int node, int left, int right, int index){
        if (left>=index) return 0;
        if (right<index) return tree[node];
        int mid = (left+right)>>1;
        return max(query(2*node+1,left,mid,index),query(2*node+2,mid+1,right,index));
    }
};
void solve(){
    int n;
    cin>>n;
    vector<long double> volumes(n);
    for (int i = 0; i < n; i++){
        long double radius, height;
        cin>>radius>>height;
        volumes[i]=pi*radius*radius*height;
    }
    unordered_map<double,int> mp;
    vector<double> copy(volumes.begin(),volumes.end());
    sort(copy.begin(),copy.end());
    copy.erase(unique(copy.begin(),copy.end()),copy.end());
    for (int i = 0; i < copy.size(); i++) mp[copy[i]]=i;
    SegmentTree segTree(mp.size());
    for (int i = 0; i < n; i++){
        long double mx = volumes[i]+segTree.query(0,0,mp.size()-1,mp[volumes[i]]);
        segTree.update(0,0,mp.size()-1,mp[volumes[i]],mx);
    }
    cout<<fixed<<setprecision(10)<<segTree.tree[0]<<endl;
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