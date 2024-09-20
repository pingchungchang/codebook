// dynamic convex hull for dp optimization : line insert & point query
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1ll<<60;

struct Line{
    mutable ll a, b, r = INF; // y=ax+b, r = upper bound
    inline Line(ll a, ll b) : a(a), b(b){}
    inline ll operator()(ll x) const {
        return a*x+b;
    }
    inline bool operator<(const Line &l2) const {
        return a<l2.a;
    }
    inline bool operator<(ll x) const {
        return r<x;
    }
};

struct hull : multiset<Line, less<>>{
    static ll divFloor(ll a, ll b){ // b>=0
        if(!b) return a>0?INF:-INF;
        return (a<0?a-b+1:a)/b;
    }
    inline bool Intersect(iterator x, iterator y){ // update x->r and return whether *y is killed
        if(y==end()){
            x->r = INF;
            return 0;
        }
        return (x->r = divFloor(x->b-y->b, y->a-x->a)) >= y->r;
    }

    inline void Insert(Line l){
        auto z = insert(l), y = z++, x = y;
        while(Intersect(y, z)) z = erase(z); // delete backward
        if(x!=begin() && Intersect(--x, y)) Intersect(x, y = erase(y)); // delete itself
        while((y = x)!=begin() && (--x)->r>=y->r) Intersect(x, erase(y)); // delete forward
    }

    inline ll Query(ll x) const {
       return (*lower_bound(x))(x);
    }
};

hull C;

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N,Q;
	cin>>N>>Q;
	for(int i = 0;i<N;i++){
		int a,b;
		cin>>a>>b;
		C.Insert(Line(a,b));
	}
	while(Q--){
		int t;
		cin>>t;
		if(t == 0){
			ll a,b;
			cin>>a>>b;
			C.insert(Line(a,b));
		}
		else{
			ll p;
			cin>>p;
			cout<<C.Query(p)<<'\n';
		}
	}
	return 0;
}
