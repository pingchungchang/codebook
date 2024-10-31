#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define FOR(i, j, k) for (int i = j, Z = k; i < Z; i++)

struct NTT {
    const static int LG = 20;
    int mod;
    int o[(1 << LG) + 1];
    int ADD(int a, int b) {
        a += b;
        a -= (a >= mod ? mod : 0);
        return a;
    }
    int SUB(int a, int b) {
        a -= b;
        a += (a < 0 ? mod : 0);
        return a;
    }
    int MUL(int a, int b) {
        return (ll) a * b % mod;
    }
    int POW(int a, int b) {
        int ans = 1;
        while (b) {
            if (b & 1) ans = MUL(ans, a);
            b >>= 1;
            a = MUL(a, a);
        }
        return ans;
    }
    NTT(int g, int gap, int _mod) {
        mod = _mod;
        o[0] = 1;
        int pp = POW(g, gap);
        FOR(i, 1, (1 << LG) + 1) o[i] = MUL(o[i - 1], pp);
    }
    void operator()(int *a, int n, bool inv) {
        auto REV = [&](int x) -> int {
            int ans = 0;
            for (int w = 1; w < n; w <<= 1) {
                ans = (ans << 1) | (x & 1);
                x >>= 1;
            }
            return ans;
        };
        FOR(i, 0, n) {
            int j = REV(i);
            if (i < j) swap(a[i], a[j]);
        }
        for (int w = 1; w < n; w <<= 1) {
            int owo = 1 << (LG - __lg(w) - 1), oid = 0;
            FOR(i, 0, w) {
                int omega = o[inv ? (1 << LG) - oid : oid];
                for (int s = 0; s < n; s += (w << 1)) {
                    int &L = a[s + i], &R = a[s + w + i];
                    int l = L, r = MUL(omega, R);
                    L = ADD(l, r);
                    R = SUB(l, r);
                }
                oid += owo;
            }
        }
        if (inv) {
            int x = POW(n, mod - 2);
            FOR(i, 0, n) a[i] = MUL(a[i], x);
        }
    }
};

const ll mxn = 1<<20;
const ll mod = 998244353;

NTT T(3,952,mod);
int a[mxn],b[mxn];
ll fac[mxn],ifac[mxn];
int N;

ll pw(ll a,ll b){
	ll re = 1;
	while(b){
		if(b&1)re = re*a%mod;
		b>>=1;
		a = a*a%mod;
	}
	return re;
}
ll inv(ll k){
	return pw(k,mod-2);
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>N;
	fac[0] = 1;
	for(int i = 1;i<mxn;i++)fac[i] = fac[i-1]*i%mod;
	ifac[mxn-1] = inv(fac[mxn-1]);
	for(int i = mxn-2;i>=0;i--)ifac[i] = ifac[i+1]*(i+1)%mod;
	for(int i = 0;i<mxn;i++)assert(fac[i]*ifac[i]%mod == 1);
	for(int i = 0;i<=N;i++){
		a[i] = pw(i,N)*ifac[i]%mod;
		b[i] = ifac[i]*(i&1?1:mod-1)%mod;
	}
	for(int i = 0;i<=N;i++)cerr<<a[i]<<',';cerr<<endl;
	T(a,mxn,0);
	T(b,mxn,0);
	for(int i = 0;i<mxn;i++)a[i] = 1ll*a[i]*b[i]%mod;
	T(a,mxn,1);
	for(int i = 0;i<=N;i++)cout<<a[i]<<' ';return 0;
}
