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

void solve(int cas){ 
    int n; cin>>n;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    bool al = true;
    for (int i = 0; i < n; i++){
        al&=(nums[i]==-1);
    }
    if (al){
        for (int i = 0; i < n; i++){
            if (i%2==0){
                cout << 1 << ' ';
            }
            else{
                cout << 2 << ' ';
            }
        }
        cout << '\n';
        return;
    }
    auto fillPref = [&] (int i) -> void{
        bool b = (nums[i]==1);
        for (int j = i - 1; j >= 0; j--){
            if (b){
                nums[j] = nums[j+1]<<1;
            }
            else{
                nums[j] = nums[j+1]>>1;
            }
            b^=1;
        }
    };
    auto fillSuff = [&] (int i) -> void{
        bool b = (nums[i]==1);
        for (int j = i + 1; j < n; j++){
            if (!b){
                nums[j] = nums[j-1]>>1;
            }
            else{
                nums[j] = nums[j-1]<<1;
            }
            b ^= 1;
        }
    };
    int st = -1, en = -1;
    for (int i = 0; i < n; i++){
        if (nums[i]!=-1){
            if (st==-1){
                st = i;
            }
            en = i;
        }
    }
    fillSuff(en);
    fillPref(st);
    auto cvt = [&] (ll i, ll j, ll ops) -> vector<ll>{
        int curr = i;
        int divTimes = 0;
        int start = -1;
        while (1){
            int diff = (31 - __builtin_clz(j)) - (31 - __builtin_clz(curr));
            if (diff >= 0){
                if ((j>>diff)==curr){
                    start = diff - 1;
                    break;
                }
            }
            divTimes++;
            curr>>=1;
        }
        int mul = (31 - __builtin_clz(j)) - (31 - __builtin_clz(curr));
        int ct = 0;
        if (ops < divTimes + mul - 1 || abs(ops - (divTimes + mul - 1))%2==1){
            return vector<ll> {-1};
        }
        bool f = false;
        vector<ll> res(ops);
        for (int x = 0; x < ops; x++){
            start = max(start, 0);
            if (divTimes){
                res[x] = (i/=2);
                divTimes--;
            }
            else if (i < j){
                res[x] = (i = (i*2) + ((j&(1<<start))!=0));
                start--;
                mul--;
            }
            else{
                if (f){
                    res[x] = (i/=2);
                    start++;
                }
                else{
                    res[x] = (i = (i*2) + ((j&(1<<start))!=0));
                    start--;
                }
                f^=1;
            }
        }
        return res;
    };
    int last = st;
    for (int i = st + 1; i <= en; i++){
        if (nums[i]!=-1){
            ll ops = i - last - 1;
            if (ops==0){
                if (nums[i-1]!=(nums[i]/2) && nums[i]!=(nums[i-1]/2)){
                    cout << -1 << '\n';
                    return;
                }
                last = i;
                continue;
            }
            vector<ll> r = cvt(nums[last], nums[i], ops);
            if (r[0]==-1){
                cout << -1 << '\n';
                return;
            }
            int ct = 0;
            last++;
            while (last < i){
                nums[last] = r[ct];
                ct++;
                last++;
            }
        }
    }
    for (int i = 0; i < n - 1; i++){
        assert(nums[i] > 0 && ((nums[i]/2==nums[i+1]) || (nums[i+1]/2==nums[i])));
    }
    assert(nums.back() > 0);
    for (int i = 0; i < n; i++){
        cout << nums[i] << ' ';
    }
    cout << '\n';
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