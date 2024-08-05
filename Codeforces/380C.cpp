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
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
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
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
struct Node{
    int left = 0;
    int right = 0;
    int maxSeq = 0;
    bool isNull = false;
    Node(){}
};
struct SegmentTree{
    vector<Node> tree;
    SegmentTree(string s){
        tree.resize(4*s.size());
        build_tree(0,0,s.size()-1,s);
    }
    void mergeNodes(Node& l, Node& r, Node& main){
        main.left= l.left+r.left; main.right = l.right+r.right;
        main.maxSeq = l.maxSeq+r.maxSeq+(min((l.left-l.maxSeq/2),(r.right-r.maxSeq/2))*2);
    }
    void build_tree(int node, int left, int right, string& s){
        if (left==right){
            if (s[left]==')'){
                tree[node].right++;
            }
            else{
                tree[node].left++;
            }
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid,s);
        build_tree(2*node+2,mid+1,right,s);
        mergeNodes(tree[2*node+1],tree[2*node+2],tree[node]);
    }
    Node query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right || arrRight<left){
            Node n; n.isNull = true;
            return n;
        }
        if (arrLeft>=left && arrRight<=right) return tree[node];
        int mid = (arrLeft+arrRight)>>1;
        Node l = query(2*node+1,left,right,arrLeft,mid);
        Node r = query(2*node+2,left,right,mid+1,arrRight);
        if (l.isNull) return r;
        if (r.isNull) return l;
        Node m = Node();
        mergeNodes(l,r,m);
        return m;
    }
};
void solve(){
    string s; int m;
    cin>>s>>m;
    SegmentTree segTree(s);
    while (m--){
        int l,r;
        cin>>l>>r;
        --l;--r;
        Node res = segTree.query(0,l,r,0,s.size()-1);
        cout<<res.maxSeq<<endl;
    }
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   //cin>>t;
   while (t--){
      solve();
   }
}