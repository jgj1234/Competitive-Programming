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
void solve(){
    int n,k;
    cin>>n>>k;
    vector<unordered_set<int>> nodeMap(n);
    vector<bool> ct(n);
    for (int i = 0; i < k; i++){
        vector<int> arr(n);
        for (int j = 0; j < n; j++){
            cin>>arr[j];
        }
        for (int i = 1; i < arr.size() - 1; i++){
            nodeMap[arr[i]-1].insert(arr[i+1]-1);
            ct[arr[i+1]-1]=true;
        }
    }
    int count = 0;
    int start = -1;
    for (int i = 0; i < n; i++){
        if (ct[i]==0){
            count++;
            start = i;
        }
    }
    if (count==0){
        cout<<"NO"<<endl;
        return;
    }
    vector<int> indegree (n);
    auto dfs = [&] (auto self, int node)->bool{
        indegree[node]=1;
        for (int neighbor: nodeMap[node]){
            if (indegree[neighbor]==1){
                return false;
            }
            if (indegree[neighbor]==2) continue;
            if (!self(self,neighbor)){
                return false;
            }
        }
        indegree[node]=2;
        return true;
    };
    cout<<(dfs(dfs,start)?"YES":"NO")<<endl;
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   cin>>t;
   while (t--){
      solve();
   }
}