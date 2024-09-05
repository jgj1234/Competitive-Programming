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
const int MAX_N = 200005;
const int states = 3;
ll dp[MAX_N][states];
void solve(){
    int n;
    cin>>n;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < states; j++){
            dp[i][j]=INT_MAX;
        }
    }
    for (int i = 0; i < n - 1; i++){
        int a;
        cin>>a;
        nodeMap[i+1].emplace_back(a-1);
        nodeMap[a-1].emplace_back(i+1);
    }
    unordered_map<char,int> mp;
    mp['C'] = 0;
    mp['P'] = 1;
    mp['S'] = 2;
    string s; cin>>s;
    auto dfs = [&] (auto&& self, int node, int parent) -> void{
        bool leaf = true;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                leaf = false;
                self(self,neighbor,node);
            }
        }
        if (leaf){
            dp[node][mp[s[node]]] = 0;
            return;
        }
        if (s[node]=='C'){
            dp[node][0] = 0;
            dp[node][1] = 0;
            dp[node][2] = 0;
        }
        else if (s[node]=='P'){
            dp[node][1] = 0;
        }
        else{
            dp[node][2] = 0;
        }
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                if (s[node]=='C'){
                    dp[node][0] += min(dp[neighbor][0], min(1 + dp[neighbor][1], 1+dp[neighbor][2]));
                    dp[node][1] += min(dp[neighbor][0], min(dp[neighbor][1], 1+dp[neighbor][2]));
                    dp[node][2] += min(dp[neighbor][0], min(1+dp[neighbor][1], dp[neighbor][2]));
                }
                else if (s[node]=='P'){
                    dp[node][1] += min(dp[neighbor][0], min(dp[neighbor][1],1+dp[neighbor][2]));
                }
                else{
                    dp[node][2]+=min(dp[neighbor][0], min(dp[neighbor][1]+1,dp[neighbor][2]));
                }
            }
        }
    };
    dfs(dfs,0,0);
    cout<<min({dp[0][0],dp[0][1],dp[0][2]})<<endl;
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