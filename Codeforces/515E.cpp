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
    ll maxSum = 0;
    ll left = 0;
    ll right = 0;
    ll dist = 0;
    ll totalDistance = 0;
    bool isNull = false;
    Node(){}
};
struct SegmentTree{
    vector<int> heights;
    vector<int> distances;
    vector<Node> tree;
    SegmentTree(vector<int> h, vector<int> d){
        heights = h;
        distances = d;
        tree.resize(4*h.size());
        build_tree(0,0,h.size()-1);
    }
    void mergeNodes(Node& leftNode, Node& rightNode, Node& mainNode){
        mainNode.maxSum = max(leftNode.maxSum, rightNode.maxSum);
        mainNode.maxSum = max(mainNode.maxSum,leftNode.right+leftNode.dist+rightNode.left);
        mainNode.dist = rightNode.dist;
        mainNode.totalDistance = leftNode.totalDistance+rightNode.totalDistance+leftNode.dist;
        mainNode.left = max(rightNode.left+leftNode.dist+leftNode.totalDistance,leftNode.left);
        mainNode.right = max(leftNode.right+leftNode.dist+rightNode.totalDistance,rightNode.right);
    }
    void build_tree(int node, int left, int right){
        if (left==right){
            tree[node].maxSum = 2*heights[left];
            tree[node].dist = distances[left];
            tree[node].left = 2*heights[left];
            tree[node].right = 2*heights[left];
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid);
        build_tree(2*node+2,mid+1,right);
        mergeNodes(tree[2*node+1],tree[2*node+2],tree[node]);
    }
    Node query(int node, int left, int right, int arrLeft, int arrRight){
        if (arrLeft>right|| arrRight<left){
            Node m;
            m.isNull = true;
            return m;
        }
        if (arrLeft>=left && arrRight<=right){
            return tree[node];
        }
        int mid = (arrLeft+arrRight)>>1;
        Node l = query(2*node+1,left,right,arrLeft,mid);
        Node r = query(2*node+2,left,right,mid+1,arrRight);
        if (l.isNull) return r;
        if (r.isNull) return l;
        Node m;
        mergeNodes(l,r,m);
        return m;
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> distances(n);
    for (int i = 0; i < n; i++) cin>>distances[i];
    vector<int> heights(n);
    for (int i = 0; i < n; i++) cin>>heights[i];
    SegmentTree segTree(heights,distances);
    while (m--){
        int a,b;
        cin>>a>>b;
        --a;--b;
        if (a<=b){
            Node l = segTree.query(0,b+1,n-1,0,n-1);
            Node r = segTree.query(0,0,a-1,0,n-1);
            if (r.isNull){
                cout<<l.maxSum<<endl;
                continue;
            }
            else if (l.isNull){
                cout<<r.maxSum<<endl;
                continue;
            }
            Node m;
            segTree.mergeNodes(l,r,m);
            cout<<m.maxSum<<endl;
        }
        else{
            Node res = segTree.query(0,b+1,a-1,0,n-1);
            cout<<res.maxSum<<endl;
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