#include <bits/stdc++.h>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Node{
    vector<ll> pref;
    vector<ll> suff;
    ll ev = 0;
    ll msk = 0;
    bool nl = false;
    Node(): pref(64), suff(64) {}
};
struct SegmentTree{
    vector<Node> tree;
    SegmentTree (int n, string& s){
        tree.resize(4*n);
        build_tree(0,0,n-1,s);
    };
    void merge(Node& res, Node& left, Node& right){
        if (left.nl){
            res.ev = right.ev;
            res.msk = right.msk;
            for (int i = 0; i < 1<<6; i++){
                res.suff[i] = right.suff[i];
                res.pref[i] = right.pref[i];
            }
            return;
        }
        if (right.nl){
            res.ev = left.ev;
            res.msk = left.msk;
            for (int i = 0; i < 1<<6; i++){
                res.suff[i] = left.suff[i];
                res.pref[i] = left.pref[i];
            }
            return;
        }
        res.ev=left.ev + right.ev;
        res.msk = left.msk^right.msk;
        for (int i = 0; i < 1<<6; i++){
            res.suff[i] += right.suff[i];
            res.pref[i] += left.pref[i];
            res.suff[right.msk^i] += left.suff[i];
            res.pref[left.msk^i] += right.pref[i];
            res.ev+=left.suff[i]*right.pref[i];
        }
    };
    void build_tree(int node, int arrLeft, int arrRight, string& s) {
        if (arrLeft==arrRight){
            ll m = 1<<(s[arrLeft]-'a');
            tree[node].pref[m] = 1;
            tree[node].suff[m] = 1;
            tree[node].msk = m;
            return;
        }
        int mid = (arrLeft + arrRight)>>1;
        build_tree(2*node+1,arrLeft, mid, s);
        build_tree(2*node+2,mid+1,arrRight, s);
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
    void update(int node, int arrLeft, int arrRight, int index, char c) {
        for (int i = 0; i < 1<<6; i++){
            tree[node].pref[i] = 0;
            tree[node].suff[i] = 0;
        }
        tree[node].ev = 0;
        if (arrLeft==arrRight){
            ll m = 1<<(c-'a');
            tree[node].pref[m] = 1;
            tree[node].suff[m] = 1;
            tree[node].msk = m;
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        if (index <= mid){
            update(2*node+1,arrLeft,mid,index,c);
        }
        else{
            update(2*node+2,mid+1,arrRight,index,c);
        }
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
    Node query(int node, int left, int right, int arrLeft, int arrRight) {
        if (arrLeft >= left && arrRight<=right) return tree[node];
        if (arrLeft > right || arrRight < left){
            Node n = Node();
            n.nl = true;
            return n;
        }
        int mid = (arrLeft + arrRight) >> 1;
        Node l = query(2*node+1,left,right, arrLeft, mid);
        Node r = query(2*node+2,left,right,mid+1,arrRight);
        Node res;
        merge(res,l,r);
        return res;
    }
};
void solve(int cas){
    string s;
    cin>>s;
    int q; cin>>q;
    SegmentTree segTree(s.size(), s);
    while (q--){
        int t;
        cin>>t;
        if (t==1){
            int l,r;
            cin>>l>>r;
            --l;--r;
            cout<<segTree.query(0,l,r,0,s.size()-1).ev<<endl;
        }
        else{
            int i; char c;
            cin>>i>>c;
            --i;
            segTree.update(0,0,s.size()-1, i, c);
        }
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
