#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

ll ChromaticNumber(const vector<vector<ll>> &G) {
    ll n = G.size();
    if (!n) return 0;
    vector<ll> g(n, 0);
    rep(i, n) {
        for (auto c : G[i]) {
            g[i] |= (1LL << c);
        }
    }
    const ll modulo = 1077563119;
    ll all = (1LL << n);
    vector<ll> ind(all), s(all);
    rep(i, all) s[i] = ((n - __builtin_popcount(i)) & 1 ? -1 : 1);
    ind[0] = 1;
    rep(i, all) {
        if (!i) continue;
        ll ctz = __builtin_ctz(i);
        ind[i] = ind[i - (1LL << ctz)] + ind[(i - (1LL << ctz)) & ~g[ctz]];
        if (ind[i] >= modulo) ind[i] -= modulo;
    }
    rep(k, n) {
        if (!k) continue;
        ll sum = 0;
        rep(i, all) {
            ll cur = ((s[i] * (ll)ind[i]) % modulo);
            s[i] = cur;
            sum += cur;
        }
        if (sum % modulo != 0) return k;
    }
    return n;
}