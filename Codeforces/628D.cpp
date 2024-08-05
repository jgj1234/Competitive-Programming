#include <cstring>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int digit,multiple;
long long dp[2001][2][2000];
long long mod=1000000007;
long long digit_dp(string& str,int index, bool tight, int remainder){
    if(index==str.size()){

        return !remainder;
    }
    if(dp[index][tight][remainder]!=-1){
        return dp[index][tight][remainder];
    }
    if(index%2==1){
        if(tight && digit>str[index]-'0'){
            return 0;
        }
        return digit_dp(str,index+1,tight && digit==str[index]-'0',(remainder*10+digit)%multiple);
    }
    int limit=9;
    if(tight) limit=str[index]-'0';
    long long res=0;
    for(int i=0;i<=limit;i++){
        if(i==digit) continue;
        res+=digit_dp(str,index+1,tight && str[index]-'0'==i,(remainder*10+i)%multiple);
        res=res%mod;
    }
    return dp[index][tight][remainder]=res;
}
int main() {
    string left,right;
    cin>>multiple>>digit;
    cin>>left;
    cin>>right;
    memset(dp,-1,sizeof dp);
    long long r=digit_dp(right,0,true,0);
    memset(dp,-1,sizeof dp);
    long long l=digit_dp(left,0,true,0);
    int rem1=0;
    bool flag=false;
    for(int i=0;i<left.size();i++){
        rem1=(rem1*10+(left[i]-'0'))%multiple;
        if((i%2==1 && (left[i]-'0')!=digit) || (i%2==0 && (left[i]-'0')==digit)){
            flag=true;
            break;
        }
    }
    if(!flag && rem1==0){
        l--;
    }
    cout<<((((r-l)%(mod))+mod)%mod)<<endl;
    return 0;
}