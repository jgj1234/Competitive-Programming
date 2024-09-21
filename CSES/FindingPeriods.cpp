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
struct PolyHash{
    vector<int64_t> pref;
    int n;
	
    PolyHash(string& ar){
        if (!base_pow[0]) init();
 
        n = ar.size();
        assert(n < MAXLEN);
        pref.resize(n + 1, 0);
 
        for (int i = 1; i <= n; i++){
            pref[i] = modmul(pref[i - 1], base) + ar[i - 1] + 997;
            while (pref[i] >= mod) pref[i] -= mod;
        }
    }
 
    uint64_t get_hash(int l, int r){
        int64_t h = pref[r + 1] - modmul(base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + mod : h;
    }
    
    void extend(char c){
		pref.push_back(nxt_hash(pref.back(), c));
		n++;
	}
};
void solve(int cas){
    string s;cin>>s;
    PolyHash h1 (s);
    for (int i = 0; i < s.size(); i++){
        int length = i + 1;
        uint64_t val = h1.get_hash(0,i);
        for (int j = 0; j + length - 1 < s.size(); j += length){
            uint64_t v = h1.get_hash(j, j+length-1);
            if (v!=val){
                break;
            }
            int nxt = j + length;
            if (nxt < s.size() && nxt + length - 1 >= s.size()){
                int rem = s.size() - nxt;
                uint64_t pref = h1.get_hash(0,rem - 1);
                uint64_t suff = h1.get_hash(nxt, s.size()-1);
                if (pref==suff){
                    cout<<length<<" ";
                }
            }
            else if (nxt + length - 1 >=s.size()){
                cout<<length<<" ";
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
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}