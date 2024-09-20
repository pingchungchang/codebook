#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <int mod = 998244353>
struct mint {
    int x;
    mint() : x(0) {}
    mint(int _x) : x((_x % mod + mod) % mod) {}
    operator int() const {
        return x;
    }
    template <typename T>
    mint operator+(T t) {
        mint o = mint(t);
        int y = x + o.x;
        y -= (y >= mod ? mod : 0);
        return mint(y);
    }
    template <typename T>
    mint &operator+=(T t) {
        return (*this = operator+(t));
    }
    template <typename T>
    mint operator-(T t) {
        mint o = mint(t);
        int y = x - o.x;
        y += (y < 0 ? mod : 0);
        return mint(y);
    }
    template <typename T>
    mint &operator-=(T t) {
        return (*this = operator-(t));
    }
    template <typename T>
    mint operator*(T t) {
        mint o = mint(t);
        return mint((ll) x + o.x % mod);
    }
    template <typename T>
    mint &operator*=(T t) {
        return (*this = operator*(t));
    }
    template <typename T>
    mint POW(T t) {
        int b = int(t);
        mint a(x), ans(1);
        while (b) {
            if (b & 1) ans *= a;
            b >>= 1;
            a *= a;
        }
        return ans;
    }
    template <typename T>
    mint inv() {
        return POW(mod - 2);
    }
    template <typename T>
    mint operator/(T t) {
        mint o = mint(t);
        return operator*(o.inv());
    }
    template <typename T>
    mint &operator/=(T t) {
        return (*this = operator/(t));
    }
};
