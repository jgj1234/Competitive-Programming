#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
ll base;
const ll mod = (1ULL<<61) - 1;
const int N = 200005;
ll pw[N], sm[N];
int64_t modmul(uint64_t a, uint64_t b){
    uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret - 1;
}
struct Node{
    ll val;
    int sz;
    bool nl = false;
    Node(){}
};
struct ST{
    vector<Node> tree;
    vector<int> lazy;
    string s;
    ST(string& str){
        s = str;
        tree.resize(4*(int)s.size());
        lazy.resize(4*(int)s.size(),-1);
        build(0,0,s.size() - 1);
    }
    void merge(Node& main, Node& left, Node& right){
        if (left.nl){
            main.sz = right.sz;
            main.val = right.val;
        }
        else if (right.nl){
            main.sz = left.sz;
            main.val = left.val;
        }
        else{
            main.sz = left.sz + right.sz;
            main.val = (left.val + modmul(right.val, pw[left.sz]))%mod;
        }
    }
    void build(int node, int left, int right){
        if (left==right){
            tree[node].val = ((s[left] - '0')*base)%mod;
            tree[node].sz = 1;
            return;
        }
        int mid = (left+right)>>1;
        build((node << 1) | 1, left,mid);
        build((node << 1) + 2, mid + 1, right);
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
    void push(int node, int arrLeft, int arrRight){
        tree[node].val = modmul(lazy[node],sm[tree[node].sz]);
        if (arrLeft!=arrRight){
            lazy[2*node+1] = lazy[node];
            lazy[2*node+2] = lazy[node];
        }
        lazy[node] = -1;
    }
    void upd(int node, int left, int right, int arrLeft, int arrRight, int dig){
        if (lazy[node]!=-1){
            push(node, arrLeft, arrRight);
        }
        if (arrLeft > right || arrRight < left) return;
        if (arrLeft >= left && arrRight <= right){
            lazy[node] = dig;
            push(node, arrLeft, arrRight);
            return;
        }
        int mid = (arrLeft + arrRight) >> 1;
        upd(2*node+1,left,right,arrLeft,mid,dig);
        upd(2*node+2,left,right,mid+1,arrRight,dig);
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
    Node get(int node, int left, int right, int arrLeft, int arrRight){
        if (lazy[node]!=-1){
            push(node, arrLeft, arrRight);
        }

        if (arrLeft > right || arrRight < left){
            Node nd;
            nd.nl = true;
            return nd;
        }
        if (arrLeft >= left && arrRight <= right) return tree[node];
        int mid = (arrLeft + arrRight) >> 1;
        Node main;
        Node l = get(2*node+1,left,right,arrLeft,mid), r = get(2*node+2,left,right,mid+1,arrRight);
        merge(main,l,r);
        return main;
    }
};
void solve(int cas){
    int n,m,k; cin>>n>>m>>k;
    string s; cin>>s;
    mt19937 dev{random_device{}()};
    uniform_int_distribution<int64_t> hGen(0,INT_MAX-1);
    base = hGen(dev);
    pw[0] = 1;
    for (int i = 1; i < N; i++){
        pw[i] = modmul(pw[i-1],base);
        sm[i] = (sm[i-1] + pw[i])%mod;
    }
    ST segTree(s);
    for (int j = 0; j < m + k; j++){
        int x; cin>>x;
        if (x==1){
            int l,r,c; cin>>l>>r>>c;
            --l;--r;
            segTree.upd(0,l,r,0,n-1,c);
        }
        else{
            int l,r,d; cin>>l>>r>>d;
            --l;--r;
            if (r-l+1==d){
                cout << "YES\n";
            }
            else{
                ll h1 = segTree.get(0,l,r-d,0,n-1).val, h2 = segTree.get(0,l+d,r,0,n-1).val;
                cout << (h1==h2 ? "YES" : "NO") << '\n';
            }
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