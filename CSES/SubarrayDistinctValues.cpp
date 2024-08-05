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
    int n,k;
    cin>>n>>k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++){
        cin>>nums[i];
    }
    unordered_map<int,int> lastMap;
    int count = 0;
    int lp = 0;
    ll res = 0;
    for (int i = 0; i < n; i++){
        if (lastMap.find(nums[i])==lastMap.end() || lastMap[nums[i]]<lp){
            count++;
        }
        lastMap[nums[i]]=i;
        while (count > k){
            if (lastMap[nums[lp]]==lp){
                count--;
            }
            lp++;
        }
        res+=i-lp+1;
    }
    cout<<res<<endl;
}
