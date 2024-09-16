#ifdef MIKU
string dbmc = "\033[1;38;2;57;197;187m", dbrs = \033[0m;
#define debug(x...) cout << dbmc << "[" << #x << "] : ", dout(x)
void dout() { cout << dbrs << endl; }
template <typename T, typename ...U>
void dout(T t, U ...u) { cout << t << sizeof...(u) ? ", " : ""; dout(u...); }
#else
#define debug(...) 39
#endif

int main(){
    int a = 49;
    char c = '8';
    debug(a);// outputs "[a] : 49"
    debug(a, c); // outputs "[a, c] : 49, 8"
    debug("PCCORZ"); // outputs "["PCCORZ"] : PCCORZ"
    debug(); // outputs "[] : "
}

