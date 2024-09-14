//Problem Link: https://codeforces.com/gym/100114/attachments/download/1307/20122013-acmicpc-neerc-central-subregional-contest-en.pdf
#include <bits/stdc++.h>
#include <fstream>
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
const int MAXN = 100005;
bool vis[MAXN];
ll low[MAXN], tin[MAXN], bridges[MAXN], leaf[MAXN];
ll res, tim;
pair<ll,ll> p;
int bct = 0;
void dfs(int node, int parent, vector<vector<int>>& nodeMap){
    low[node] = tin[node] = tim++;
    vis[node] = true;
    int mx1 = -1, mx1i = -1, mx2 = -1, mx2i = -1;
    bool pskip = false;
    for (int neighbor: nodeMap[node]){
        if (neighbor==parent && !pskip){
            pskip = true;
            continue;
        }
        if (vis[neighbor]){
            low[node] = min(tin[neighbor], low[node]);
        }
        else{
            dfs(neighbor,node,nodeMap);
            if (bridges[neighbor]>mx1){
                mx2i = mx1i;
                mx2=mx1;
                mx1 = bridges[neighbor];
                mx1i = leaf[neighbor];
            }
            else if (bridges[neighbor]>mx2){
                mx2 = bridges[neighbor];
                mx2i = leaf[neighbor];
            }
            low[node] = min(low[neighbor],low[node]);
            if (low[neighbor] > low[node]){
                bct++;
            }
        }
    }
    if (mx1i!=-1 && mx2i!=-1 && mx1+mx2 > res){
        res = mx1 + mx2;
        p.first = mx1i;
        p.second = mx2i;
    }
    else if (mx1i!=-1 && mx1 > res){
        res = mx1;
        p.first = node;
        p.second = mx1i;
    }
    if (mx1i!=-1){
        leaf[node] = mx1i;
        bridges[node] = mx1;
    }
    if (low[node]==tin[node] && node!=0){
        bridges[node]++;
        if (leaf[node]==-1){
            leaf[node] = node;
        }
    }
}
void solve2(ifstream& inFile, ofstream& outFile){
    int n,m;
    inFile>>n>>m;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < m; i++){
        int a,b;
        inFile>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    if (n==1){
        outFile<<1<<" "<<0<<endl;
        return;
    }
    memset(vis, false, sizeof vis);
    memset(low, 0, sizeof low);
    memset(tin, 0, sizeof tin);
    memset(bridges, 0, sizeof bridges);
    memset(leaf, -1, sizeof leaf);
    res = -1; tim = 0; p = pair<ll,ll> (0,1);
    dfs(0,-1,nodeMap);
    if (res==-1){
        outFile<<1<<" "<<0<<endl;return;
    }
    outFile<<min(p.first,p.second)+1<<" "<<max(p.first,p.second)+1<<endl;
}
void solve(){
}
int main(){
    int t=1;
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    while (t--){
        //solve();
        solve2(inFile, outFile);
    }
    inFile.close();
    outFile.close();
    return 0;
}