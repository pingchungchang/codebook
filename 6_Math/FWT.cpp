#include <bits/stdc++.h>
using namespace std;
#define fs first
#define sc second
#define FOR(i, j, k) for (int i = j, Z = k; i < Z; i++)
using ll = long long;
typedef pair<int, int> pii;

typedef pair<pii, pii> MAT;

template <int mod = 998244353>
struct mint {
    int x;
    mint() : x(0) {}
    mint(int _x) : x(_x) {}
    mint operator+(mint o) {
        int y = x + o.x;
        y -= (y >= mod ? mod : 0);
        return mint(y);
    }
    mint operator*(int y) {
        y += (y < 0 ? mod : 0);
        return mint((ll) x * y % mod);
    }
    mint operator*(mint o) {
        return mint((ll) x * o.x % mod);
    }
    mint inv() {
        int b = mod - 2, a = x;
        int ans = 1;
        while (b) {
            if (b & 1) ans = (ll) ans * a % mod;
            b >>= 1;
            a = (ll) a * a % mod;
        }
        return mint(ans);
    }
};

template <typename T = int>
struct FWT {
    enum FWT_TYPE {
        AND,
        OR,
        XOR
    };
    const MAT mat[3] = {
        {{1, 1}, {0, 1}},
        {{1, 0}, {1, 1}},
        {{1, 1}, {1, -1}}
    };
    const MAT tam[3] = {
        {{1, -1}, {0, 1}},
        {{1, 0}, {-1, 1}},
        {{1, 1}, {1, -1}}
    };
    FWT() {}
    void btf(T &L, T &R, MAT &m) {
        T l = L, r = R;
        L = l * m.fs.fs + r * m.fs.sc;
        R = l * m.sc.fs + r * m.sc.sc;
    }
    void apply(T *a, int n, bool inv, FWT_TYPE tp) {
        MAT m = (inv ? tam : mat)[tp];
        for (int w = 1; w < n; w <<= 1) {
            FOR(i, 0, n) if (i & w) {
                btf(a[i - w], a[i], m);
            }
        }
        if (tp == FWT_TYPE::XOR && inv) {
            T n_ = T(n).inv();
            FOR(i, 0, n) a[i] = a[i] * n_;
        } 
    }
};

