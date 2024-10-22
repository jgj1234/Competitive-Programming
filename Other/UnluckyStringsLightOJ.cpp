#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define REP(i,n) for(int i = 0; i < (n); i++)
const int mod = 1e9 + 7;
int n;
struct Matrix {
	vector<vector<unsigned int>> a = vector<vector<unsigned int>>(n, vector<unsigned int>(n));
	Matrix operator *(const Matrix& other) {
		Matrix product;
		vector<vector<unsigned int>> tmp(n, vector<unsigned int>(n));
		REP(i,n)REP(j,n)REP(k,n) {
			tmp[i][k] += a[i][j] * other.a[j][k];
		}
		REP(i,n)REP(j,n) product.a[i][j] = tmp[i][j];
		return product;
	}
};
Matrix expo_power(Matrix a, long long k) {
	Matrix product;
	REP(i,n) product.a[i][i] = 1;
	while(k > 0) {
		if(k % 2) {
			product = product * a;
		}
		a = a * a;
		k /= 2;
	}
	return product;
}
void solve(int cas){
    int x; cin>>x;
    string allowed;
    cin>>allowed;
    string s;
    cin>>s;
    n = s.size();
    Matrix mat;
    mat.a[0][0] = allowed.size() - 1;
    mat.a[0][1] = 1;
    vector<int> pi(s.size());
    for (int i = 1; i < s.size(); i++){
        int j = pi[i-1];
        while (j > 0 && s[i]!=s[j]) j = pi[j-1];
        if (s[i]==s[j]) j++;
        pi[i] = j;
    }
    for (int done = 1; done < s.size(); done++){
            for (int f = 0; f < allowed.size(); f++){
                char c = allowed[f];
                if (c==s[done]) continue;
                int j = pi[done - 1];
                while (j > 0 && c!=s[j]) j = pi[j-1];
                if (c==s[j]) j++;
                mat.a[done][j]++;
            }
        
        if (done + 1 < n){
            mat.a[done][done + 1] = 1;
        }
    }
    Matrix res = expo_power(mat, x);
    
    unsigned int ans = 0;
    for (int i = 0; i < n; i++){
        ans+=res.a[0][i];
    }
    cout<<"Case "<<cas<<": "<<ans<<endl;
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}