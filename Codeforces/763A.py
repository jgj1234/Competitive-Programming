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
vector<pii> edges;
vector<int> colors;
vector<vector<int>> nodeMap;
bool dfs(int index, int node, int parent, int color){
    if (node == index){
        for (int neighbor: nodeMap[node]){
            if (!dfs(index,neighbor,node,colors[neighbor])){
                return false;
            }
        }
        return true;
    }
    for (int neighbor: nodeMap[node]){
        if (neighbor==parent) continue;
        if (colors[neighbor]!=color || !dfs(index,neighbor,node,color)){
            return false;
        }
    }
    return true;
}   
int main(){
   int n;
   cin>>n;
   nodeMap.resize(n);
   colors.resize(n);
   for (int i = 0; i < n - 1; i++){
        int u,v;
        cin>>u>>v;
        nodeMap[u-1].emplace_back(v-1);
        nodeMap[v-1].emplace_back(u-1);
   }
   for (int i = 0; i < n; i++) cin>>colors[i];
   int index = -1;
   int maxCount = 0;
   for (int i = 0; i < n; i++){
       int currCount = 0;
       for (int j = 0; j < nodeMap[i].size(); j++){
           if (colors[nodeMap[i][j]]!=colors[i]){
               currCount++;
           }
       }
       if (currCount > maxCount){
           maxCount = currCount;
           index = i;
       }
   }
   if (index == -1){
        cout<<yes<<endl;
        cout<<1;
   }
   else{
    if(dfs(index,index,-1,-1)){
        cout<<yes<<endl;
        cout<<index+1;
    }
    else{
        cout<<no<<endl;
    }
   }
}