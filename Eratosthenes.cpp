#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

struct Eratosthenes {
    vector<bool> isprime;

    vector<int> minfactor;

    Eratosthenes(int N) : isprime(N + 1, true), minfactor(N + 1, -1) {
        isprime[1] = false;
        minfactor[1] = 1;
        rep(p, N + 1) {
            if (p <= 1) continue;
            if (!isprime[p]) continue;
            minfactor[p] = p;
            for (int q = p * 2; q <= N; q += p) {
                isprime[q] = false;
                if (minfactor[q] == -1) minfactor[q] = p;
            }
        }
    }

    vector<pair<int, int>> factorize(int n) {
        vector<pair<int, int>> res;
        while (n > 1) {
            int p = minfactor[n];
            int exp = 0;
            while (minfactor[n] == p) {
                n /= p;
                exp++;
            }
            res.emplace_back(p, exp);
        }
        return res;
    }
};