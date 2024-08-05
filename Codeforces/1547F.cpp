#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>

#include <cmath>
#define pii pair<int,int>
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

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
struct SparseTable{
    vector<vector<int>> table;
    SparseTable(vector<int> nums){
        table.resize(nums.size(),vector<int> (32));
        for (int i = 0; i < nums.size(); i++){
            table[i][0]=nums[i];
        }
        for (int j = 1; j < 32; j++){
            for (int i = 0; i+(1<<j)<=nums.size();i++){
                table[i][j]=gcd(table[i][j-1],table[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int left, int right){
        int length = right-left+1;
        int bit = 31-__builtin_clz(length);
        return gcd(table[left][bit],table[right-(1<<bit)+1][bit]);
    }
};
void solve(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    SparseTable st (nums);
    int lp = 0;
    int rp = n;
    while (lp<=rp){
        int mid = (lp+rp)>>1;
        int c = -1;
        bool good = true;
        for (int i = 0; i < n; i++){
            int q = -1;
            if (i+mid<n){
                q=st.query(i,i+mid);
            }
            else{
                q =gcd(st.query(i,n-1),st.query(0,(i+mid)%n));
            }                                                   
            if (c==-1){
                c=q;
            }
            else if (c!=q){
                good=false;
                break;
            }
        }                                      
        if (good){
            rp=mid-1;
        }
        else{
            lp=mid+1;
        }
    }
    cout<<lp<<endl;
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