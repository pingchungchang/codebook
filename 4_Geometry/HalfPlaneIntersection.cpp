#include <bits/stdc++.h>
using namespace std;


using i128 = __int128_t;
#define IM imag
#define RE real
using lld = int64_t;
using llf = long double;
using PT = complex<lld>;
using PF = complex<llf>;
using P = PT;

int sgn(lld x) { return (x > 0) - (x < 0); }
lld cross(P a, P b) { return IM(conj(a) * b); }
int ori(P a, P b, P c) {
  return sgn(cross(b - a, c - a));
}
int quad(P p) {
  return (IM(p) == 0) // use sgn for PF
    ? (RE(p) < 0 ? 3 : 1) : (IM(p) < 0 ? 0 : 2);
}
PF toPF(PT p) { return PF{RE(p), IM(p)}; }
template <typename V> llf area(const V & pt) {
  lld ret = 0; // BE CAREFUL OF TYPE!
  for (int i = 1; i + 1 < (int)pt.size(); i++)
    ret += cross(pt[i] - pt[0], pt[i+1] - pt[0]);
  return ret / 2.0;
}
int argCmp(P a, P b) {
  // returns 0/+-1, starts from theta = -PI
  int qa = quad(a), qb = quad(b);
  if (qa != qb) return sgn(qa - qb);
  return sgn(cross(b, a));
}
struct Line {
  P st, ed, dir;
  Line (P s, P e) : st(s), ed(e), dir(e - s) {}
}; using LN = const Line &;
PF intersect(LN A, LN B) {
  llf t = cross(B.st - A.st, B.dir) /
    llf(cross(A.dir, B.dir));
  return toPF(A.st) + toPF(A.dir) * t; // C^3 / C^2
}
bool cov(LN l, LN A, LN B) {
  i128 u = cross(B.st-A.st, B.dir);
  i128 v = cross(A.dir, B.dir);
  // ori(l.st, l.ed, A.st + A.dir*(u/v)) <= 0?
  i128 x = RE(A.dir) * u + RE(A.st - l.st) * v;
  i128 y = IM(A.dir) * u + IM(A.st - l.st) * v;
  return sgn(x*IM(l.dir) - y*RE(l.dir)) * sgn(v) >= 0;
} // x, y are C^3, also sgn<i128> is needed
bool operator<(LN a, LN b) {
  if (int c = argCmp(a.dir, b.dir)) return c == -1;
  return ori(a.st, a.ed, b.st) < 0;
}
// cross(pt-line.st, line.dir)<=0 <-> pt in half plane
// the half plane is the LHS when going from st to ed
llf HPI(vector<Line> &q) {
  sort(q.begin(), q.end());
  int n = (int)q.size(), l = 0, r = -1;
  for (int i = 0; i < n; i++) {
    if (i && !argCmp(q[i].dir, q[i-1].dir)) continue;
    while (l < r && cov(q[i], q[r-1], q[r])) --r;
    while (l < r && cov(q[i], q[l], q[l+1])) ++l;
    q[++r] = q[i];
  }
  while (l < r && cov(q[l], q[r-1], q[r])) --r;
  while (l < r && cov(q[r], q[l], q[l+1])) ++l;
  n = r - l + 1; // q[l .. r] are the lines
  if (n <= 2 || !argCmp(q[l].dir, q[r].dir)) return 0;
  vector<PF> pt(n);
  for (int i = 0; i < n; i++)
    pt[i] = intersect(q[i+l], q[(i+1)%n+l]);
  return area(pt);
} // test @ 2020 Nordic NCPC : BigBrother
