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
#define ppii pair<int, pair<int,int>>
#define ll long long
#define MOD (int)1e9+7
using namespace std;
 
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<char>> grid(n,vector<char>(m));
    queue<ppii> monsterQ;
    int startX,startY;
    vector<vector<int>> monsters(n,vector<int> (m,-1));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin>>grid[i][j];
            if (grid[i][j]=='A'){
                startX=i;
                startY=j;
            }
            else if (grid[i][j]=='M'){
                monsterQ.push({0,{i,j}});
                monsters[i][j]=0;
            }
        }
    }
    vector<pii> directions = {{0,1},{1,0},{0,-1},{-1,0}};
    while (!monsterQ.empty()){
        ppii curr = monsterQ.front();
        monsterQ.pop();
        for (const auto& dir: directions){
            int newR=curr.second.first+dir.first;
            int newC=curr.second.second+dir.second;
            if (newR<0 || newR>=n || newC<0 ||newC>=m || monsters[newR][newC]!=-1 || grid[newR][newC]=='#'){
                continue;
            }
            monsters[newR][newC] = curr.first+1;
            monsterQ.push({curr.first+1,{newR,newC}});
        }
    }
    vector<vector<char>> dp(n,vector<char>(m,'X'));
    dp[startX][startY]='-';
    queue<ppii> q;
    q.push({0,{startX,startY}});
    int endX,endY;
    bool ans = false;
    while (!q.empty()){
        ppii curr = q.front();
        q.pop();
        if (curr.second.first==0 || curr.second.first==n-1 || curr.second.second==0 || curr.second.second==m-1){
            endX=curr.second.first;
            endY=curr.second.second;
            ans=true;
            break;
        }
        for (const auto& dir: directions){
            int newR = curr.second.first+dir.first;
            int newC = curr.second.second+dir.second;
            if (newR<0 || newR>=n || newC<0 || newC>=m || dp[newR][newC]!='X' || grid[newR][newC]=='M' || grid[newR][newC]=='#'||(curr.first+1>=monsters[newR][newC] && monsters[newR][newC]!=-1)){
                continue;
            }
            if (dir.first==1 && dir.second==0){
                dp[newR][newC]='D';
            }
            else if (dir.first==-1 && dir.second==0){
                dp[newR][newC]='U';
            }
            else if (dir.first==0 && dir.second==1){
                dp[newR][newC]='R';
            }
            else{
                dp[newR][newC]='L';
            }
            q.push({curr.first+1,{newR,newC}});
        }
    }
    if (!ans){
        cout<<"NO";
    }
    else{
        cout<<"YES"<<endl;
        vector<char> path;
        while (endX!=startX || endY!=startY){
            path.push_back(dp[endX][endY]);
            if (dp[endX][endY]=='D'){
                endX--;
            }
            else if (dp[endX][endY]=='U'){
                endX++;
            }
            else if (dp[endX][endY]=='R'){
                endY--;
            }
            else{
                endY++;
            }
        }
        cout<<path.size()<<endl;
        for (int i = path.size()-1;i>=0;i--){
            cout<<path[i];
        }
    }
      
}
