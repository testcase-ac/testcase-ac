class PanCakeCookie{
private:
	int w, h;
	int x, y, t;
	int score;
	int maxC, curC;
	int u, d;
public:
	PanCakeCookie(int w, int h, int maxC, int u, int d);

	int getX();
	int getY();
	int getU();
	int getD();
	int getScore();
	int getC();

	void reset();
	void setU(int x);
	void setD(int x);
	void setC(int x);
	void setT(int t);  
};

PanCakeCookie::PanCakeCookie(int w, int h, int maxC, int u, int d) : w(w), h(h), maxC(maxC), u(u), d(d) {
	reset();
}

int PanCakeCookie::getX(){ return this->x;}
int PanCakeCookie::getY(){ return this->y;}
int PanCakeCookie::getU(){ return this->u;}
int PanCakeCookie::getD(){ return this->d;}
int PanCakeCookie::getScore(){ return this->score;}
int PanCakeCookie::getC(){ return this->curC;}

void PanCakeCookie::reset(){
	x = y = score = 0;
	curC = maxC;
}

void PanCakeCookie::setU(int x){
	if (x < 1 || x > 1000) return;
	u = x;
	reset();
}

void PanCakeCookie::setD(int x){
	if (x < 1 || x > 1000) return;
	d = x;
	reset();
}

void PanCakeCookie::setC(int x){
	if (x < 1 || x > 1000) return;
	maxC = x;
	reset();
}

int min(int a, int b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void PanCakeCookie::setT(int t){
	if (t < 0 || t >= w) return;

	reset();
	for (int i = 1; i <= t; i++) {
		x++;
		if (curC) {
			curC--;
			y = min(h, y + u);
		}
		else {
			curC++;
			y = max(0, y - d);
		}
		score += y;
	}
}
