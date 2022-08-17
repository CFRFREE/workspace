#include <bits/stdc++.h>

#define forn(i, n) for (ll i = 0; i < ll(n); i++)
#define fore(i, l, r) for (ll i = ll(l); i <= ll(r); ++i)
#define endl "\n"
#define pii pair<ll, ll>
#define all(x) x.begin(), x.end()
#define pb push_back
#define vi vector<ll>

using namespace std;
using ll = long long;
using ull = unsigned long long;

const ll inf = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
const ll N = 1e5 + 10;

template <typename T, class F = function<T(const T &, const T &)>>
class SparseTable {
public:
    ll n;
    vector<vector<T>> mat;
    F func;

    SparseTable(const vector<T> &a, const F &f) : func(f)
    {
        n = static_cast<ll>(a.size());
        ll max_log = 32 - __builtin_clz(n);
        // __builtin_clz(x) 前导0的个数
        mat.resize(max_log);
        mat[0] = a;
        for (ll j = 1; j < max_log; ++j)
        {
            mat[j].resize(n - (1 << j) + 1);
            for (ll i = 0; i <= n - (1 << j); ++i)
            {
                mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T get(ll from, ll to) const
    {
        assert(0 <= from && from <= to && to <= n - 1);
        ll lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;
    vi a(n);
    forn(i, n) cin >> a[i];
    vi pos;
    forn(i, n - 1)
    {
        if (a[i] > a[i + 1])
        {
            pos.pb(i);
        }
    }
    SparseTable<ll> st(
        pos, [&](ll i, ll j) { return a[pos[i]] > a[pos[j]] ? i : j; });
    vi R(pos.size());
    forn(i, pos.size())
    {
        if (i == pos.size() - 1)
        {
            R[i] = -1;
            continue;
        }
        // cout<<i<<": "<<st.get(i+1,pos.size()-1)<<"
        // "<<a[pos[st.get(i+1,pos.size()-1)]]<<" "<<a[pos[i]]<<endl;
        if (i == pos.size() - 1 ||
            a[pos[st.get(i + 1, pos.size() - 1)]] < a[pos[i]])
            R[i] = -1;
        else
        {
            ll l = i + 1, r = pos.size() - 1;
            while (l < r)
            {
                ll mid = l + r >> 1;
                if (a[pos[st.get(i + 1, mid)]] > a[pos[i]])
                    r = mid;
                else
                    l = mid + 1;
            }
            R[i] = l;
        }
    }
    // forn(i,pos.size()) cout<<a[pos[i]]<<" \n"[i==pos.size()-1];
    // forn(i,pos.size()) cout<<R[i]<<" \n"[i==pos.size()-1];
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        l--, r--;
        auto it = lower_bound(all(pos), l);
        ll x = it - pos.begin();
        if (it == pos.end() || *it > r)
            cout << 0 << endl;
        else
        {
            ll cnt = 0;
            while (pos[x] <= r - 1)
            {
                // cout<<x<<" ";
                cnt++;
                x = R[x];
                if (x == -1)
                    break;
            }
            // cout<<endl;
            cout << cnt << endl;
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
#endif
    ll tt;
    cin >> tt;
    while (tt--)
        solve();
    return 0;
}