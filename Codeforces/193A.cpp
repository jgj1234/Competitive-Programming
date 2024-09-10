#include <bits/stdc++.h>
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
int n,m;
const int MAXN = 51;
bool vis[MAXN][MAXN];
ll low[MAXN][MAXN], tin[MAXN][MAXN];
vector<pii> dirs  = {pii(1,0),pii(-1,0),pii(0,1),pii(0,-1)};
int tim;
bool dfs(int i, int j, int px, int py, vector<string>& grid){
    low[i][j] = tin[i][j] = tim++;
    vis[i][j] = true;
    int child = 0;
    bool got = false;
    for (const auto& [dx, dy]: dirs){
        if (i+dx==px && j+dy==py) continue;
        if (i+dx<n && i+dx>=0 && j+dy<m && j+dy>=0 && grid[i+dx][j+dy]=='#'){
            if (vis[i+dx][j+dy]){
                low[i][j] = min(low[i][j], low[i+dx][j+dy]);
            }
            else{
                child++;
                if (dfs(i+dx,j+dy,i,j,grid)){
                    return true;
                }
                if (low[i+dx][j+dy] >= tin[i][j] && px!=-1){
                    return true;
                }
                low[i][j] = min(low[i][j],low[i+dx][j+dy]);
            }
        }
    }
    return px==-1 and child>1;
};
void solve(){
    cin>>n>>m;
    tim = 0;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin>>grid[i];
    int ct = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (grid[i][j]=='#') ct++;
        }
    }
    if (ct<=2){
        cout<<-1<<endl;
        return;
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (grid[i][j]=='#'){
                if (dfs(i,j,-1,-1,grid)){
                    cout<<1<<endl;
                }
                else{
                    cout<<2<<endl;
                }
                return;
            }
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