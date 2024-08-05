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
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
void solve(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<int> factors = spf(*max_element(nums.begin(),nums.end()));
    int g = nums[0];
    bool diff = false;
    for (int i = 1; i < n; i++){
        diff|=(nums[i]!=nums[0]);
        g = gcd(g,nums[i]);
    }
    if (!diff){
        cout<<-1<<endl;
        return;
    }
    map<int,int> gcdfactors;
    while (g>1){
        int fc = factors[g];
        g/=fc;
        gcdfactors[fc]++;
    }
    map<int,int> fc;
    for (int i = 0; i < n; i++){
        map<int,int> tempMap;
        while (nums[i]>1){
            int fac = factors[nums[i]];
            nums[i]/=fac;
            tempMap[fac]++;
        }
        for (auto [k,v]: tempMap){
            if (tempMap[k]>gcdfactors[k]){
                fc[k]++;
            }
        }
    }
    int res = n;
    for (auto [k,v]: fc){
        res = min(res,n-v);
    }
    cout<<res<<endl;
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