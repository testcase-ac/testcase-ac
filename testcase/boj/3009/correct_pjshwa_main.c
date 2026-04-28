#include <stdio.h>

int main(){
	int x1, x2, y1, y2, tmp;
	int next_xint_on_third_flag = 0;
	int next_yint_on_third_flag = 0;
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	if(x1 == x2) next_xint_on_third_flag = 1;
	if(y1 == y2) next_yint_on_third_flag = 1;
	if(next_xint_on_third_flag){
		scanf("%d", &x1);
		printf("%d ", x1);
	}
	else{
		scanf("%d", &tmp);
		if(x1 == tmp) printf("%d ", x2);
		else printf("%d ", x1);
	}
	if(next_yint_on_third_flag){
		scanf("%d", &y1);
		printf("%d\n", y1);
	}
	else{
		scanf("%d", &tmp);
		if(y1 == tmp) printf("%d\n", y2);
		else printf("%d\n", y1);
	}
}