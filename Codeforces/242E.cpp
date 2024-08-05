#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>

#include <cmath>
#define pii pair<int,int>
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
    vector<vector<ll>> tree;
    vector<vector<ll>> lazy;
    vector<bool> pending;
    vector<int> nums;
    SegmentTree(vector<int> arr){
        nums=arr;
        tree.resize(4*arr.size(),vector<ll> (20));
        lazy.resize(4*arr.size(),vector<ll>(20));
        pending.resize(4*arr.size());
        build_tree(0,0,arr.size()-1);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            for (int i = 0; i < 20; i++){
                tree[node][i]=(nums[left]&(1<<i))!=0;
            }
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        for (int i = 0; i < 20; i++){
            tree[node][i]=tree[2*node+1][i]+tree[2*node+2][i];
        }
    }
    void update(int node, int left, int right, int arrLeft, int arrRight, int x){
        if (pending[node]){
            for (int i = 0; i < 20; i++){
                if (lazy[node][i]){
                    tree[node][i]=(arrRight-arrLeft+1)-tree[node][i];
                    if (arrLeft!=arrRight){
                        lazy[2*node+1][i]=!lazy[2*node+1][i];
                        lazy[2*node+2][i]=!lazy[2*node+2][i];
                    }
                    lazy[node][i]=false;
                }
            }
            if (arrLeft!=arrRight){
                    pending[2*node+1]=true;
                    pending[2*node+2]=true;
                }
                pending[node]=false;
        }
        if (arrLeft>right || arrRight < left) return;
        if (arrLeft>=left && arrRight<=right){
            for (int i = 0; i < 20; i++){
                if ((x&(1<<i))!=0){
                    tree[node][i]=(arrRight-arrLeft+1)-tree[node][i];
                    if (arrLeft!=arrRight){
                        lazy[2*node+1][i]=!lazy[2*node+1][i];
                        lazy[2*node+2][i]=!lazy[2*node+2][i];
                    }
                }
            }
            if (arrLeft!=arrRight){
                    pending[2*node+1]=true;
                    pending[2*node+2]=true;
            }
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        update(2*node+1,left,right,arrLeft,mid,x);
        update(2*node+2,left,right,mid+1,arrRight,x);
        for (int i = 0; i < 20; i++){
            tree[node][i]=tree[2*node+1][i]+tree[2*node+2][i];
        }
        
    }
    ll query(int node, int left, int right, int arrLeft, int arrRight){
        if (pending[node]){
            for (int i = 0; i < 20; i++){
                if (lazy[node][i]){
                    tree[node][i]=(arrRight-arrLeft+1)-tree[node][i];
                    if (arrLeft!=arrRight){
                        lazy[2*node+1][i]=!lazy[2*node+1][i];
                        lazy[2*node+2][i]=!lazy[2*node+2][i];
                    }
                    lazy[node][i]=false;
                }
            }
            if (arrLeft!=arrRight){
                    pending[2*node+1]=true;
                    pending[2*node+2]=true;
                }
                pending[node]=false;
        }
        if (arrLeft>right||arrRight<left) return 0;
        if (arrLeft>=left && arrRight<=right){
            ll res = 0;
            for (int i = 0; i < 20; i++){
                if (tree[node][i]!=0){
                    res+=(tree[node][i]<<i);
                }
            }
            return res;
        }
        int mid = (arrLeft+arrRight)>>1;
        return query(2*node+1,left,right,arrLeft,mid)+query(2*node+2,left,right,mid+1,arrRight);
    }
};


void solve(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    SegmentTree segTree(nums);
    int m;
    cin>>m;
    for (int i = 0; i < m; i++){
        int t;
        cin>>t;
        if (t==1){
            int l,r;
            cin>>l>>r;
            cout<<segTree.query(0,l-1,r-1,0,n-1)<<endl;
        }
        else{
            int l,r,x;
            cin>>l>>r>>x;
            segTree.update(0,l-1,r-1,0,n-1,x);
        }
    }
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