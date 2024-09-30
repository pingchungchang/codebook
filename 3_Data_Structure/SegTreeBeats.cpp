#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll inf = 1e13;
//0-indexed
//range chmin range add range sum,max
struct node{
	ll mx,mxc,smx,tag,sum,mxtag;
	node(){
		mx = mxc = smx = tag = sum = 0;
		mxtag = inf;
	}
};
struct SegTreeBeats{
#define ls now*2+1
#define rs now*2+2
#define mid ((l+r)>>1)
	vector<node> seg;
	int n;
	node pull(node tl,node tr,int l,int m,int r){
		node re;
		re.tag = 0;
		re.smx = -inf;
		re.mx = max(tl.mx+tl.tag,tr.mx+tr.tag);
		re.mxc = tl.mxc*(tl.mx+tl.tag == re.mx)+tr.mxc*(tr.mx+tr.tag == re.mx);
		re.smx = max(tl.smx+tl.tag,tr.smx+tr.tag);
		if(tl.mx+tl.tag != re.mx)re.smx = max(tl.mx+tl.tag,re.smx);
		if(tr.mx+tr.tag != re.mx)re.smx = max(tr.mx+tr.tag,re.smx);
		re.sum = tl.sum+tr.sum+tl.tag*(m-l+1)+tr.tag*(r-m);
		return re;
	}
	void push(int now,int l,int r){
		seg[now].mx += seg[now].tag;
		seg[now].smx += seg[now].tag;
		seg[now].sum += seg[now].tag*(r-l+1);
		seg[now].tag = 0;
		if(l == r)return;
		seg[ls].tag += seg[now].tag;
		seg[rs].tag += seg[now].tag;
		return;
	}
	void build(int now,int l,int r){
		if(l>r)return;
		if(l == r){
			seg[now].smx = -inf,seg[now].mxc = 1;
			return;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		seg[now] = pull(seg[ls],seg[rs],l,mid,r);
	}
	void modify(int now,int l,int r,int s,int e,ll v,int tp){
		if(l>=s&&e>=r){
			if(tp == 1){
				seg[now].tag += v;
				return;
			}
			push(now,l,r);
			if(seg[now].mx<=v)return;
			if(l == r){
				seg[now].mx = min(seg[now].mx,v);
				seg[now].tag = 0;
				return;
			}
			if(seg[now].smx<v){
				seg[now].sum += (seg[now].mx-v)*seg[now].mxc;
				seg[now].mx = v;
				return;
			}
			modify(ls,l,mid,s,e,v,tp);
			modify(rs,mid+1,r,s,e,v,tp);
			seg[now] = pull(seg[ls],seg[rs],l,mid,r);
		}
		if(mid>=s)modify(ls,l,mid,s,e,v,tp);
		if(mid<e)modify(rs,mid+1,r,s,e,v,tp);
		seg[now] = pull(seg[ls],seg[rs],l,mid,r);
	}
	node getval(int now,int l,int r,int s,int e){
		if(l>=s&&e>=r)return seg[now];
		push(now,l,r);
		if(mid>=e)return getval(ls,l,mid,s,e);
		else if(mid<s)return getval(rs,mid+1,r,s,e);
		else return pull(getval(ls,l,mid,s,e),getval(rs,mid+1,r,s,e),max(l,s),mid,min(r,e));
	}
	void chmin(int l,int r,int v){
		modify(0,0,n-1,l,r,v,0);
	}
	void range_add(int l,int r,int v){
		modify(0,0,n-1,l,r,v,1);
	}
	ll getsum(int l,int r){
		node re = getval(0,0,n-1,l,r);
		return re.sum+re.tag*(r-l+1);
	}
	ll getmax(int l,int r){
		node re = getval(0,0,n-1,l,r);
		return re.mx+re.tag;
	}
	SegTreeBeats(int _n = 0){
		n = _n;
		seg = vector<node>(n*4,node());
		build(0,0,n-1);
	}
#undef ls
#undef rs
#undef mid
};

SegTreeBeats D;
int N,Q;

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>N>>Q;
	D = SegTreeBeats(N);
	for(int i = 0;i<N;i++){
		int k;
		cin>>k;
		D.range_add(i,i,k);
	}
	while(Q--){
		int t,l,r;
		cin>>t>>l>>r;
		l--,r--;
		if(t == 1){
			int k;
			cin>>k;
			D.chmin(l,r,k);
		}
		else if(t == 2){
			int k;
			cin>>k;
			D.range_add(l,r,k);
		}
		else if(t == 4)cout<<D.getmax(l,r)<<'\n';
		else cout<<D.getsum(l,r)<<'\n';
	}
	return 0;
}
