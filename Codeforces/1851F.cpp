#include <iostream>
#include <vector>
#include <string>
#include <cstring>
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
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
struct TrieNode{
    int index = -1;
    bool bt;
    vector<TrieNode*> children;
    TrieNode() : bt(false), children(2, nullptr) {}
};
struct Trie{
    TrieNode* root;
    Trie(){root = new TrieNode();}
    void insert(int num, int index, int k){
        TrieNode* curr = root;
        for (int bit = k - 1; bit>=0; bit--){
            bool btx = num&(1<<bit);
            if (curr->children[btx]==nullptr){
                curr->children[btx] = new TrieNode();
                curr->children[btx]->bt = btx;
            }
            curr = curr->children[btx];
        }
        curr->index = index;
    }
    pair<ll,ll> dfs(int num, int bit, int x, TrieNode* curr){
        if (curr -> index != -1){
            return pair<ll,ll> (0, curr->index);
        }
        if ((num&(1<<bit))==0){
            pair<ll,ll> res;
            if (curr->children[0]!=nullptr){
                res = dfs(num, bit - 1, x, curr->children[0]);
            }
            if (curr -> children[0]!=nullptr){
                pair<ll,ll> d1 = dfs(num,bit-1,x,curr->children[1]);
                if (d1.first>res.first) res = d1;
            }
            return res;
        }
        bool btx = bool(x&(1<<bit))^1;
        if (curr->children[btx]!=nullptr){
            pair<ll,ll> d1 = dfs(num,bit-1,x,curr->children[btx]);
            d1.first+=(1<<bit);
            return d1;
        }
        return dfs(num,bit-1,x,curr->children[!btx]);
    }
};
void solve(){
    int n,k;
    cin>>n>>k;
    vector<int> nums(n);
    ll res = 0;
    vector<int> info(3);
    for (int i = 0; i < n; i++) cin>>nums[i];
    Trie trie;
    trie.insert(nums[n-1],n-1,k);
    for (int i = n - 2; i>=0; i--){
        int x = ((1<<k)-1)^nums[i];
        pair<ll,ll> f = trie.dfs(nums[i]^x,k-1,x,trie.root);
        if (f.first>=res){
            info[0] = i;
            info[1] = f.second;
            info[2]=x;
            res = f.first;
        }
        trie.insert(nums[i],i,k);
    }
    cout<<info[0]+1<<" "<<info[1]+1<<" "<<info[2]<<endl;
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   cin>>t;
   while (t--){
      solve();
   }
}