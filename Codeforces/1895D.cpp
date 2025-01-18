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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
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
    int dfs(int num, int bit, TrieNode* curr){
        if (bit < 0) return 0;
        bool b = num&(1<<bit);
        if (curr->children[1-b]!=nullptr){
            int r = (1<<bit)|dfs(num, bit - 1, curr->children[1-b]);
            return r;
        }
        return dfs(num, bit - 1, curr->children[b]);
    }
};
void solve(int cas){
    int n; cin>>n;
    vector<ll> nums(n-1);
    for (auto& a: nums) cin>>a;
    int lg = 32 - __builtin_clz(n);
    Trie trie;
    int curr = 0;
    trie.insert(0,0,lg);
    for (int i = 0; i < n-1; i++){
        curr^=nums[i];
        trie.insert(curr,0,lg);
    }
    int start = -1;
    for (int i = 0; i < n; i++){
        if (trie.dfs(i,lg-1,trie.root) == n - 1){
            start = i;
            break;
        }
    }
    assert(start!=-1);
    cout << start << ' ';
    for (int i = 0; i < n-1; i++){
        start^=nums[i];
        cout << start << ' ';
    }
    cout << '\n';
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