template <typename T>
struct Z_alg {
    void operator()(T a, int n, int *z) {
        fill(z, z + n + 1, 0);
        int l = 0;
        for (int i = 1; i <= n; i++) {
            if (i >= l + z[l]) {
                while (i + z[i] < n && a[i + z[i]] == a[z[i]]) z[i]++;
                l = i;
                continue;
            }
            int i_ = i - l;
            if (i_ + z[i_] == z[l]) {
                z[i] = z[i_];
                while (i + z[i] < n && a[i + z[i]] == a[z[i]]) z[i]++;
                l = i;
                continue;
            }
            z[i] = (i_ + z[i_] < z[l] ? z[i_] : z[l] - i_);
        }
    }
};
