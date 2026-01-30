#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct Node{
    int depth = 0;
    vector<Node*> children;
    priority_queue<ll> heap;
    int ct = 0;
    Node(){
        children.resize(26, nullptr);
    }
};
struct Trie{
    Node* root;
    Trie(){
        root = new Node();
    }
    void insert(string& word){
        Node* curr = root;
        for (int i = 0; i < word.size(); i++){
            if (!curr->children[word[i]-'a']){
                curr->children[word[i]-'a'] = new Node();
                curr->children[word[i]-'a']->depth = curr->depth + 1;
            }
            curr = curr->children[word[i]-'a'];
        }
        curr->ct++;
    }
};
void solve(int cas){ 
    int n; cin>>n;
    vector<string> st(n);
    for (auto& a: st) cin>>a;
    Trie trie;
    for (int i = 0; i < n; i++) trie.insert(st[i]);
    ll res = 0;
    auto dfs =[&] (auto&& self, Node* curr) -> void{
        for (int i = 0; i < 26; i++){
            if (curr->children[i]!=nullptr){
                self(self,curr->children[i]);
                if (curr->children[i]->heap.size() > curr->heap.size()) swap(curr->children[i]->heap, curr->heap);
                while (!curr->children[i]->heap.empty()){
                    curr->heap.push(curr->children[i]->heap.top());
                    curr->children[i]->heap.pop();
                }
            }
        }
        if (!curr->ct && !curr->heap.empty() && curr->depth > 0){
            res -= curr->heap.top();
            curr->heap.pop();
            res += curr->depth;
        }
        else if (curr->ct){
            res += curr->depth;
        }
        curr->heap.push(curr->depth);
    };
    dfs(dfs,trie.root);
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