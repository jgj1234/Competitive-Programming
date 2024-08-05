#include <bits/stdc++.h>
using namespace std;
#define read(type) readInt<type>() // Fast read
#define ll long long
#define nL "\n"
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define a first
#define b second
#define vi vector<int>
#define all(x) (x).begin(), (x).end()
#define umap unordered_map
#define uset unordered_set
#define MOD 1000000007
#define imax INT_MAX
#define imin INT_MIN
#define exp 1e9
#define sz(x) (int((x).size()))
vi str=vector(103,0);
ll dp[103][11][1<<11];
ll digit_dp(int index, int base, int bitmask,bool tight,bool leading_zero){
	if(index<0){
		return bitmask==0;
	}
	if(index+1<__builtin_popcount(bitmask)){
		return 0;
	}
	if (!tight && !leading_zero && dp[index][base][bitmask]!=-1){
		return dp[index][base][bitmask];
	}
	int upper_limit=tight?str[index]:base-1;
	ll res=0;
	for (int i=0;i<=upper_limit;i++){
		if(leading_zero && i==0){
			res+=digit_dp(index-1,base,0,false,true);
		}
		else{
			bool ntight=tight&&i==upper_limit;
			int nmask=bitmask^(1<<i);
			res+=digit_dp(index-1,base,nmask,ntight,false);
		}
	}
	if(!leading_zero && !tight){
		dp[index][base][bitmask]=res;
	}
	return res;
}
void solve(){
	int base;
	ll left,right;
	cin>>base>>left>>right;
	int count=0;
	while(left>0){
		str[count++]=left%base;
		left/=base;
	}
	int bitmask=0;
	for(int i=count-1;i>=0;i--){
		bitmask=bitmask^(1<<str[i]);
    }
	int rem=bitmask==0;
	ll ldp=digit_dp(count-1,base,0,true,true);
	count=0;
	while(right>0){
		str[count++]=right%base;
		right/=base;
	}
	ll rdp=digit_dp(count-1,base,0,true,true);
	cout<<rdp-ldp+rem<<endl;

}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    memset(dp,-1,sizeof dp);
    int t;
	cin>>t;
	while(t--){
		solve();
	}

}