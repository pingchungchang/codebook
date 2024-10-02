#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt,sse4")

#define ll long long
const int SZ = 2e5+10;
//1-indexed,0 used for nullptr
struct Splay{
#define ls ch[now][0]
#define rs ch[now][1]
	int val[SZ];
	ll sum[SZ];
	int ch[SZ][2],fa[SZ],cnt,rev[SZ],sz[SZ];
	void pull(int now){
		if(!now)return;
		sum[now] = sum[ls]+sum[rs]+val[now];
		sz[now] = sz[ls]+sz[rs]+1;
		return;
	}
	void push(int now){
		if(!now)return;
		if(rev[now]){
			swap(ls,rs);
			rev[ls] ^= 1;
			rev[rs] ^= 1;
			rev[now] = 0;
		}
		pull(now);
		return;
	}
	Splay(){
		fill(sz+1,sz+SZ,1);
		return;
	}
	int newnode(){
		return ++cnt;
	}
	int dir(int now){//is ls or rs
		push(fa[now]);
		return ch[fa[now]][1] == now;
	}
	void rot(int now){
		assert(now);
		int p = fa[now];
		int g = fa[p];
		push(p);
		push(now);
		int d = dir(now);
		ch[g][dir(p)] = now;
		fa[ch[now][d^1]] = p;
		ch[p][d] = ch[now][d^1];
		fa[now] = g;
		fa[p] = now;
		ch[now][d^1] = p;
		pull(p);
		pull(now);
		return;
	}
	void splay(int now){
		if(!now)return;
		while(fa[now]){
			if(fa[fa[now]]){
				if(dir(now) == dir(fa[now]))rot(fa[now]);
				else rot(now);
			}
			rot(now);
		}
		return;
	}
	int get_sz(int now,int tar){
		push(now);
		while(now&&sz[ls]+1 != tar){
			if(sz[ls]>=tar)now = ls;
			else{
				tar -= sz[ls]+1;
				now = rs;
			}
			push(now);
		}
		//assert(now);
		return now;
	}
	void merge(int a,int b){
		if(!a||!b)return;
		splay(a);splay(b);
		a = get_sz(a,sz[a]);
		b = get_sz(b,1);
		splay(a);splay(b);
		ch[a][1] = b;
		fa[b] = a;
		pull(a);
		return;
	}
	pair<int,int> split(int a,int tar){
		splay(a);
		if(!tar)return make_pair(0,a);
		int b = get_sz(a,tar);
		splay(b);
		pair<int,int> re;
		re.first = b;
		re.second = ch[b][1];
		fa[ch[b][1]] = 0;
		ch[b][1] = 0;
		pull(b);
		return re;
	}
	void dfs(int now){
		if(!now)return;
		push(now);
		dfs(ls);
		cout<<char(val[now]);
		dfs(rs);
		return;
	}
#undef ls
#undef rs
};

Splay T;

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N,Q;
	cin>>N>>Q;
	for(int i = 1;i<=N;i++){
		int c;
		cin>>c;
		T.val[i] = c;
		T.sum[i] = T.val[i];
		if(i != 1)T.merge(1,i);
	}
	while(Q--){
		int t,l,r;
		cin>>t>>l>>r;
		l++;
		if(l>r){
			if(t)cout<<"0\n";
			continue;
		}
		auto [t1,t2] = T.split(1,r);
		auto [t3,t4] = T.split(t1,l-1);
		T.splay(t4);
		if(t == 0){
			T.rev[t4] ^= 1;
		}
		else{
			cout<<T.sum[t4]<<'\n';
		}
		T.merge(t3,t4);
		T.merge(t4,t2);

	}
}
