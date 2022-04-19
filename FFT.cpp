#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

void dft(vector<complex<double>> &f, int inv) {
    int sz = f.size();
    if (sz == 1) return;
    vector<complex<double>> a, b;
    rep(i, sz / 2) {
        a.push_back(f[2 * i]);
        b.push_back(f[2 * i + 1]);
    }
    dft(a, inv);
    dft(b, inv);
    complex<double> now = 1;
    complex<double> zeta = polar(1.0, inv * 2.0 * acos(-1) / sz);
    rep(i, sz) {
        f[i] = a[i % (sz / 2)] + now * b[i % (sz / 2)];
        now *= zeta;
    }
}
vector<double> pl(vector<ll> f, vector<ll> g) {
    int n = 1;
    while (n < f.size() + g.size()) n *= 2;
    vector<complex<double>> nf(n), ng(n);
    rep(i, f.size()) { nf[i] = f[i]; }
    rep(i, g.size()) { ng[i] = g[i]; }
    dft(nf, 1);
    dft(ng, 1);
    rep(i, n) nf[i] *= ng[i];
    dft(nf, -1);
    vector<double> ans;
    rep(i, n) ans.push_back(nf[i].real() / n);
    return ans;
}

//pl(f,g)で計算をする。(ll)roundl(c)で四捨五入。