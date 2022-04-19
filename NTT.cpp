#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using ll = long long;

int n;

ll gensikon = 3;

ll modpow(ll a, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

ll inva(ll a, ll mod) {
    ll m = mod;
    ll b = m, u = 1, v = 0;
    while (b) {
        ll t = a / b;
        a -= t * b;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    u %= m;
    if (u < 0) u += m;
    return u;
}

struct NTT {
    ll mod;
    ll si;
    vector<ll> root;
    vector<ll> inv_root;

    void start() {
        ll si = 0;
        ll mda = mod - 1;
        while (mda % 2 == 0) {
            mda /= 2;
            si++;
        }
        root.resize(si + 1);
        inv_root.resize(si + 1);
        root[si] = modpow(gensikon,
                          (mod - 1) * inva(modpow(2, si, mod), mod) % mod, mod);
        root[si] %= mod;
        inv_root[si] = inva(root[si], mod);
        inv_root[si] %= mod;
        for (int i = si - 1; i >= 0; i--) {
            root[i] = root[i + 1] * root[i + 1];
            root[i] %= mod;
            inv_root[i] = inv_root[i + 1] * inv_root[i + 1];
            inv_root[i] %= mod;
        }
    }

    void ntt(vector<ll> &f, ll mod, ll inv, ll lo) {
        int sz = f.size();
        if (sz == 1) return;
        vector<ll> fa, fb;
        rep(i, sz / 2) {
            fa.push_back(f[2 * i]);
            fb.push_back(f[2 * i + 1]);
        }
        ntt(fa, mod, inv, lo - 1);
        ntt(fb, mod, inv, lo - 1);
        ll now = 1;
        rep(i, sz) {
            f[i] = fa[i % (sz / 2)] + now * fb[i % (sz / 2)] % mod;
            f[i] %= mod;
            if (inv == 1)
                now *= root[lo];
            else
                now *= inv_root[lo];
            now %= mod;
        }
    }

    vector<ll> convolution(vector<int32_t> &a, vector<int32_t> &b, ll mod) {
        ll sz = 1;
        ll _lo = 0;
        while (sz < 2 * n) sz *= 2, _lo++;
        vector<ll> na(sz), nb(sz);
        rep(i, n) na[i] = a[i] % mod;
        rep(i, n) nb[i] = b[i] % mod;
        ntt(na, mod, 1, _lo);
        ntt(nb, mod, 1, _lo);
        rep(i, sz) na[i] *= nb[i];
        rep(i, sz) na[i] %= mod;
        ntt(na, mod, -1, _lo); // inv ntt

        rep(i, na.size())(na[i] *= (inva(sz, mod) % mod)) %= mod;
        return na;
    }
    NTT(ll _mod) {
        mod = _mod;
        start();
    }
};


//NTT hoge(998244353)で宣言。
//hoge.convolution(f, g, mod)で計算。
