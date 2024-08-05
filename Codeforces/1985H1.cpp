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
struct UnionFind{
    vector<int> par;
    vector<int> sz;
    vector<int> rank;
    UnionFind(vector<vector<char>>& board){
        int x = board.size()*board[0].size();
        par.resize(x,-1);sz.resize(x);
        rank.resize(x);
        for (int i = 0; i < board.size(); i++){
            for (int j = 0; j < board[0].size(); j++){
                if (board[i][j]=='#'){
                    int key = i*board[0].size()+j;
                    par[key]=key; sz[key]=1;
                    if (i>0 && board[i-1][j]=='#'){
                        int nKey = (i-1)*board[0].size()+j;
                        unionn(find(key),find(nKey));
                    }
                    if (j>0 && board[i][j-1]=='#'){
                        int nKey = i*(board[0].size())+j-1;
                        unionn(find(key),find(nKey));
                    }
                }
            }
        }
    }
    int find(int u){
        if (par[u]==u){
            return u;
        }
        return par[u]=find(par[u]);
    }
    void unionn(int u, int v){
        if (u==v) return;
        if (rank[u]==rank[v]) rank[u]++;
        if (rank[u]>rank[v]){
            par[v]=u;
            sz[u]+=sz[v];
        }
        else{
            par[u]=v;
            sz[v]+=sz[u];
        }
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<char>> board (n,vector<char> (m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) cin>>board[i][j];
    }
    UnionFind uf(board);
    //Columns
    int res = 0;
    for (int j = 0; j < board[0].size(); j++){
        int ct = 0;
        int temp = 0;
        bool found = false;
        set<int> keys;
        for (int i = 0; i < board.size(); i++){
            if (board[i][j]=='#') temp++;
            if (board[i][j]=='.'){
                if (found){
                    ct+=temp;
                }
                found=false;
                temp=0;
            }
            if (j>0 && board[i][j-1]=='#'){
                keys.insert(uf.find(i*board[0].size()+j-1));
                if (temp) found = true;
            }
            if (j+1<board[0].size() && board[i][j+1]=='#'){
                keys.insert(uf.find(i*board[0].size()+j+1));
                if (temp) found = true;
            }
        }
        if (found && temp) ct+=temp;
        int r = 0;
        for (int key: keys){
            r+=uf.sz[key];
        }
        res=max(res,r+n-ct);
    }
    for (int i = 0; i < board.size(); i++){
        int ct = 0;
        set<int> keys;
        int temp = 0;
        bool found = false;
        for (int j = 0; j <board[0].size(); j++){
            if (board[i][j]=='#') temp++;
            if (board[i][j]=='.'){
                if (found){
                    ct+=temp;
                }
                found=false;
                temp=0;
            }
            if (i>0 && board[i-1][j]=='#'){
                keys.insert(uf.find((i-1)*board[0].size()+j));
                if (temp) found = true;
            }
            if (i+1<board.size() && board[i+1][j]=='#'){
                keys.insert(uf.find((i+1)*board[0].size()+j));
                if (temp) found = true;
            }
        }
        if (found && temp) ct+=temp;
        int r = 0;
        for (int key: keys){
            r+=uf.sz[key];
        }
        res=max(res,r+m-ct);
    }
    cout<<res<<endl;
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