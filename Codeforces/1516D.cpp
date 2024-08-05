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
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
vector<int> sieve(int n){
   vector<bool> isPrime(n+1,true);
   isPrime[0]=isPrime[1]=false;
   for (int i = 2; i <= (int)sqrt(n); i++){
      for (int j = 2; j <=n; j++){
         if (i*j>n) break;
         isPrime[i*j]=false;
      }
   }
   vector<int> primes;
   for (int i = 2; i < isPrime.size(); i++){
      if (isPrime[i]) primes.emplace_back(i);
   }
   return primes;
}
vector<int> spf(int n){
   vector<int> res (n+1,0);
   vector<int> primes = sieve(n);
   for (int prime: primes){
      for (int i = prime; i < n + 1; i+=prime){
         if (res[i]==0){
            res[i]=prime;
         }
      }
   }
   return res;
}
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<int> nf (100001,n);
    vector<int> facs = spf(100001);
    vector<int> nxt(n);
    for (int i =  n - 1; i>=0; i--){
        int x = nums[i];
        int fw = n;
        while (x>1){
            if (nf[facs[x]]!=i){
                fw = min(fw,nf[facs[x]]);
            }
            nf[facs[x]] = i;
            x/=facs[x];
        }
        nxt[i] = fw;
        if (i+1<n) nxt[i] = min(nxt[i],nxt[i+1]);
    }
    int lg = 32 - __builtin_clz(n);
    vector<vector<int>> jump(n+1,vector<int> (lg));
    for (int i = 0; i < n; i++){
        jump[i][0] =  nxt[i];
    }
    for (int i = 0; i < lg; i++){
        jump[n][i] = n;
    }
    for (int j = 1; j < lg; j++){
        for (int i = 0; i < n; i++){
            jump[i][j] = jump[jump[i][j-1]][j-1];
        }
    }
    while (q--){
        int l,r;
        cin>>l>>r;
        --l;--r;
        ll res = 0;
        for (int i = lg - 1; i>=0; i--){
            if (jump[l][i]<=r){
                res+=(1<<i);
                l = jump[l][i];
            }
        }
        cout<<res+1<<endl;
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