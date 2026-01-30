#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 1e6 + 5;
int pi[N];
void solve(int cas){  
    string s; cin>>s;
    int n = s.size();
    for (int i = 1, j = 0; i < n; i++){
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    int j = pi[n - 1];
    vector<int> stk;
    while (j > 0){
        stk.emplace_back(j);
        j = pi[j - 1];
    }
    while (!stk.empty()){
        cout << stk.back() << " ";
        stk.pop_back();
    }
    cout << '\n';
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