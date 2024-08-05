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
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
struct Node{
    int c1 = 0;
    int c2 = 0;
    int maxLength0 = 1; //Longest non decreasing
    int maxLength1 = 1; //Longest non increasing
    Node(){}
};
struct SegmentTree{
    vector<Node> tree;
    vector<bool> lazy;
    SegmentTree(string s){
        tree.resize(4*s.size());
        lazy.resize(4*s.size());
        build_tree(0,0,s.size()-1,s);
    }
    void mergeNodes(Node& left, Node& right, Node& main){
        main.c1 = left.c1+right.c1;
        main.c2=left.c2+right.c2;
        main.maxLength0 = max(max(left.maxLength0+right.c2,left.c1+right.maxLength0),left.c1+right.c2);
        main.maxLength1=max(left.c2+right.c1,max(left.maxLength1+right.c1,left.c2+right.maxLength1));
    }
    void build_tree(int node, int left, int right, string& s){
        if (left==right){
            if (s[left]=='4'){
                tree[node].c1++;
            }
            else{
                tree[node].c2++;
            }
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid,s);
        build_tree(2*node+2,mid+1,right,s);
        mergeNodes(tree[2*node+1],tree[2*node+2],tree[node]);
    }
    void update(int node, int left, int right, int arrLeft, int arrRight){
        if (lazy[node]){
            swap(tree[node].c1,tree[node].c2);
            swap(tree[node].maxLength0,tree[node].maxLength1);
            if (arrLeft!=arrRight){
                lazy[2*node+1]=!lazy[2*node+1];
                lazy[2*node+2]=!lazy[2*node+2];
            }
            lazy[node]=false;
        }
        if (arrLeft>right || arrRight<left) return;
        if (arrLeft>=left && arrRight<=right){
            swap(tree[node].c1,tree[node].c2);
            swap(tree[node].maxLength0,tree[node].maxLength1);
            if (arrLeft!=arrRight){
                lazy[2*node+1]=!lazy[2*node+1];
                lazy[2*node+2]=!lazy[2*node+2];
            }
            return;
        }
        int mid = (arrLeft+arrRight)>>1;
        update(2*node+1,left,right,arrLeft,mid);
        update(2*node+2,left,right,mid+1,arrRight);
        mergeNodes(tree[2*node+1],tree[2*node+2],tree[node]);
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    string s; cin>>s;
    SegmentTree segTree(s);
    while (m--){
        string x; cin>>x;
        if (x=="count"){
            cout<<segTree.tree[0].maxLength0<<endl;
        }
        else{
            int l,r;
            cin>>l>>r;
            --l; --r;
            segTree.update(0,l,r,0,n-1);
        }
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