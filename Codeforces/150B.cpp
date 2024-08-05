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
ll power_modulo(ll a, ll b) {
    int result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (1LL * result * a) % 1000000007;
        }
        a = (1LL * a * a) % 1000000007;
        b /= 2;
    }
    return result;
}
int main(){
   int n,m,k;
   cin>>n>>m>>k;
   vector<bool> visited (n,false);
   auto dfs=[&](auto self, int index)->void{
      visited[index]=true;
      for (int i = index + 1; i <= min(index+k,n); i++){
         int dist = i - index + 1;
         if ((k-dist)%2==0){
            int l = index - (k-dist)/2;
            int r = i + (k-dist)/2;
            if (l>=0 && r < n && !visited[i]) self(self,i);
         }
      }
      for (int i = index - 1; i >= max(index-k,0); i--){
         int dist = index-i+1;
         if ((k-dist)%2==0){
            int l = i - (k-dist)/2;
            int r = index + (k-dist)/2;
            if (l>=0 && r < n && !visited[i]) self(self,i);
         }
      }
   };
   int count = 0;
   for (int i = 0; i < n; i++){
      if (!visited[i]){
         count++;
         dfs(dfs,i);
      }
   }
   ll res = power_modulo(m,count);
   cout<<res<<endl;
}