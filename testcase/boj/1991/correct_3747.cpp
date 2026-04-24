#include <iostream>
#include <string.h>

using namespace std;

typedef struct node {
	char data;
	struct node* left;
	struct node* right;
} node;

void preorder(node n) {
	cout << n.data;
	if(n.left != NULL) preorder(*(n.left));
	if(n.right != NULL) preorder(*(n.right));
}
void inorder(node n) {
	if(n.left != NULL) inorder(*(n.left));
	cout << n.data;
	if(n.right != NULL) inorder(*(n.right));
}
void postorder(node n) {
	if(n.left != NULL) postorder(*(n.left));
	if(n.right != NULL) postorder(*(n.right));
	cout << n.data;
}
int main() {
	int n;
	string s1, s2, s3;
	char c1, c2, c3;
	cin >> n;
	node nodeArr[n];
	memset(nodeArr, 0, sizeof(nodeArr));
	for(int i=0; i<n; i++) {
		nodeArr[i].data = 'A' + i;
		cin >> s1 >> s2 >> s3;
		c1 = s1[0];
		c2 = s2[0];
		c3 = s3[0];
		int nodeIndex = c1 - 'A';
		if(c2 != '.')
			nodeArr[nodeIndex].left = (nodeArr + (c2 - 'A'));
		if(c3 != '.')
			nodeArr[nodeIndex].right = (nodeArr + (c3 - 'A'));
	}
	preorder(nodeArr[0]); cout << endl;
	inorder(nodeArr[0]); cout << endl;
	postorder(nodeArr[0]);
}
