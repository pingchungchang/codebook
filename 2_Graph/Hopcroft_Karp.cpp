//from https://judge.yosupo.jp/submission/175637
struct Hopcroft_Karp{
	vector<int> l, r, a, p; int ans;
	int nl,nr;
	vector<vector<int>> g;
	Hopcroft_Karp(int tl = 0, int tr = 0) : l(tl, -1), r(tr, -1), ans(0), nl(tl), nr(tr),g(nl){}
	void add_edge(int x,int y){//only need to add l to r
		g[x].push_back(y);
	}
	int solve(){
		for (bool match = true; match;) {
			match = false; a.assign(nl, -1); p.assign(nl, -1);
			queue<int> q;
			for (int i = 0; i < nl; i++)
				if (l[i] == -1) q.push(a[i] = p[i] = i);
			while (!q.empty()) {
				int x = q.front(); q.pop();
				if (l[a[x]] != -1) continue;
				for (int y : g[x]) { // or iterate t = g[x]&nvis
					if (r[y] == -1) {
						while (y != -1)
							r[y] = x, swap(l[x], y), x = p[x];
						match = true; ++ans; break;
					} else if (p[r[y]] == -1)
						q.push(y = r[y]), p[y] = x, a[y] = a[x];
				}
			}
		}
		return ans;
	}
};
