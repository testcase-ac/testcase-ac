#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const double EPS=1e-6;
int main(int argc, char* argv[]) {
	registerTestlibCmd(argc,argv);
	int T=inf.readInt(1,10000);
	for(int i=0;i<T;i++) {
		int x1=inf.readInt(-1000,1000);
		int y1=inf.readInt(1,1000);
		int x2=inf.readInt(-1000,1000);
		int y2=inf.readInt(1,1000);
		double user_ans=ouf.readDouble();
		double correct_ans=ans.readDouble();
		double diff=fabs(user_ans-correct_ans);
		if (!(diff<=EPS||diff<=EPS*fabs(correct_ans))) {
			quitf(_wa,"Test case %d: expected %.9f but found %.9f",i+1,correct_ans,user_ans);
		}
	} quitf(_ok,"All test cases passed");
}
