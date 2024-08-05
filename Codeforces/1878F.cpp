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
vector<int> factors;
void solve(){
    ll n,q;
    cin>>n>>q;
    ll nd = 0;
    int od = 0;
    ll temp = n;
    map<int,int> facs;
    map<int,int> og;
    while (temp>1){
        int f =  factors[temp];
        facs[f]++;
        og[f]++;
        temp/=f;
        nd++;
    }
    od = nd;
    while (q--){
        ll k;
        cin>>k;
        if (k==1){
            ll x;
            cin>>x;
            while (x>1){
                ll f = factors[x];
                x/=f;
                facs[f]++;
                nd++;
            }
            ll curr = 1;
            for (auto [k,v]: facs){
                curr*=(v+1);
            }
            map<int,int> ct;
            while (curr%2==0){
                curr/=2;
                ct[2]++;
            }
            for (int i = 3; i <= sqrt(curr); i+=2){
                while (curr%i==0){
                    curr/=i;
                    ct[i]++;
                }
            }
            if (curr>2) ct[curr]++;
            bool good = true;
            for (auto [k,v]:ct){
                if (v>facs[k]){
                    good=false;
                    break;
                }
            }
            if (good){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
            
        }
        else{
            
            nd = od;
            map<int,int> temp;
            for (auto [k,v]: og){
                temp[k]=v;
            }
            facs=temp;
        }
    }
    cout<<endl;
}
int main(){
    factors = spf(1000001);
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   cin>>t;
   while (t--){
      solve();
   }
}