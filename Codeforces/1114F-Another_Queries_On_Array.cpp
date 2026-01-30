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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());


long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

ll spf[301];
vector<ll> primes;
struct SegmentTree{
    vector<ll> prod, masks, lmask, lprod;
    SegmentTree(vector<ll>& nums){
        prod.resize(4*nums.size());
        masks.resize(4*nums.size());
        lmask.resize(4*nums.size());
        lprod.resize(4*nums.size(),1);
        build_tree(0,0,nums.size()-1,nums);
    }
    void build_tree(int node, int left, int right, vector<ll>& nums){
        if (left==right){
            ll curr = nums[left];
            prod[node] = curr;
            for (int i = 0; i < primes.size(); i++){
                if (curr%primes[i]==0) {
                    masks[node]|=(1LL<<i);
                }
            }
            return;
        }
        int mid = (left+right)>>1;
        build_tree(2*node+1,left,mid,nums);
        build_tree(2*node+2,mid+1,right,nums);
        prod[node] = (prod[2*node+1]*prod[2*node+2])%MOD;
        masks[node] = masks[2*node+1] | masks[2*node+2];
    }
    void upd(int node, int left, int right, int arrLeft, int arrRight, ll val, ll mask){
        /*if (left==4 && right==4 && arrLeft==4 && arrRight==4){
                cout<<arrLeft<<" "<<arrRight<<" "<<lprod[node]<<endl;
        }*/
        if (lmask[node]){
            prod[node] = (prod[node] * binpow(lprod[node],arrRight-arrLeft+1,MOD))%MOD;
            masks[node] |= lmask[node];
            if (arrLeft!=arrRight){
                lprod[2*node+1] = (lprod[2*node+1]*lprod[node])%MOD;
                lprod[2*node+2] = (lprod[2*node+2]*lprod[node])%MOD;
                lmask[2*node+1] |= lmask[node];
                lmask[2*node+2] |= lmask[node];
            }
            lmask[node] = 0;
            lprod[node] = 1;
        }
        if (arrLeft > right || arrRight < left) return;
        if (arrLeft >= left && arrRight <= right){
            
            prod[node] = (prod[node]*binpow(val,arrRight-arrLeft+1,MOD))%MOD;
            masks[node] |= mask;
            if (arrLeft!=arrRight){
                lprod[2*node+1] = (lprod[2*node+1]*val)%MOD;
                lprod[2*node+2] = (lprod[2*node+2]*val)%MOD;
                lmask[2*node+1] |= mask;
                lmask[2*node+2] |= mask;
            }
            return;
        }
        int mid = (arrLeft + arrRight)>>1;
        upd(2*node+1,left,right,arrLeft,mid,val,mask);
        upd(2*node+2,left,right,mid+1,arrRight,val,mask);
        prod[node] = (prod[2*node+1]*prod[2*node+2])%MOD;
        masks[node] = masks[2*node+1]|masks[2*node+2];
    }
    ll qm(int node, int left, int right, int arrLeft, int arrRight){
        if (lmask[node]){
            prod[node] = (prod[node] * binpow(lprod[node],arrRight-arrLeft+1,MOD))%MOD;
            masks[node] |= lmask[node];
            if (arrLeft!=arrRight){
                lprod[2*node+1] = (lprod[2*node+1]*lprod[node])%MOD;
                lprod[2*node+2] = (lprod[2*node+2]*lprod[node])%MOD;
                lmask[2*node+1] |= lmask[node];
                lmask[2*node+2] |= lmask[node];
            }
            lmask[node] = 0;
            lprod[node] = 1;
        }
        if (arrLeft > right || arrRight < left) return 0;
        if (arrLeft >= left && arrRight <= right) return masks[node];
        int mid = (arrLeft + arrRight)>>1;
        return qm(2*node+1,left,right,arrLeft,mid)|qm(2*node+2,left,right,mid+1,arrRight);
    }
    ll qp(int node, int left, int right, int arrLeft, int arrRight){
        if (lmask[node]){
            prod[node] = (prod[node] * binpow(lprod[node],arrRight-arrLeft+1,MOD))%MOD;
            masks[node] |= lmask[node];
            if (arrLeft!=arrRight){
                lprod[2*node+1] = (lprod[2*node+1]*lprod[node])%MOD;
                lprod[2*node+2] = (lprod[2*node+2]*lprod[node])%MOD;
                lmask[2*node+1] |= lmask[node];
                lmask[2*node+2] |= lmask[node];
            }
            lmask[node] = 0;
            lprod[node] = 1;
        }
        if (arrLeft > right || arrRight < left) return 1;
        if (arrLeft >= left && arrRight <= right) return prod[node];
        int mid = (arrLeft + arrRight)>>1;
        return (qp(2*node+1,left,right,arrLeft,mid)*qp(2*node+2,left,right,mid+1,arrRight))%MOD;
    }
};
#define MOD 1000000007
template<int MODX>
struct ModInt {
  unsigned x;
  ModInt() : x(0) { }
  ModInt(signed sig) : x(((sig%MODX)+MODX)%MODX) {  }
  ModInt(signed long long sig) : x(((sig%MODX)+MODX)%MODX) { }
  int get() const { return (int)x; }
  ModInt pow(ll p) { ModInt res = 1, a = *this; while (p) { if (p & 1) res *= a; a *= a; p >>= 1; } return res; }
 
  ModInt &operator+=(ModInt that) { if ((x += that.x) >= MODX) x -= MODX; return *this; }
  ModInt &operator-=(ModInt that) { if ((x += MODX - that.x) >= MODX) x -= MODX; return *this; }
  ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MODX; if (x < 0) x += MODX; return *this; }
  ModInt &operator/=(ModInt that) { return (*this) *= that.pow(MODX - 2); }
 
  ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
  ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
  ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
  ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
  bool operator<(ModInt that) const { return x < that.x; }
  friend ostream& operator<<(ostream &os, ModInt a) { os << a.x; return os; }
};
typedef ModInt<MOD> mint;
void solve(int cas){
    memset(spf,-1,sizeof spf);
    for (int i = 2; i < 301; i++){
        if (spf[i]==-1){
            primes.emplace_back(i);
        }
        for (int j = i; j < 301; j+=i){
            if (spf[j]==-1) spf[j] = i;
        }
    }
    int n,q;
    cin>>n>>q;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    SegmentTree segTree(nums);
    
    while (q--){
        string s;
        cin>>s;
        if (s[0]=='M'){
            ll l,r,v;
            cin>>l>>r>>v;
            --l;--r;
            ll mask = 0;
            for (int i = 0; i < primes.size(); i++){
                if (v%primes[i]==0) mask|=(1LL<<i);
            }
            segTree.upd(0,l,r,0,n-1,v,mask);
        }
        else{
            ll l,r;
            cin>>l>>r;--l;--r;
            ll mask = segTree.qm(0,l,r,0,n-1);
            ll prod = segTree.qp(0,l,r,0,n-1);
            //cout<<prod<<" "<<mask<<endl;
            mint res = mint(prod);
            for (int i = 0; i < primes.size(); i++){
                if ((mask&(1LL<<i))!=0){
                    //cout<<primes[i]<<endl;
                    res = (res*(primes[i]-1));
                    res/=primes[i];
                }
            }
            cout<<res<<endl;
        }
    }
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}