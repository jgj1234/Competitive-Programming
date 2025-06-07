#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 200005;
ll nums[N], sz[4*N], gr[4*N];
pair<ll,ll> lazy[N<<2];
ll tree[N<<2];
void build(int node, int left, int right){
    sz[node] = right - left + 1;
    if (left==right){
        tree[node] = nums[left];
        return;
    }
    int mid = (left+right)/2;
    gr[node] = mid + 1 - left;
    build(2*node+1, left, mid);
    build(2*node+2, mid + 1, right);
    tree[node] = tree[2*node+1] + tree[2*node+2];
}
void push(int node){
    auto [coeff, ct] = lazy[node];
    tree[node] += coeff*sz[node] + ct*(sz[node]*(sz[node]+1)/2);
    if (sz[node] > 1){
        lazy[2*node+1].first += coeff;
        lazy[2*node+1].second += ct;
        lazy[2*node+2].first += coeff + gr[node]*ct;
        lazy[2*node+2].second += ct;
    }
    lazy[node] = make_pair(0,0);
}
void upd(int node, int left, int right, int arrLeft, int arrRight){
    if (lazy[node].second){
        push(node);
    }
    if (arrLeft > right || arrRight < left) return;
    if (arrLeft >= left && arrRight <= right){
        lazy[node].first += arrLeft - left;
        lazy[node].second++;
        push(node);
        return;
    }
    int mid = (arrLeft + arrRight)/2;
    upd(2*node+1, left, right, arrLeft, mid);
    upd(2*node+2, left, right, mid + 1, arrRight);
    tree[node] = tree[2*node+1] + tree[2*node+2];
}
ll query(int node, int left, int right, int arrLeft, int arrRight){
    if (lazy[node].second){
        push(node);
    }
    if (arrLeft > right || arrRight < left) return 0;
    if (arrLeft >= left && arrRight <= right) return tree[node];
    int mid = (arrLeft + arrRight)/2;
    ll res = query(2*node+1, left, right, arrLeft, mid) + query(2*node+2, left, right, mid + 1, arrRight);
    tree[node] = tree[2*node+1] + tree[2*node+2];
    return res;
}
void solve(int cas){
    int n,q; cin>>n>>q;
    for (int i = 0; i < n; i++) cin>>nums[i];
    build(0,0,n-1);
    while (q--){
        int t,a,b; cin>>t>>a>>b;
        --a;--b;
        if (t==1){
            upd(0,a,b,0,n-1);
        }
        else{
            cout << query(0,a,b,0,n-1) << '\n';
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    //cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}