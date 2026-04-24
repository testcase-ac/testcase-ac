#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> set_l;
typedef tree<int,null_type,greater<int>,rb_tree_tag,tree_order_statistics_node_update> set_r;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	set_l lset;
	set_r rset;
	int lbnd = n/2, rbnd = (n+3)/2, middle = (n&1 ? (n+1)/2 : 0);
	for(int i=1; i<=lbnd; i++)
		lset.insert(i);
	for(int i=rbnd; i<=n; i++)
		rset.insert(i);
	while(m--) {
		int cmd, x;
		cin >> cmd >> x;
		if(cmd == 1) {
			if(x <= lbnd) {
				lset.erase(x);
			} else if(x >= rbnd) {
				rset.erase(x);
			}
			if(x == middle) middle = 0;
			if(middle) {
				if(x <= lbnd) lset.insert(middle), lbnd++;
				else rset.insert(middle), rbnd--;
				middle = 0;
			}
		} else {
			if(x == middle) {
				cout << middle << '\n';
			} else {
				if(x <= lbnd) {
					x--;
					if((int)lset.size() <= x)
						cout << "0\n";
					else
						cout << *lset.find_by_order(x) << '\n';
				} else {
					x = n-x;
					if((int)rset.size() <= x)
						cout << "0\n";
					else
						cout << *rset.find_by_order(x) << '\n';
				}
			}
		}
	}
}
