#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int MAXN = 200005;
ll pw[MAXN];
struct Info{
    ll subs[2][2];
    ll ans = 0;
    ll length = 0;
    Info(){
        for (int i = 0; i < 2; i++){
            subs[i][0] = subs[i][1] = 0;
        }
    }
};
struct SegmentTree{
    vector<Info> tree;
    string s;
    SegmentTree(int n, string st){
        tree.resize(4*n);
        s = st;
        build_tree(0,0,n-1);
    }
    void merge(Info& main, Info& left, Info& right){
        main.length = left.length + right.length;
        main.ans = ((left.ans*pw[right.length])%MOD2 + (right.ans*pw[left.length])%MOD2)%MOD2;
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                main.subs[i][j] = (left.subs[i][j] + right.subs[i][j])%MOD2;
            }
        }
        main.subs[0][0] += (((left.subs[0][0] + left.subs[0][1])%MOD2)*((right.subs[0][0] + right.subs[1][0])%MOD2))%MOD2;
        if (main.subs[0][0] >= MOD2) main.subs[0][0] -= MOD2;
        main.subs[0][1] += (((left.subs[0][0] + left.subs[0][1])%MOD2)*((right.subs[0][1] + right.subs[1][1])%MOD2))%MOD2;
        if (main.subs[0][1] >= MOD2) main.subs[0][1] -= MOD2;
        main.subs[1][0] += (((left.subs[1][0] + left.subs[1][1])%MOD2)*((right.subs[0][0] + right.subs[1][0])%MOD2))%MOD2;
        if (main.subs[1][0] >= MOD2) main.subs[1][0] -= MOD2;
        main.subs[1][1] += (((left.subs[1][0] + left.subs[1][1])%MOD2)*((right.subs[0][1] + right.subs[1][1])%MOD2))%MOD2;
        if (main.subs[1][1] >= MOD2) main.subs[1][1] -= MOD2;
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                for (int k = 0; k < 2; k++){
                    if (j==k) continue;
                    for (int l = 0; l < 2; l++){
                        main.ans += (left.subs[i][j]*right.subs[k][l])%MOD2;
                        if (main.ans >= MOD2) main.ans -= MOD2;
                    }
                }
            }
        }
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            if (s[left]=='0'){
                tree[node].subs[0][0] = 1;
            }
            else{
                tree[node].subs[1][1] = 1;
            }
            tree[node].length = 1;
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
    void upd(int node, int left, int right, int pos){
        if (left==right){
            tree[node].subs[s[left]-'0'][s[left]-'0'] = 0;
            tree[node].subs[1-(s[left]-'0')][1-(s[left]-'0')] = 1;
            s[left] = (s[left] == '0' ? '1' : '0');
            return;
        }
        int mid = (left+right)>>1;
        if (pos <= mid){
            upd(2*node+1,left,mid,pos);
        }
        else{
            upd(2*node+2,mid+1,right,pos);
        }
        merge(tree[node], tree[2*node+1], tree[2*node+2]);
    }
};
void solve(int cas){ 
    string s; cin>>s;
    int n = s.size();
    SegmentTree segTree(n, s);
    int q; cin>>q;
    vector<int> queries(q);
    for (auto& a: queries) cin>>a;
    for (int i = 0; i < q; i++){
        --queries[i];
        segTree.upd(0,0,n-1,queries[i]);
        cout << (segTree.tree[0].ans + pw[n] - 1)%MOD2<< " \n"[i==q-1];
    }
}
void pre(){
    pw[0] = 1;
    for (int i = 1; i < MAXN; i++){
        pw[i] = (pw[i-1]*2)%MOD2;
    }
}
int main(){
    pre();
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
