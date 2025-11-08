// SegmentTree with lazy propagations
// This example can solve queries:
// 1) Add(l, r, x)  -> a[i] += x for i in [l, r)
// 2) get Sum(l, r) -> ans = sum( a[i] for i in [l, r) )
// 3) get Max(l, r) -> ans = max( a[i] for i in [l, r) )

#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll INF = 2e18;

struct SegmentTree {
    struct Node{
        ll mx;
        ll sm;
        ll cnt;
        ll add;

        void ApplyAdd(ll x) {
            mx += x;
            add += x;
            sm += cnt * x;
        }
    };

    Node Neutral() {
        return Node {
            .mx = -INF,
            .sm = 0,
            .cnt = 0,
            .add = 0
        };
    }

    Node Join(const Node& lhs, const Node& rhs) {
        return Node {
            .mx = max(lhs.mx, rhs.mx),
            .sm = lhs.sm + rhs.sm,
            .cnt = lhs.cnt + rhs.cnt,
            .add = 0
        };
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
            t[v].mx = a[vl];
            t[v].sm = a[vl];
            t[v].cnt = 1;
            t[v].add = 0;
        }
        else {
            const ll m = (vl + vr) / 2;
            Build(2 * v, vl, m, a);
            Build(2 * v + 1, m, vr, a);
            t[v] = Join(t[2 * v], t[2 * v + 1]);
        }
    }

    void Push(ll v) {
        if(t[v].add != 0){
            t[2 * v].ApplyAdd(t[v].add);
            t[2 * v + 1].ApplyAdd(t[v].add);
            t[v].add = 0;
        }
    }

    void AssignAdd(ll v, ll vl, ll vr, ll l, ll r, ll x) {
        if(vl >= r || vr <= l) {

        }
        else if(vl >= l && vr <= r) {
            t[v].ApplyAdd(x);
        }
        else {
            const ll m = (vl + vr) / 2;
            Push(v);
            AssignAdd(2 * v, vl, m, l, r, x);
            AssignAdd(2 * v + 1, m, vr, l, r, x);
            t[v] = Join(t[2 * v], t[2 * v + 1]);
        }
    }

    void AssignAdd(ll l, ll r, ll x) {
        AssignAdd(1, 0, n, l, r, x);
    }

    Node Query(ll v, ll vl, ll vr, ll l, ll r) {
        if(vl >= r || vr <= l) {
            return Neutral();
        }
        else if(vl >= l && vr <= r) {
            return t[v];
        }
        else {
            const ll m = (vl + vr) / 2;
            Push(v);
            auto lhs = Query(2 * v, vl, m, l, r);
            auto rhs = Query(2 * v + 1, m, vr, l, r);
            return Join(lhs, rhs);
        }
    }

    ll Sum (ll l, ll r) {
        return Query(1, 0, n, l, r).sm;
    }

    ll Max(ll l, ll r) {
        return Query(1, 0, n, l, r).mx;
    }
};



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n; cin >> n;
    ll q; cin >> q;
    vector<ll> a(n);
    for(ll i = 0; i < n; ++i) {
        cin >> a[i];
    }
    SegmentTree sgt(a);
    while(q--) {
        ll type, l, r, x;
        cin >> type >> l >> r;
        l--;
        if(type == 1) {
            cin >> x;
            sgt.AssignAdd(l, r, x);
        }
        if(type == 2) {
            cout << sgt.Sum(l, r) << "\n";
        }
        if(type == 3) {
            cout << sgt.Max(l, r) << "\n";
        }
    }

    return 0;
}
