#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pli pair<long long,int>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
using namespace std;
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
   for (int i = 2; i < size(isPrime); i++){
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
   int n;
   cin>>n;
   vector<int> nums (n);
   int maxEle = 0;
   for (int i = 0; i < n; i++){
       cin>>nums[i];
       maxEle=max(maxEle,nums[i]);
   }
   if (n==1){
       cout<<nums[0]<<endl;
       return;
   }
   vector<int> factors = spf(maxEle);
   unordered_map<int,pii> factorMap;
   vector<int> ct(maxEle+1);
   for (int i = 0; i < nums.size(); i++){
      int temp = nums[i];
      unordered_map<int,int> factorCount;
      while (temp > 1){
         int factor = factors[temp];
         factorCount[factor]++;
         temp/=factor;
      }
      for (auto[factor,key]: factorCount){
          ct[factor]++;
         if (factorMap.find(factor)==factorMap.end()){
             factorMap[factor]=pii(INT_MAX,INT_MAX);
         }
         if (key <= factorMap[factor].first){
             factorMap[factor].second=factorMap[factor].first;
             factorMap[factor].first=key;
         }
         else if(key<=factorMap[factor].second){
             factorMap[factor].second=key;
         }
      }
   }
   ll res = 1;
   for (auto[factor,k]: factorMap){
      if (ct[factor] < n - 1) continue;
      if (ct[factor]==n){
         res*=pow(factor,k.second);
      }
      else{
         res*=pow(factor,k.first);
      }
   }
   //ll ans = (ll) res;
   cout<<res<<endl;
}
int main(){
   int t=1;
   //cin>>t;
   while (t--){
      solve();
   }
}