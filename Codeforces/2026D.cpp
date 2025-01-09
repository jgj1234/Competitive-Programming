#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct node{
    int range = 0, sm = 0, acsm = 0;
    node(){}
};
struct SegmentTree{
    vector<ll> nums;
    vector<node> tree;
    SegmentTree(vector<ll>& arr){
        nums = arr;
        tree.resize(4*arr.size());
        build_tree(0,0,arr.size()-1);
    }
    void merge(node& main, node& left, node& right){
        main.sm = left.sm+right.sm+left.acsm*right.range;
        main.acsm = left.acsm+right.acsm;
        main.range = left.range+right.range;
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node].range = 1;
            tree[node].sm = tree[node].acsm = nums[left];
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
    node query(int nd, int left, int right, int arrLeft, int arrRight){
        if (arrLeft > right || arrRight < left) return node();
        if (arrLeft >= left && arrRight <= right) return tree[nd];
        int mid = (arrLeft + arrRight) >> 1;
        node res;
        node l = query(2*nd+1,left,right,arrLeft,mid), r = query(2*nd+2,left,right,mid+1,arrRight);
        merge(res,l,r);
        return res;
    }
};
void solve(int cas){  
    int n; cin>>n;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    int q; cin>>q;
    vector<ll> suff(n);
    suff[n-1] = nums.back();
    for (int i = n - 2; i >= 0; i--){
        suff[i] = nums[i]*(n-i) + suff[i+1];
    }
    vector<ll> psuff(n);
    psuff[0] = suff[0];
    for (int i = 1; i < n; i++) psuff[i] = suff[i] + psuff[i-1];
    SegmentTree segTree(nums);
    auto sum = [&] (ll l, ll r) -> ll{
        if (l==0) return r*(r+1)/2;
        return r*(r+1)/2 - l*(l-1)/2;
    };
    auto get = [&] (ll index) -> ll{
        int lp = 0, rp = n - 1;
        while (lp <= rp){
            int mid = (lp + rp) >> 1;
            ll sm = sum(n - mid, n);
            if (sm <= index){
                lp = mid + 1;
            }
            else{
                rp = mid - 1;
            }
        }
        ll res = (rp < 0 ? 0: psuff[rp]);
        ll start = rp + 1, end = rp + 1;
        ll bef = rp < 0 ? 0: sum(n - rp, n);
        end += index - bef;
        return res + segTree.query(0,start,end,0,n-1).sm;
    };
    while (q--){
        ll l,r; cin>>l>>r;
        --r; --l;
        cout << get(r) - (l==0?0:get(l-1)) << '\n';
    }
    
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}