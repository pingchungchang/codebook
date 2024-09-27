#include <bits/stdc++.h>
using namespace std;

template<typename T = int>
struct Pt{
	T x,y;
	Pt (T xx = T(),T yy = T()):x(xx),y(yy){}
	Pt operator+(Pt b)const{return Pt(x+b.x,y+b.y);}
	Pt operator-(Pt b)const{return Pt(x-b.x,y-b.y);}
	T operator*(Pt b)const{return x*b.x+y*b.y;}
	T operator^(Pt b)const{return x*b.y-y*b.x;}
	T operator/(Pt b)const{return x*b.y-y*b.x;}
	bool operator<(Pt b)const{return x == b.x?y<b.y:x<b.x;}
	bool operator==(Pt b)const{return x== b.x&&y == b.y;}
	friend int dir(Pt a,Pt b){//returns sign(a ^ b)
		auto re = a ^ b;
		return re<0?-1:re>0?1:0;
	}
	friend bool onseg(Pt x,Pt s,Pt e){
		if(((e-x)^(s-x)) != 0)return false;
		else if((s-x)*(e-x)>0)return false;
		return true;
	}
	friend int intersect(Pt s1,Pt e1,Pt s2,Pt e2){//returns 0 if doesn't intersect,1 if intersect,2 if on line
		if(onseg(s1,s2,e2)||onseg(e1,s2,e2)||onseg(s2,s1,e1)||onseg(e2,s1,e1))return 2;
		if(dir(s1-s2,e2-s2)*dir(e1-s2,e2-s2)<0&&dir(s2-s1,e1-s1)*dir(e2-s1,e1-s1)<0)return 1;
		return 0;
	}
};

struct ConvexHull{//returns in clockwise direction
	template <typename T>
	vector<Pt<T>> solve(vector<Pt<T>> v){
		sort(v.begin(),v.end());
		v.resize(unique(v.begin(),v.end())-v.begin());
		vector<Pt<T>> u,d;
		for(auto &i:v){
			while(u.size()>1&&((i-u.end()[-1])^(u.end()[-2]-u.end()[-1]))>=0)u.pop_back();
			while(d.size()>1&&((i-d.end()[-1])^(d.end()[-2]-d.end()[-1]))<=0)d.pop_back();
			u.push_back(i);
			d.push_back(i);
		}
		for(int i = 1;i+1<d.size();i++)u.push_back(d.end()[-1-i]);
		return u;
	}
};

#define Pt Pt<long long>

ConvexHull C;

void solve(){
	int N;
	cin>>N;
	vector<Pt> v;
	for(int i = 0;i<N;i++){
		Pt tmp;
		cin>>tmp.x>>tmp.y;
		v.push_back(tmp);
	}
	auto ans = C.solve(v);
	reverse(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(auto &i:ans)cout<<i.x<<' '<<i.y<<'\n';
	return;
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--)solve();
}
