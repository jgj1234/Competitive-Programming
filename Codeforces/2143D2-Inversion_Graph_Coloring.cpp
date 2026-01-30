#include <bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct Node{
    ll sm = 0;
    Node(){}
};
struct SegmentTree{
    vector<Node> tree;
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void merge(Node& main, Node& left, Node& right){
        main.sm = left.sm + right.sm;
        if (main.sm >= MOD) main.sm -= MOD;
    }
    void upd(int node, int left, int right, int pos, ll val){
        if (left==right){
            tree[node].sm += val;
            if (tree[node].sm >= MOD) tree[node].sm -= MOD;
            return;
        }
        int mid = (left+right)>>1;
        if (pos <= mid){
            upd(2*node+1,left,mid,pos,val);
        }
        else{
            upd(2*node+2,mid+1,right,pos,val);
        }
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
    Node query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft > right || arrRight < left) return Node();
        if (arrLeft >= left && arrRight <= right) return tree[node];
        Node res;
        int mid = (arrLeft + arrRight) >> 1;
        Node l = query(2*node+1,left,right,arrLeft,mid);
        Node r = query(2*node+2,left,right,mid+1,arrRight);
        merge(res, l, r);
        return res;
    }
};
void solve(int cas){
    int n; cin>>n;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    vector<SegmentTree> st1(n + 1, SegmentTree(n + 1)), st2(n + 1, SegmentTree(n + 1));
    st1[0].upd(0,0,n,0,1);
    st2[0].upd(0,0,n,0,1);
    for (int i = 0; i < n; i++){
        vector<ll> ladd(n - nums[i]), radd(nums[i] + 1);
        for (int j = nums[i] + 1; j <= n; j++){
            ll bef = st1[j].query(0,0,nums[i],0,n).sm;
            ladd[j - nums[i] - 1] = bef;
        }
        for (int j = 0; j <= nums[i]; j++){
            ll bef = st2[j].query(0,j,nums[i],0,n).sm;
            radd[j] = bef;
        }
        for (int j = nums[i] + 1; j <= n; j++){
            st1[j].upd(0,0,n,nums[i],ladd[j - nums[i] - 1]);
            st2[nums[i]].upd(0,0,n,j,ladd[j - nums[i] - 1]);
        }
        for (int j = 0; j <= nums[i]; j++){
            st1[nums[i]].upd(0,0,n,j,radd[j]);
            st2[j].upd(0,0,n,nums[i],radd[j]);
        }
    }
    ll res = 0;
    for (int i = 0; i <= n; i++){
        res += st1[i].tree[0].sm;
        if (res >= MOD) res -= MOD;
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