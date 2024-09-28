#include <bits/stdc++.h>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
string s;
int dp[2000][2000][2];
int dfs(int i, int j, bool left){
    if (dp[i][j][left]!=-1) return dp[i][j][left];
    if (i==j){
        char c = left ? s[i-1]: s[j+1];
        if (s[i] < c){
            return dp[i][j][left] = 1;
        }
        else if (s[i] > c){
            return dp[i][j][left] = 0;
        }
        return dp[i][j][left] = 2;
    }
    int res1 = dfs(i+1,j,true);
    int res2 = dfs(i,j-1,false);
    if (res1==0 || res2==0){
        return dp[i][j][left] = 1;
    }
    else if (res1==1 && res2==1){
        return dp[i][j][left] = 0;
    }
    if ((j-i+1)%2==0){
        return dp[i][j][left] = 2;
    }
    char c = left ? s[i-1]: s[j+1];
    bool hasDraw = false;
    if (res1==2){
        if (s[i] < c) return dp[i][j][left] = 1;
        if (s[i]==c) hasDraw = true;
    }
    if (res2==2){
        if (s[j] < c) return dp[i][j][left] = 1;
        if (s[j]==c) hasDraw = true;
    }
    if (hasDraw){
        return dp[i][j][left] = 2;
    }
    return dp[i][j][left] = 0;
}
void solve(int cas){
    cin>>s;
    for (int i = 0; i < s.size(); i++){
        for (int j = 0; j < s.size(); j++){
            for (int x = 0; x < 2; x++){
                dp[i][j][x] = -1;
            }
        }
    }
    int x = dfs(0,s.size()-1,false);
    if (x==2){
        cout<<"Draw"<<endl;
    }
    else if (x==1){
        cout<<"Alice"<<endl;
    }
    else{
        cout<<"Bob"<<endl;
    }
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}