#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <limits>
#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;
using str = string;
using chr = char;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using vpl = vector<pl>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define forn(i, n) for(ll i = 0; i < n; ++i)
#define rforn(i, n) for(ll i = n - 1; i >= 0; --i)
#define pb push_back
#define mp make_pair
#define fi first 
#define se second 
#define fastio() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

const ll INF = 2e18;


ll get_code(ll a, ll b) {
    if (a == 0) {
        if (b == 0) return 0;
        if (b == 1) return 1;
        if (b == 2) return 2;
        if (b == 3) return 3;
    } else if (a == 1) {
        if (b == 1) return 4;
        if (b == 2) return 5;
        if (b == 3) return 6;
    } else if (a == 2) {
        if (b == 1) return 7;
        if (b == 2) return 8;
        if (b == 3) return 9;
    } else if (a == 3) {
        if (b == 1) return 10;
        if (b == 2) return 11;
        if (b == 3) return 12;
    }
    return -1;
}


ll calc_gain(ll prev1, ll prev2, ll current) {
    set<ll> types;
    if (prev1 != 0) types.insert(prev1);
    if (prev2 != 0) types.insert(prev2);
    types.insert(current);
    return types.size();
}

int main() {
    fastio();

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    map<ll, pair<ll, ll>> pattern;
    pattern[0] = {0, 0};
    pattern[1] = {0, 1};
    pattern[2] = {0, 2};
    pattern[3] = {0, 3};
    pattern[4] = {1, 1};
    pattern[5] = {1, 2};
    pattern[6] = {1, 3};
    pattern[7] = {2, 1};
    pattern[8] = {2, 2};
    pattern[9] = {2, 3};
    pattern[10] = {3, 1};
    pattern[11] = {3, 2};
    pattern[12] = {3, 3};

    ll n;
    cin >> n;
    str s;
    cin >> s;
    
    vl foods(n);
    forn(i, n) {
        if (s[i] == 'M') foods[i] = 1;
        else if (s[i] == 'F') foods[i] = 2;
        else if (s[i] == 'B') foods[i] = 3;
    }
    
    vector<vector<vl>> dp(n + 1, vector<vl>(13, vl(13, -INF)));
    dp[0][0][0] = 0;
    
    forn(i, n) {
        ll current_food = foods[i];
        
        forn(j, 13) {
            forn(k, 13) {
                if (dp[i][j][k] == -INF) continue;
                
                ll prev1_1 = pattern[j].first;
                ll prev1_2 = pattern[j].second;
                ll prev2_1 = pattern[k].first;
                ll prev2_2 = pattern[k].second;
                
                ll new_state1 = get_code(prev1_2, current_food);
                ll gain1 = calc_gain(prev1_1, prev1_2, current_food);
                dp[i + 1][new_state1][k] = max(dp[i + 1][new_state1][k], dp[i][j][k] + gain1);
                
                ll new_state2 = get_code(prev2_2, current_food);
                ll gain2 = calc_gain(prev2_1, prev2_2, current_food);
                dp[i + 1][j][new_state2] = max(dp[i + 1][j][new_state2], dp[i][j][k] + gain2);
            }
        }
    }
    
    ll ans = 0;
    forn(j, 13) {
        forn(k, 13) {
            ans = max(ans, dp[n][j][k]);
        }
    }
    
    cout << ans << endl;

    return 0;
}
