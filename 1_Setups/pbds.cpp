#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

int main(){
    ordered_set<int> st;
    st.insert(1);
    st.find_by_order(0);//iterator to 1
    st.order_of_key(1);//returns 0
}

