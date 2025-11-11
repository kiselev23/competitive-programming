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
#include <sstream>
#include <cctype>
#include <cstdio>

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
const ll MOD = 1e9+7;
const ll K = 300;

struct SegmentTree {
  struct Node {
    ll cnt;
    vector<ll> sub;
  };

  Node Join(const Node& lhs, const Node& rhs) {
    Node res;
    res.cnt = lhs.cnt + rhs.cnt;
    res.sub.resize(res.cnt);
    merge(lhs.sub.begin(), lhs.sub.end(), rhs.sub.begin(), rhs.sub.end(), res.sub.begin());
    return res;
  }

  vector<Node> t;
  ll n;

  SegmentTree(const vector<ll>& a) {
    n = a.size();
    t.resize(4 * n);
    Build(1, 0, n, a);
  }

  void Build(ll v, ll vl, ll vr, const vector<ll>& a) {
    if(vl + 1 == vr) {
      t[v].cnt = 1;
      t[v].sub = {a[vl]};
    }
    else {
      const ll m = (vl + vr) / 2;
      Build(2 * v, vl, m, a);
      Build(2 * v + 1, m, vr, a);
      t[v] = Join(t[2 * v], t[2 * v + 1]);
    }
  }

  ll Query(ll v, ll vl, ll vr, ll l, ll r, ll x, ll y) {
    if(vl >= r || vr <= l) {
      return 0;
    }
    else if(vl >= l && vr <= r) {
      return (t[v].sub.end() - lower_bound(t[v].sub.begin(), t[v].sub.end(), x)) - (t[v].sub.end() - upper_bound(t[v].sub.begin(), t[v].sub.end(), y));;
    }
    else {
      const ll m = (vl + vr) / 2;
      auto lhs = Query(2 * v, vl, m, l, r, x,  y);
      auto rhs = Query(2 * v + 1, m, vr, l, r, x, y);
      return lhs + rhs;
    }
  }

  ll Search(ll l, ll r, ll x, ll y) {
    return Query(1, 0, n, l, r, x, y);
  }
};


int main() {
  fastio();

  #ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif

  ll n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for(ll i = 0; i < n; ++i) {
    cin >> a[i];
  }

  SegmentTree sgt(a);
  ll l, r, x, y;
  while(q--) {
    cin >> l >> r >> x >> y;
    l--;
    cout << sgt.Search(l, r, x, y);
    if(q != 0) {
      cout << "\n";
    }
  }
  return 0;
}
