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
    vector<pii> tree; //Length of subsequence then last index
    SegmentTree(int n){
        tree.resize(4*n);
        //for (int i = 0; i < tree.size(); i++) tree[i]=pii(-1,-1);
    }
    void update(int node, int left, int right, int index, int realIndex, int value){
        if (left==right){
            if (value>tree[node].first){
                tree[node].first=value;
                tree[node].second=realIndex;
            }
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            update(2*node+1,left,mid,index,realIndex,value);
        }
        else{
            update(2*node+2,mid+1,right,index,realIndex,value);
        }
        if (tree[2*node+1].first>=tree[2*node+2].first){
            tree[node].first=tree[2*node+1].first;
            tree[node].second=tree[2*node+1].second;
        }
        else{
            tree[node].first=tree[2*node+2].first;
            tree[node].second=tree[2*node+2].second;
        }
    }
    pii queryGreater(int node, int left, int right, int index){
        if (right<index) return pii(-1,-1);
        if (left>=index) return tree[node];
        int mid = (left+right)>>1;
        pii l = queryGreater(2*node+1,left,mid,index);
        pii r = queryGreater(2*node+2,mid+1,right,index);
        if (l.first>=r.first) return l;
        return r;
    }
    pii queryLess(int node, int left, int right, int index){
        if (left>index) return pii(-1,-1);
        if (right<=index) return tree[node];
        int mid = (left+right)>>1;
        pii l = queryLess(2*node+1,left,mid,index);
        pii r = queryLess(2*node+2,mid+1,right,index);
        if (l.first>=r.first) return l;
        return r;
    }
};
void solve(){
    int n,d;
    cin>>n>>d;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    unordered_map<ll,int> mp;
    vector<ll> copy(nums.begin(),nums.end());
    sort(copy.begin(),copy.end());
    copy.erase(unique(copy.begin(),copy.end()),copy.end());
    for (int i = 0; i < copy.size(); i++){
        mp[copy[i]]=i;
    }
    SegmentTree segTree(mp.size());
    vector<int> last(n);
    for (int i = 0; i < n; i++){
        int lp = 0; int rp = copy.size() - 1;
        while (lp<=rp){
            int mid = (lp+rp)>>1;
            if (copy[mid]>nums[i]-d){
                rp=mid-1;
            }
            else{
                lp=mid+1;
            }
        }
        int lower = rp;
        pii lowerLength = pii(-1,-1);
        if (lower>=0)
            lowerLength = segTree.queryLess(0,0,mp.size()-1,mp[copy[lower]]);
        lp = 0; rp = copy.size() - 1;
        while (lp<=rp){
            int mid = (lp+rp)>>1;
            if (copy[mid]<nums[i]+d){
                lp=mid+1;
            }
            else{
                rp=mid-1;
            }
        }
        int upper = lp;
        pii upperLength = pii(-1,-1);
        if (upper<mp.size())
            upperLength = segTree.queryGreater(0,0,mp.size()-1,mp[copy[upper]]);
        segTree.update(0,0,mp.size()-1,mp[nums[i]],i,1+max(max(lowerLength.first,upperLength.first),0));
        if (lowerLength.first>=upperLength.first){
            last[i]=lowerLength.second;
        }
        else{
            last[i]=upperLength.second;
        }
        //cout<<i<<endl;
    //cout<<lower<<" "<<lowerLength.first<<" "<<lowerLength.second<<endl;
    //cout<<upper<<" "<<upperLength.first<<" "<<upperLength.second<<endl;
    }
    vector<int> res(segTree.tree[0].first);
    cout<<segTree.tree[0].first<<endl;
    for (int i = 0, c = segTree.tree[0].second; i < res.size(); i++, c = last[c]){
        res[i]=c+1;
    }
    for (int i = res.size() - 1; i>=0; i--){
        cout<<res[i]<<" ";
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