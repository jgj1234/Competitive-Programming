#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#define ll long long
#define pii pair<int,int>
#define piii tuple<int,int,int>
using namespace std;
const int N=400001;
vector<vector<int>> adj(N);
vector<int> degree(N);
vector<int> t(N);
int main(){
   int num_tests;
   cin>>num_tests;
   while(num_tests--){
        int n,k;
        cin>>n>>k;
        for(int i = 0; i<=n;i++){
            adj[i].clear();
            degree[i]=0;
            t[i]=0;
        }
        for (int i = 0; i<n-1;i++){
            int u,v;
            cin>>u>>v;
            adj[u-1].push_back(v-1);
            adj[v-1].push_back(u-1);
            degree[u-1]++;
            degree[v-1]++;
        }
        queue<int> q;
        for(int i = 0; i<n;i++){
            if (degree[i]<=1){
                q.push(i);
                t[i]=1;
            }
        }
        int count=n;
        while (!q.empty()){
            int node=q.front();q.pop();
            if(t[node]>k){
                break;
            }
            count--;
            for (int neighbor : adj[node]){
                degree[neighbor]--;
                if(degree[neighbor]==1 && t[neighbor]==0){
                    q.push(neighbor);
                    t[neighbor]=t[node]+1;
                }
            }
        }
        cout<<count<<endl;
   }
}