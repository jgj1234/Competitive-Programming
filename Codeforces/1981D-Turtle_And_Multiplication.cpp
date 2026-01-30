#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int MAX_PRIME = 100000;
bool pr[MAX_PRIME];
vector<int> primes;
void solve(int cas){  
    int n; cin >> n;
    if (n == 2){
        cout << 1 << " " << 1 << '\n';
        return;
    }
    int lp = 2, rp = min(n, 5000);
    while (lp <= rp){
        int mid = (lp + rp) / 2;
        int ct = mid * (mid - 1) / 2 + mid;
        if (mid % 2 == 0){
            ct -= mid / 2 - 1;
        }
        if (ct >= n - 1){
            rp = mid - 1;
        }
        else{
            lp = mid + 1;
        }
    }
    int sz = lp;
    vector<set<int>> g(sz);
    for (int i = 0; i < sz; i++){
        for (int j = 0; j < sz; j++){
            if (i != (j ^ 1) || (sz % 2 == 1 || min(i, j) == 0)){
                g[i].insert(j);
            }
        }
    }
    vector<int> stk = {0};
    vector<int> res;
    while (!stk.empty() && (int) res.size() < n){
        int node = stk.back();
        if (g[node].empty()){
            res.emplace_back(node);
            stk.pop_back();
        }
        else{
            int nxt = *g[node].begin();
            stk.emplace_back(nxt);
            g[node].erase(nxt);
            if (nxt != node)
                g[nxt].erase(node);
        }
    }
    for (int i = 0; i < n; i++) cout << primes[res[i]] << " ";
    cout << '\n';
}
void pre(){
    memset(pr, 1, sizeof(pr));
    pr[0] = pr[1] = 0;
    for (ll i = 2; i < MAX_PRIME; i++){
        if (pr[i]){
            primes.emplace_back(i);
            for (ll j = i * i; j < MAX_PRIME; j += i){
                pr[j] = 0;
            }
        }
    }
}   
int main(){
    pre();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}