struct point {
	double x,y;
	point(double x = 0,double y = 0) : x(x), y(y) {}
};
int sig(double a) {
	return (a < -eps ? -1 : (a > eps));
}
//默认 vector 就是 point ,就不 typedef 了
point operator + (point a,point b) { return point(a.x + b.x,a.y + b.y); }
point operator - (point a,point b) { return point(a.x - b.x,a.y - b.y); }
point operator * (point a,double p) { return point(a.x * p,a.y * p); }
point operator / (point a,double p) { return point(a.x / p,a.y / p); }
double operator * (point a,point b) { return a.x * b.x + a.y * b.y; } // 点积
double operator / (point a,point b) { return a.x * b.y - a.y * b.x; } // 叉积 b 在 a 左边叉积
> 0
bool operator == (const point &a,const point &b) {
	return !sig(a.x - b.x) && !sig(a.y - b.y);
  }
double length(point a) { return sqrt(a * a); } // 求向量长度
double angle(point a,point b) { return acos(a * b / length(a) / length(b)); } // 两向量夹角
(弧度)
//向量旋转|| 旋转坐标系
point rotate(point a,double rad) {
	return point(a.x * cos(rad) - a.y * sin(rad),a.x * sin(rad) + a.y * cos(rad));
} // cos - sin, sin + cos.... 好记
//----------------直线相关-----------------
// 直线的参数法表示:
struct line {
	point p,v; // 直线上任意一点 x 满足 x = p + v * t;
};
// 直线求交
point cross_line(line a,line b) {point u = a.p - b.p;
	if (!sig(a.v / b.v)) return point(INF,INF);
	double t = (b.v / u) / (a.v / b.v);
	return a.p + a.v * t;
}
// 点到直线的距离 -> 叉积得到的有向面积除以底
double dis_dot_line(point p,line A) {
	point a = A.p,b = A.p + A.v;
	point v1 = b - a, v2 = p - a;
	return fabs((v1 / v2) / length(v1));
}
// 点到线段的距离 分三种情况考虑
double dis_dot_seg(point p,point a,point b) {
	if (a == b) return length(p - a);
	point v1 = b - a,v2 = p - a,v3 = p - b;
	if (sig(v1 * v2) < 0) return length(v2);
	else if (sig(v1 * v2) > 0) return length(v3);
	else return fabs((v1 / v2) / length(v1));
}
// 点在直线上的投影点 列方程求解
point dot_projection(point a,line b) {
	return b.p + b.v * ((b.v * (a - b.p)) / (b.v * b.v));
}
//计算多边形的有向面积-- 虽替!
double count_s(point *p,int n) {
	double ans = 0;
	for (int i = 1; i < n; i++) ans += p[i] / p[i + 1];
	ans += p[n] / p[1];
	return fabs(ans / 2.0);
}
