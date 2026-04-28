#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>

int main() {
	std::string s;
	std::cin >> s;

	if (s.size() % 2 == 0) {
		std::cout << "No" << std::endl;
		return 0;
	}
	
	std::unordered_set<std::string> searched;
	std::stack<std::string> st;
	st.push(s);

	while (!st.empty()) {
		std::string node = st.top(); st.pop();
		if (node == "ABC") {
			std::cout << "Yes" << std::endl;
			return 0;
		}
		if (node.find("ABC") == -1) continue;

		//ABCをAかBかCに置き換え
		for (int i = 0; i < 3; i++) {
			std::string ss("");
			bool isOk = true;
			for (int j = 0; j < node.size(); j++) {
				if (j + 2 < node.size() && node[j] == 'A' && node[j + 1] == 'B' && node[j + 2] == 'C') {
					ss += 'A' + i;
					j += 2;
				}
				else if (node[j] == 'A' + i) isOk = false; //置換対象の文字が単独でいる状態はありえない(置換されているはずなのでABCのセットに必ずなっている。)
				else ss += node[j];
			}
			if (isOk && searched.find(ss) == searched.end()) {
				st.push(ss);
				searched.insert(ss);
			}
		}
	}
	std::cout << "No" << std::endl;
	return 0;
}
