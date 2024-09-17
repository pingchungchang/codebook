struct RoundSquareTree{
	//0-indexed
	//returns a forest if the graph is not connected
	vector<vector<int>> g;
	vector<vector<int>> groups;
	vector<vector<int>> tr;
	vector<int> idx,low,st;
	int cnt,gcnt;
	int n;
	RoundSquareTree(int _n = 0){
		cnt = gcnt = 0;
		n = _n;
		g = vector<vector<int>>(n);
	}
	void add_edge(int a,int b){//adds bidirectional edges
		g[a].push_back(b);
		g[b].push_back(a);
	}
	void dfs(int now){
		idx[now] = low[now] = cnt++;
		st.push_back(now);
		for(auto nxt:g[now]){
			if(idx[nxt] == -1){
				dfs(nxt);
				low[now] = min(low[now],low[nxt]);
				if(low[nxt] == idx[now]){
					int id = -1;
					tr.push_back(vector<int>());
					while(id != nxt){
						id = st.back();st.pop_back();
						groups[id].push_back(gcnt);
						tr[id].push_back(gcnt+n);
						tr[gcnt+n].push_back(id);
					}
					groups[now].push_back(gcnt);
					tr[now].push_back(gcnt+n);
					tr[gcnt+n].push_back(now);
					gcnt++;
				}
			}
			else idx[now] = min(idx[now],idx[nxt]);
		}
		return;
	}
	vector<vector<int>> solve(){//returns the tree (round vertices numbered [0,n))
		idx = low = vector<int>(n,-1);
		tr = vector<vector<int>>(n);
		for(int i = 0;i<n;i++){
			if(idx[i] == -1)dfs(i);
		}
		return tr;
	}
};
