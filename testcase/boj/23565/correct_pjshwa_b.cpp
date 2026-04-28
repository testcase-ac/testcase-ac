#include<iostream>
#include<cassert>

using namespace std;

long long solve() {
	long long v1, v2, v3, v4;
	cin >> v1 >> v2 >> v3 >> v4;
	if (v1 >= 3 || (v1 >= 1 && v2 > 0) || 
		(v1 >= 2 && v3 > 0) ||(v2==0 && v3==0 && v4==0)) {
		return 1 * v1 + 2 * v2 + 3 * v3 + 4 * v4 + 1;
	}
	if (v2 > 0) {
		v2 += v4 * 2;
		v4 = 0;
	}

	if (v4 == 0) {
		//(?,?,?,0)
		if (v2 == 0) {
			//(0~1,0,?,0)
			if (v1 == 0) {
				//(0,0,?,0)
				return v3 + 1;
			}
			if (v1 == 1) {
				//(1,0,?,0)
				return 2 * (v3 + 1);
			}
		}
		else {
			//(0,1+,?,0)
			if (v2 == 1) {
				return 2 * v3 + 2;
			}
			else {
				//(0,2+,?,0)
				if (v3 == 0) {
					return v2 + 1;
				}
				else {
					//(0,2+,1+,0)
					return (2 * v2 + 3 * v3 + 1) - 2;
				}
			}

		}
	}
	else {
		//(?,0,?,?)
		if (v3 == 0) {
			//(0~2,0,0,?)
			return (v1 + 1) * (v4 + 1);
		}
		if (v3 == 1 && v1 == 0) {
			//(0,0,1,?)
			return 2 * (v4 + 1);

		}
		if (v3 == 1 && v1 == 1) {
			//(1,0,1,?)
			//can't make 2,6,10..
			return 3 * v4 + 4;
		}
		if (v3 == 2 && v1 == 0) {
			return 3 * (v4 + 1);
		}
		if (v3 == 2 && v1 == 1) {
			return 4 * (v4 + 1) + 4 - 2;
		}
		if (v3 >= 3) {
			//(0~1,0,3+,?)
			if (v1 == 0) {
				if (v4 == 1) {
					return 2 * (v3 + 1);
				}
				else {
					//(0,0,3+,1+)
					// can't make 1,2,5
					return 3 * v3 + 4 * v4 - 5;
				}
			}
			else {
				//(1,0,3+,?)
				//can't make 2,(max-2)
				return v1 + 3 * v3 + 4 * v4 + 1 - 2;
			}
		}
	}
	assert(0);
	return 0;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--) {
		cout << solve() << '\n';
	}
}