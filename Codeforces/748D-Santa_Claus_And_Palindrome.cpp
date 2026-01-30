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
constexpr uint64_t mod = (1ULL << 61) - 1;
const int MAXLEN = 1e6 + 5;
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (mod / 3) + (mod / 3);
 
uint64_t base_pow[MAXLEN];
 
int64_t modmul(uint64_t a, uint64_t b){
    uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret - 1;
}
 
void init(){
    base_pow[0] = 1;
    for (int i = 1; i < MAXLEN; i++){
        base_pow[i] = modmul(base_pow[i - 1], base);
    }
}
 
uint64_t nxt_hash(uint64_t cur, char c){
	return (modmul(cur, base) + c + 997) % mod;
}
uint64_t total_hash(string& s){
	uint64_t cur = 0;
	for(int i = 0; i < s.length(); i++) cur = nxt_hash(cur, s[i]);
	return cur;
}
void solve(){
    ll k,n;
    cin>>k>>n;
    vector<string> s(k);
    vector<ll> beauty(k);
    for (int i = 0; i < k; i++) cin>>s[i]>>beauty[i];
    map<uint64_t,vector<ll>> original;
    map<uint64_t,uint64_t> mp;
    ll res = 0;
    for (int i = 0; i < k; i++){
        uint64_t og = total_hash(s[i]);
        reverse(all(s[i]));
        uint64_t rev = total_hash(s[i]);
        original[og].emplace_back(beauty[i]);
        mp[og] = rev;
    }
    for (auto& [k,v]: original){
        sort(all(v), greater<ll>());
    }
    ll odd = 0;
    set<uint64_t> vis;
    for (auto& [k,v]:original){
        if (mp[k]==k){
            for (int i = 0; i <v.size() - 1; i+=2){
                if (v[i]<0) break;
                if (v[i]+v[i+1]<0){
                    odd = max(odd, v[i]);
                    break;
                }
                if (v[i+1]>0){
                    res+=v[i]+v[i+1];
                }
                else{
                    res+=v[i]+v[i+1];
                    odd = max(odd, -1*v[i+1]);
                    break;
                }
            }
            if (v.back()>0 && v.size()%2==1){
                odd = max(odd, v.back());
            }
        }
        else{
            if (!original.count(mp[k]) || vis.count(k)) continue;
            vis.insert(mp[k]);
            for (int i = 0; i < v.size(); i++){
                if (i>=original[mp[k]].size() || v[i]+original[mp[k]][i]<0) break;
                res+=v[i]+original[mp[k]][i];
            }
        }
    }
    cout<<res+odd<<endl;
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
    return 0;
}