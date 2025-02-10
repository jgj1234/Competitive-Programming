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
struct Node{
    ll mn = LLONG_MAX;
    ll ways = 0;
    Node(){}
};
struct SegmentTree{
    vector<Node> tree;
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void merge(Node& main, Node& left, Node& right){
        main.mn = min(left.mn, right.mn);
        main.ways = 0;
        if (left.mn == main.mn){
            main.ways = left.ways;
        }
        if (right.mn == main.mn){
            main.ways += right.ways;
            if (main.ways >= MOD) main.ways -= MOD;
        }
    }
    void upd(int node, int left, int right, int pos, ll cost, ll ways){
        if (left==right){
            tree[node].mn = cost;
            tree[node].ways = ways;
            return;
        }
        int mid = (left+right)>>1;
        if (pos <= mid){
            upd(2*node+1,left,mid,pos,cost,ways);
        }
        else{
            upd(2*node+2,mid+1,right,pos,cost,ways);
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
    //dp1[n][m] -> min cost for n,m
    //dp2[n][m] -> number of ways for n,m
    int n,m; cin>>n>>m;
    vector<ll> a(n), b(m);
    for (auto& x: a) cin>>x;
    for (auto& x: b) cin>>x;
    if (b[0] < *max_element(all(a))){
        cout << -1 << '\n';
        return;
    }
    vector<ll> pref(n + 1);
    for (int i = 1; i <= n; i++) pref[i] = a[i-1] + pref[i-1];
    vector<vector<ll>> dp1(n + 1, vector<ll> (m + 1, LLONG_MAX));
    vector<vector<ll>> bres(n + 1, vector<ll> (m + 1, -1));
    for (int i = 0; i <= m; i++) dp1[n][i] = 0;
    for (int i = n - 1; i >= 0; i--){
        for (int j = m - 1; j >= 0; j--){
            dp1[i][j] = dp1[i][j+1];
            if (a[i] > b[j]) continue;
            int lp = i + 1, rp = n - 1;
            while (lp <= rp){
                int mid = (lp + rp) >> 1;
                if (pref[mid+1]-pref[i] <= b[j]){
                    lp = mid + 1;
                }
                else{
                    rp = mid - 1;
                }
            }
            bres[i][j] = lp;
            if (dp1[lp][j]!=LLONG_MAX)
                dp1[i][j] = min(dp1[i][j], m - 1 - j + dp1[lp][j]);
        }
    }
    vector<SegmentTree> trees(m+1, SegmentTree(n+1));
    vector<vector<ll>> dp2(n+1, vector<ll> (m+1));
    for (int i = 0; i <= m; i++){
        dp2[n][i] = 1;
    }
    for (int i = 0; i <= m; i++){
        trees[i].upd(0,0,n,n,0,1);
    }
    for (int i = n - 1; i >= 0; i--){
        for (int j = m - 1; j >= 0; j--){
            ll incJ = dp1[i][j+1];
            if (bres[i][j]==-1){
                if (incJ!=LLONG_MAX)
                    trees[j].upd(0,0,n,i,incJ,dp2[i][j+1]);
                dp2[i][j] = incJ;
                continue;
            }
            Node best = trees[j].query(0,i+1,bres[i][j],0,n);
            ll mncost = incJ;
            if (best.mn!=LLONG_MAX){
                mncost = min(mncost, m - 1 - j + best.mn);
            }
            ll tot = 0;
            if (incJ==mncost){
                tot = dp2[i][j+1];
            }
            if (best.mn!=LLONG_MAX && best.mn+(m-1-j)==mncost){
                tot += best.ways;
                if (tot >= MOD) tot -= MOD;
            }
            dp2[i][j] = tot;
            if (mncost!=LLONG_MAX)
                trees[j].upd(0,0,n,i,mncost,dp2[i][j]);
        }
    }
    cout << dp1[0][0] << " " << dp2[0][0] << '\n';
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
