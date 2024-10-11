#define TYPE double
typedef complex<TYPE> cd;
#undef TYPE

struct FFT {
    const double pi = acos(-1);
    cd cis(double theta) {
        return cd(cos(theta), sin(theta));
    }
    cd OMEGA(int n, int k) {
        return cis(pi * 2 * k / n);
    }
    void operator()(cd *a, int N, bool inv) {
        auto REV = [&](int x) -> int {
            int ans = 0;
            for (int i = 1; i < N; i <<= 1) {
                ans <<= 1;
                if (i & x) ans |= 1;
            }
            return ans;
        };
        FOR(i, 0, N) {
            int r = REV(i);
            if (i < r) swap(a[i], a[r]);
        }
        for (int w = 1; w < N; w <<= 1) {
            int on = w << 1;
            for (int ok = 0; ok < w; ok++) {
                cd omega = OMEGA(on, (inv ? -1 : 1) * ok);
                for (int s = 0; s < N; s += on) {
                    cd &L = a[s + ok], &R = a[s + ok + w];
                    cd l = L, r = omega * R;
                    L = l + r;
                    R = l - r;
                }
            }
        }
        if (inv) {
            for (int i = 0; i < N; i++) a[i] /= N;
        }
    }
};

