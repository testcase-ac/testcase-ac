#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(1,100);
	int m=rnd.next(1,min(100,1000/n));
	cout<<n<<' '<<m<<'\n';
	for(int i=0;i<n;i++) {
	    for(int j=0;j<m;j++) cout<<(rnd.next(0,1)?'O':'X');
	    cout<<'\n';
	}
}
