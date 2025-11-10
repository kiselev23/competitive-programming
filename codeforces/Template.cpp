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
using ull = unsigned long long;
using ld = long double;
using str = string;
using chr = char;

#define all(x) x.begin(),x.end()
#define range(i, n) for (int i=0;i<int(n);++i)
#define range(i, s, f) for (int i=(s);i<int(f);++i)
#define rrange(i,n) for (int i=(n)-1;i>=0;--i)
#define mp make_pair
#define CF(x) int x;cin >> x;while(x--)
#define md(x) if (x>=mod) x%=mod
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define forn(i, n) for(ll i = 0; i < n; ++i)
#define rforn(i, n) for(ll i = n - 1; i >= 0; --i)
#define pb push_back
#define fi first 
#define se second
#define fastio() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

const ll MOD = 1e9 + 5;
const double INF = 1e18;

template<typename T>istream& operator >>(istream& in, vector<T>& a) { range(i, a.size()) in >> a[i]; return in; }
template<typename T>ostream& operator <<(ostream& out, const vector<T>& a) { range(i, a.size()) out << a[i] << ' '; return out; }

template<typename T1, typename T2>istream& operator >>(istream& in, pair<T1, T2>& p) { in >> p.first >> p.second; return in; }
template<typename T1, typename T2>ostream& operator <<(ostream& out, const pair<T1, T2>& p) { out << p.first << ' ' << p.second; return out; }

int main() {
	fastio();

	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif


  
	return 0;
}
