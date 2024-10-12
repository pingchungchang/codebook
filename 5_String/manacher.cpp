template <typename T>
struct MANACHER {
    void operator()(T a, int n, int *mn) {
        fill(mn, mn + n, 0);
        int l = 0;
        for (int i = 1; i < n; i++) {
            if (i > l + mn[l]) {
                while (i - mn[i] - 1 >= 0 && i + mn[i] + 1 < n && a[i - mn[i] - 1] == a[i + mn[i] + 1]) mn[i]++;
                l = i;
                continue;
            }
            int i_ = 2 * l - i;
            if (i_ - mn[i_] == l - mn[l]) {
                mn[i] = mn[i_];
                while (i - mn[i] - 1 >= 0 && i + mn[i] + 1 < n && a[i - mn[i] - 1] == a[i + mn[i] + 1]) mn[i]++;
                l = i;
                continue;
            }
            mn[i] = (i_ - mn[i_] > l - mn[l] ? mn[i_] : i_ - l + mn[l]);
        }
    }
};
