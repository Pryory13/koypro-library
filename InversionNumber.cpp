#include <atcoder/all>
#include <atcoder/fenwicktree.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

ll InversionNumber(vector<ll> a) {
    ll n = a.size();
    fenwick_tree<ll> fw(200005);
    ll ans = 0;
    rep(j, n) {
        ans += j - fw.sum(0, a[j]);
        fw.add(a[j], 1);
    }
    return ans;
}
