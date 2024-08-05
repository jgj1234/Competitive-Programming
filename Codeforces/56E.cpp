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
#pragma GCC optimize ("O3")

struct SegmentTree{
    vector<pii> tree; //Sum + max index that it hits to nullify
    vector<bool> lazy;
    SegmentTree(int n){
        tree.resize(4*n);
        lazy.resize(4*n);
    }
    void update(int node, int left, int right, int index, int sm, int mx){
        if (lazy[node]){
            if (left!=right){
                tree[2*node+1].first = 0; tree[2*node+1].second = 0; tree[2*node+2].first = 0; tree[2*node+2].second = 0;
                lazy[2*node+1]=true; lazy[2*node+2]=true;
            }
            lazy[node]=false;
        }
        if (left==right){
            tree[node].first = sm;
            tree[node].second = mx;
            return;
        }
        int mid = (left+right)>>1;
        if (index<=mid){
            update(2*node+1,left,mid,index,sm,mx);
        }
        else{
            update(2*node+2,mid+1,right,index,sm,mx);
        }
        tree[node].first=tree[2*node+1].first+tree[2*node+2].first;
        tree[node].second = max(tree[2*node+1].second,tree[2*node+2].second);
    }
    void nullRange(int node, int left, int right, int arrLeft, int arrRight){
        //cout<<left<<" "<<right<<" "<<arrLeft<<" "<<arrRight<<endl;
        if (lazy[node]){
            if (arrLeft!=arrRight){
                tree[2*node+1].first = 0; tree[2*node+1].second = 0; tree[2*node+2].first = 0; tree[2*node+2].second = 0;
                lazy[2*node+1]=true; lazy[2*node+2]=true;
            }
            lazy[node]=false;
        }
        if (arrLeft>right || arrRight<left) return;
        if (arrLeft>=left && arrRight<=right){
            //cout<<arrLeft<<" "<<arrRight<<endl;
            tree[node].first = 0;
            tree[node].second = 0;
            if (arrLeft!=arrRight){
                tree[2*node+1].first = 0; tree[2*node+1].second = 0; tree[2*node+2].first = 0; tree[2*node+2].second = 0;
                lazy[2*node+1]=true;
                lazy[2*node+2]=true;
            }
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        nullRange(2*node+1,left,right,arrLeft,mid);
        nullRange(2*node+2,left,right,mid+1,arrRight);
        tree[node].first=tree[2*node+1].first+tree[2*node+2].first;
        tree[node].second = max(tree[2*node+1].second,tree[2*node+2].second);
    }
    pii query(int node, int left, int right, int arrLeft, int arrRight){
        if (lazy[node]){
            if (arrLeft!=arrRight){
                tree[2*node+1].first = 0; tree[2*node+1].second = 0; tree[2*node+2].first = 0; tree[2*node+2].second = 0;
                lazy[2*node+1]=true; lazy[2*node+2]=true;
            }
            lazy[node]=false;
        }
        //cout<<node<<" "<<left<<" "<<right<<" "<<arrLeft<<" "<<arrRight<<" "<<tree[node].first<<endl;
        if (arrLeft>right || arrRight<left) return pii(0,0);
        if (arrLeft>=left && arrRight<=right) return tree[node];
        int mid = (arrLeft+arrRight)>>1;
        pii l = query(2*node+1,left,right,arrLeft,mid);
        pii r = query(2*node+2,left,right,mid+1,arrRight);
        return pii(l.first+r.first,max(l.second,r.second));
    }
};
void solve(){
    int n;
    cin>>n;
    vector<pii> nums(n);
    for (int i = 0; i < n; i++) cin>> nums[i].first >> nums[i].second;
    map<int,int> indexmp;
    set<int> p1;
    for (int i = 0; i < n; i++){
        indexmp[nums[i].first]=i;
        p1.insert(nums[i].first);
        p1.insert(nums[i].first+nums[i].second-1);
    }
    sort(nums.begin(),nums.end());
    map<int,int> points; int idx = 0;
    for (int p: p1){
        points[p]=idx++;
    }
    SegmentTree segTree(idx);
    vector<int> res(n);
    for (int i = n - 1; i >= 0; i--){
        int index = indexmp[nums[i].first];
        pii ans = segTree.query(0,points[nums[i].first],points[nums[i].first+nums[i].second-1],0,p1.size()-1);
        ans.first++;
        ans.second = max(ans.second,points[nums[i].first+nums[i].second-1]);
        segTree.nullRange(0,points[nums[i].first],ans.second,0,p1.size()-1);
        segTree.update(0,0,p1.size()-1,points[nums[i].first],ans.first,ans.second);
        res[index]=ans.first;
    }
    for (int i = 0; i < n; i++){
        cout<<res[i]<<" ";
    }
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   // cin>>t;
   while (t--){
      solve();
   }
}