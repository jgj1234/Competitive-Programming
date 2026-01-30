#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 1600000;
vector<int> g[N];
bool vis[N];
int tin[N], low[N], col[N], st[N], pos[N];
int c = 0, timer = 1, scc = 0, sp = 0;
void add_disjunction(int a, bool aa, int b, bool bb){
    g[2*a + (1 - aa)].emplace_back(2*b + bb);
    g[2*b + (1 - bb)].emplace_back(2*a + aa);
}
void dfs(int node){
    vis[node] = 1;
    tin[node] = low[node] = timer++;
    st[sp++] = node;
    for (int neighbor: g[node]){
        if (!tin[neighbor]){
            dfs(neighbor);
            low[node] = min(low[node], low[neighbor]);
        }
        else if (vis[neighbor]){
            low[node] = min(low[node], low[neighbor]);
        }
    }
    if (low[node] == tin[node]){
        --sp;
        while (st[sp] != node){
            vis[st[sp]] = 0;
            col[st[sp]] = scc;
            sp--;
        }
        col[node] = scc++;
        vis[node] = 0;
    }
}
void solve(int cas){
    int n,p,mx,m; cin>>n>>p>>mx>>m;
    for (int i = 0; i < n; i++){
        int x,y; cin>>x>>y;
        --x;--y;
        add_disjunction(x, true, y, true);
    }
    vector<array<int, 3>> nums(p);
    for (int i = 0; i < p; i++){
        cin >> nums[i][0] >> nums[i][1];
        nums[i][2] = i;
    }
    sort(all(nums));
    for (int i = 0; i < p; i++) pos[nums[i][2]] = i;
    for (int i = 0; i < m; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        add_disjunction(u, false, v, false);
    }
    int curr = p;
    for (int i = p - 1; i >= 0; i--){
        if (i + 1 != p){
            add_disjunction(curr - 1, false, curr, true);
        }
        add_disjunction(nums[i][2], false, curr, true);
        curr++;
    }
    for (int i = 0; i < p; i++){
        int lp = i + 1, rp = p - 1;
        while (lp <= rp){
            int mid = (lp + rp)/2;
            if (nums[mid][0] > nums[i][1]){
                rp = mid - 1;
            }
            else{
                lp = mid + 1;
            }
        }
        if (lp != p){
            add_disjunction(nums[i][2], false, p + (p - 1 - lp), false);
        }
    }
    for (int i = 0; i < 2 * curr; i++){
        if (!tin[i]) dfs(i);
    }
    for (int i = 0; i < 2 * p; i += 2){
        if (col[i] == col[i+1]){
            cout << -1 << '\n';
            return;
        }
    }
    int mn = 0, mxx = INT_MAX;
    vector<int> picked;
    for (int i = 0; i < 2*p; i+=2){
        if (col[i] > col[i+1]){
            picked.emplace_back(i/2 + 1);
            mn = max(mn, nums[pos[i/2]][0]);
            mxx = min(mxx, nums[pos[i/2]][1]);
        }
    }
    cout << (int) picked.size() << " " << mn << '\n';
    for (auto& x: picked) cout << x << " ";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    //cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}