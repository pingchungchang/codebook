#include <bits/stdc++.h>
using namespace std;
#define FOR(i, j, k) for (int i = j, Z = k; i < Z; i++)

template <typename T>
struct FFT {
    const T pi = acos(-1);
    complex<T> cis(T theta) {
        return complex<T>(cos(theta), sin(theta));
    }
    complex<T> OMEGA(int n, int k) {
        return cis(pi * 2 * k / n);
    }
    void apply(complex<T> *a, int N, bool inv) {
        auto REVERSE = [&](int x) -> int {
            int ans = 0;
            for (int i = 1; i < N; i <<= 1) {
                ans <<= 1;
                if (i & x) ans |= 1;
            }
            return ans;
        };
        FOR(i, 0, N) {
            int r = REVERSE(i);
            if (i < r) swap(a[i], a[r]);
        }
        for (int w = 1; w < N; w <<= 1) {
            int omega_n = w << 1;
            for (int omega_k = 0; omega_k < w; omega_k++) {
                complex<T> omega = OMEGA(omega_n, (inv ? -1 : 1) * omega_k);
                for (int s = 0; s < N; s += omega_n) {
                    complex<T> &L = a[s + omega_k], &R = a[s + omega_k + w];
                    complex<T> l = L, r = omega * R;
                    L = l + r;
                    R = l - r;
                }
            }
        }
        if (inv) {
            FOR(i, 0, N) a[i] /= N;
        }
    }
};
