#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
void solve(int cas){  
    int n; cin>>n;
    map<string, vector<char>> g;
    for (int i = 0; i < n; i++){
        string s; cin>>s;
        g[s.substr(0, 2)].emplace_back(s[2]);
        if (!g.count(s.substr(1, 1) + s[2])){
            g[s.substr(1, 1) + s[2]] = vector<char>{};
        }
    }
    map<string, int> indeg;
    for (auto& [k, v]: g){
        for (char c: v){
            indeg[k.substr(1, 1) + c]++;
        }
    }
    string o1 = "", i1 = "";
    for (auto& [s, v]: g){
        if (abs(indeg[s] - (int) g[s].size()) > 1){
            cout << "NO\n";
            return;
        }
        if (indeg[s] > g[s].size()){
            if (i1 != ""){
                cout << "NO\n";
                return;
            }
            i1 = s;
        }
        if (indeg[s] < g[s].size()){
            if (o1 != ""){
                cout << "NO\n";
                return;
            }
            o1 = s;
        }
    }
    string start;
    if (o1 == "" && i1 == ""){
        start = (g.begin())->first;
    }
    else if (o1 != "" && i1 != ""){
        start = o1;
    }
    else{
        cout << "NO\n";
        return;
    }
    vector<pair<string, char>> stk= {make_pair(start, '-')};
    string res;
    while (!stk.empty()){
        auto [node, parEdge] = stk.back();
        if (g[node].empty()){
            if (parEdge != '-') res.push_back(parEdge);
            stk.pop_back();
        }
        else{
            stk.emplace_back(make_pair(node.substr(1, 1) + g[node].back(), g[node].back()));
            g[node].pop_back();
        }
    }
    reverse(all(res));
    res = start + res;
    if ((int)res.size() != n + 2){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
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