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
    vector<ll> tree;
    vector<int> nums;
    SegmentTree(vector<int> arr){
        tree.resize(4*arr.size());
        nums = arr;
        build_tree(0,0,nums.size()-1);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node]=nums[left];
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
    }
    void update(int node, int left, int right, int arrLeft, int arrRight, ll val){
        if (tree[node]!=0){
            if (arrLeft!=arrRight){
                tree[2*node+1]+=tree[node];
                tree[2*node+2]+=tree[node];
                tree[node]=0;
            }
        }
        if (arrLeft>right || arrRight<left) return;
        if (arrLeft>=left && arrRight<=right){
            tree[node]+=val;
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        update(2*node+1,left,right,arrLeft,mid,val);
        update(2*node+2,left,right,mid+1,arrRight,val);
    }
    ll query(int node, int left, int right, int pos){
        if (tree[node]!=0){
            if (left!=right){
                tree[2*node+1]+=tree[node];
                tree[2*node+2]+=tree[node];
                tree[node]=0;
            }
        }
        if (left==right) return tree[node];
        int mid = (left+right)>>1;
        if (pos<=mid){
            return query(2*node+1,left,mid,pos);
        }
        else{
            return query(2*node+2,mid+1,right,pos);
        }
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> values(n);
    for (int i = 0; i < n; i++) cin>>values[i];
    if (n==1){
        ll ans = values[0];
        while (m--){
            int t;
            cin>>t;
            if (t==1){
                int x,val;
                cin>>x>>val;
                ans+=val;
            }
            else{
                int x; cin>>x;
                cout<<ans<<endl;
            }
        }
        return;
    }
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    int pos = 0;
    vector<pii> p0,p1;
    vector<pii> mp(n);
    vector<pii> sz(n);
    auto dfs = [&] (auto self, int node, int parent, int depth) -> pii{
        if (depth%2==0){
            mp[node]=pii(0,pos);
            p0.emplace_back(pos,values[node]);
        }
        else{
            mp[node]=pii(1,pos);
            p1.emplace_back(pos,values[node]);
        }
        pos++;
        pii res = pii(int(depth%2==0),int(depth%2==1));
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                pii a = self(self,neighbor,node,depth+1);
                res.first+=a.first; res.second+=a.second;
            }
        }
        return sz[node]=res;
    };
    dfs(dfs,0,-1,0);
    vector<int> a0,a1;
    for (int i = 0; i < p0.size(); i++){
        a0.emplace_back(p0[i].second);
    }
    for (int i = 0; i < p1.size(); i++){
        a1.emplace_back(p1[i].second);
    }
    SegmentTree s0(a0), s1(a1);
    while (m--){
        int t;
        cin>>t;
        if (t==1){
            int x,val;
            cin>>x>>val;
            --x;
            int l0 = lower_bound(p0.begin(),p0.end(),mp[x].second,[](const pii &a, int b) { return a.first < b; })-p0.begin();
            int l1 = lower_bound(p1.begin(),p1.end(),mp[x].second,[](const pii &a, int b) { return a.first < b; })-p1.begin();
            if (mp[x].first==0){
                s0.update(0,l0,l0+sz[x].first-1,0,a0.size()-1,val);
                s1.update(0,l1,l1+sz[x].second-1,0,a1.size()-1,-1*val);
            }
            else{
                s0.update(0,l0,l0+sz[x].first-1,0,a0.size()-1,-1*val);
                s1.update(0,l1,l1+sz[x].second-1,0,a1.size()-1,val);
            }
        }
        else{
            int x;
            cin>>x;
            --x;
            if (mp[x].first==0){
                int l0 = lower_bound(p0.begin(),p0.end(),mp[x].second,[](const pii &a, int b) { return a.first < b; })-p0.begin();
                cout<<s0.query(0,0,a0.size()-1,l0)<<endl;
            }
            else{
                int l1 = lower_bound(p1.begin(),p1.end(),mp[x].second,[](const pii &a, int b) { return a.first < b; })-p1.begin();
                cout<<s1.query(0,0,a1.size()-1,l1)<<endl;
            }
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