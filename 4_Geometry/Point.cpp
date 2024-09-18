template<typename T = int>//可以直接改=double之類的
struct Pt{
	T x,y;
	Pt (T xx = T(),T yy = T()):x(xx),y(yy){}
	Pt operator+(Pt b)const{return Pt(x+b.x,y+b.y);}
	Pt operator-(Pt b)const{return Pt(x-b.x,y-b.y);}
	T operator*(Pt b)const{return x*b.x+y*b.y;}
	T operator^(Pt b)const{return x*b.y-y*b.x;}
	T operator/(Pt b)const{return x*b.y-y*b.x;}
	bool operator<(Pt b)const{return x == b.x?y<b.y:x<b.x;}
};

