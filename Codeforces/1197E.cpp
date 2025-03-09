#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct Node{
    ll mn = LLONG_MAX, ct = 0;
    Node(){}
};
struct SegmentTree{
    vector<Node> tree;
    SegmentTree(int n){
        tree.resize(4*n);
    }
    void merge(Node& main, Node& left, Node& right){
        main.mn = min(left.mn, right.mn);
        if (left.mn < right.mn){
            main.ct = left.ct;
        }
        else if (right.mn < left.mn){
            main.ct = right.ct;
        }
        else{
            main.ct = (left.ct + right.ct)%MOD;
        }
    }
    void upd(int node, int left, int right, int pos, int mn, int ct){
        if (left==right){
            if (mn < tree[node].mn){
                tree[node].mn = mn;
                tree[node].ct = ct;
            }
            else if (tree[node].mn==mn){
                tree[node].ct += ct;
                tree[node].ct%=MOD;
            }
            return;
        }
        int mid = (left+right)>>1;
        if (pos <= mid){
            upd(2*node+1,left,mid,pos,mn,ct);
        }
        else{
            upd(2*node+2,mid+1,right,pos,mn,ct);
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
    vector<pair<ll,ll>> nums(n);
    for (auto& a: nums) cin>>a.first>>a.second; // out, in
    sort(nums.rbegin(), nums.rend());
    ll max_in = 0;
    for (int i = 0; i < n; i++){
        max_in = max(max_in, nums[i].second);
    }
    vector<bool> last(n), first(n);
    for (int i = 0; i < n; i++){
        if (nums[n-1].first > nums[i].second) last[i] = true;
        if (nums[i].first > max_in) first[i] = true;
    }
    vector<ll> vals;
    for (int i = 0; i < n; i++){
        vals.emplace_back(nums[i].first);
        vals.emplace_back(nums[i].second);
    }
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    map<ll,ll> mp;
    int idx = 0;
    for (int i = 0; i < vals.size(); i++) mp[vals[i]] = idx++;
    SegmentTree segTree(idx);
    ll res = 0;
    vector<pair<ll,ll>> mns;
    for (int i = 0; i < n; i++){
        Node r = segTree.query(0,mp[nums[i].first],idx-1,0,idx-1);
        if (r.mn!=LLONG_MAX)
            segTree.upd(0,0,idx-1,mp[nums[i].second],r.mn-nums[i].first+nums[i].second,r.ct);
        if (first[i]){
            segTree.upd(0,0,idx-1,mp[nums[i].second],nums[i].second,1);
        }
        if (last[i]){
            if (r.mn!=LLONG_MAX)
                mns.emplace_back(make_pair(r.mn - nums[i].first + nums[i].second, r.ct));
            else if (first[i])
                mns.emplace_back(make_pair(nums[i].second,1));
        }
    }
    sort(all(mns));
    for (int i = 0; i < mns.size(); i++){
        if (mns[i].first==mns[0].first){
            res = (res + mns[i].second)%MOD;
        }
    }
    cout << res << '\n';
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
