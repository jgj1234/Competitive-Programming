#include <bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct Node{
    ll sm = 0, lazy = 1;
    Node(){}
};
struct LazySegmentTree{
    vector<Node> tree;
    LazySegmentTree(int n){
        tree.resize(4 * n);
    }
    void push(int node, int l, int r){
        tree[node].sm = (tree[node].sm * tree[node].lazy)%MOD2;
        if (l != r){
            tree[2 * node + 1].lazy = (tree[2 * node + 1].lazy * tree[node].lazy)%MOD2;
            tree[2 * node + 2].lazy = (tree[2 * node + 2].lazy * tree[node].lazy)%MOD2;
        }
        tree[node].lazy = 1;
    }
    void mult(int node, int l, int r, int al, int ar){
        if (tree[node].lazy != 1){
            push(node, al, ar);
        }
        if (al > r || ar < l) return;
        if (al >= l && ar <= r){
            tree[node].lazy = (tree[node].lazy * 2)%MOD2;
            push(node, al, ar);
            return;
        }
        int mid = (al + ar)/2;
        mult(2*node+1,l,r,al,mid);
        mult(2*node+2,l,r,mid+1,ar);
        tree[node].sm = (tree[2*node+1].sm + tree[2*node+2].sm)%MOD2;
    }
    void add(int node, int l, int al, int ar, ll x){
        if (tree[node].lazy != 1){
            push(node, al, ar);
        }
        if (al == ar){
            tree[node].sm = (tree[node].sm + x)%MOD2;
            return;
        }
        int mid = (al + ar)/2;
        if (l <= mid){
            add(2*node+1,l,al,mid,x);
        }
        else{
            add(2*node+2,l,mid+1,ar,x);
        }
        tree[node].sm = (tree[2*node+1].sm + tree[2*node+2].sm)%MOD2;
    }
    ll query(int node, int l, int al, int ar){
        if (tree[node].lazy != 1) push(node, al, ar);
        if (al == ar) return tree[node].sm;
        int mid = (al + ar)/2;
        ll res;
        if (l <= mid){
            res = query(2*node+1,l,al,mid);
        }
        else{
            res = query(2*node+2,l,mid+1,ar);
        }
        tree[node].sm = (tree[2*node+1].sm + tree[2*node+2].sm)%MOD2;
        return res;
    }
};
void solve(int cas){
    int n; cin>>n;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    vector<ll> l = {nums[0]}, r = {nums.back()};
    for (int i = 1; i < n; i++){
        if (nums[i] > l.back()) l.emplace_back(nums[i]);
    }
    for (int i = n - 2; i >= 0; i--){
        if (nums[i] > r.back()) r.emplace_back(nums[i]);
    }
    map<int, int> posl, posr;
    for (int i = 0; i < l.size(); i++) posl[l[i]] = i;
    for (int i = 0; i < r.size() - 1; i++) posr[r[i]] = i;
    LazySegmentTree lt(l.size()), rt(r.size() - 1);
    vector<ll> numR(n);
    if (r.size() == 1){
        fill(numR.begin(), numR.end(), 1);
    }
    else{
        for (int i = n - 1; i >= 0; i--){
            if (posr.count(nums[i])){
                int x = posr[nums[i]];
                ll bef = x == 0 ? 1 : rt.query(0,x-1,0,r.size()-2);
                rt.mult(0,x,r.size()-2,0,r.size()-2);
                rt.add(0,x,0,r.size()-2,bef);
            }
            else if (nums[i] != l.back()){
                int lp = 0, rp = r.size() - 2;
                while (lp <= rp){
                    int mid = (lp + rp)/2;
                    if (r[mid] >= nums[i]){
                        rp = mid - 1;
                    }
                    else{
                        lp = mid + 1;
                    }
                }
                rt.mult(0,lp,r.size()-2,0,r.size()-2);
            }
            if (nums[i] == l.back()){
                numR[i] = rt.query(0,r.size()-2,0,r.size()-2);
            }
        }
    }
    ll res = 0;
    for (int i = 0; i < n; i++){
        if (nums[i] == l.back()){
            ll bbef = l.size() == 1 ? 1: lt.query(0,l.size()-2,0,l.size()-1);
            ll bef = lt.query(0,l.size()-1,0,l.size()-1);
            res += ((bef + bbef) * numR[i])%MOD2;
            if (res >= MOD2) res -= MOD2;
        }
        if (posl.count(nums[i])){
            int x = posl[nums[i]];
            ll bef = x == 0 ? 1: lt.query(0,x-1,0,l.size()-1);
            lt.mult(0,x,l.size()-1,0,l.size()-1);
            lt.add(0,x,0,l.size()-1,bef);
        }
        else{
            int lp = 0, rp = l.size() - 1;
            while (lp <= rp){
                int mid = (lp + rp)/2;
                if (l[mid] >= nums[i]){
                    rp = mid - 1;
                }
                else{
                    lp = mid + 1;
                }
            }
            lt.mult(0,lp,l.size()-1,0,l.size()-1);
        }
    }
    cout << res << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}