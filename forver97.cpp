const double EPS = 1e-8;
//-------------------------------------------------------------------
// double cmp
int dcmp(double x) { return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }
struct Point {
    double x, y, z;
    Point() { x = y = z = 0; }
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    Point operator+(Point a) { return Point(x + a.x, y + a.y, z + a.z); }
    Point operator-(Point a) { return Point(x - a.x, y - a.y, z - a.z); }
    Point operator*(double k) { return Point(x * k, y * k, z * k); }
    Point operator/(double k) { return Point(x / k, y / k, z / k); }
    double operator*(Point a) { return x * a.x + y * a.y + z * a.z; }  // 点积
    Point operator^(Point a) {
        return Point(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
    }  // 叉积
    double length() { return sqrt(x * x + y * y + z * z); }
};
double Angle(Point a, Point b) { return acos(a * b / a.length() / b.length()); }
Point projection(Point v, Point u) {  // 向量v 在u 上投影
    double scalar = (v * u) / (u * u);
    return u * scalar;
}
Point projection(Point p, Point a, Point b,
                 Point c) {  // 点p 在平面ABC 上的投影
    Point u = (b - a) ^ (c - a), v = p - a;
    double scalar = (v * u) / (u * u);
    return p - (u * scalar);
}
double dist(Point p, Point a, Point b) {  // 点p 到直线ab 的距离
    p = p - a;
    Point proj = projection(p, b - a);
    return sqrt(p * p - proj * proj);
}
//点到线段
double DistanceToSegment(Point p, Point a, Point b) {
    if (a == b) return (p - a).length();
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if (dcmp(v1 * v2) < 0)
        return v2.length();
    else if (dcmp(v1 * v3) > 0)
        return v3.length();
    else
        return (v1 ^ v2).length() / v1.length();
}
double area(Point a, Point b, Point c) {  // 三角形ABC 的面积
    double h = dist(a, b, c);
    return (h * (b - c).length()) / 2;
}
double volume(Point x, Point y, Point z) {  // 三个向量构成的体积
    Point base = Point(y.y * z.z - y.z * z.y, y.z * z.x - y.x * z.z,
                       y.x * z.y - y.y * z.x);
    return fabs(x.x * base.x + x.y * base.y + x.z * base.z) / 3;
}
//-------------------------------------------------------------------
//空间直线
struct Line {
    Point a, b;
};
//空间直线间距离
double LineToLine(Line u, Line v, Point &tmp) {
    tmp = (u.a - u.b) ^ (v.a - v.b);
    return fabs((u.a - v.a) * tmp) / tmp.length();
}
//-------------------------------------------------------------------
//面： 点+法线
//面交线： 两面交线与两面法线均垂直，法线叉积为其方向矢量.
//角平分面： 法向量为两平面法向量相加(内角) 或相减(外角).
struct Plane {
    Point p0, n;  // n:法线
    Plane() {}
    Plane(Point nn, Point pp0) {
        n = nn / nn.length();
        p0 = pp0;
    }
    Plane(Point a, Point b, Point c) {
        Point nn = (b - a) ^ (c - a);
        n = nn / nn.length();
        p0 = a;
    }
};
//角平分面
Plane jpfPlane(Point a1, Point a2, Point b, Point c) {
    Plane p1(a1, b, c), p2(a2, c, b);
    Point temp = p1.n + p2.n;  // 法向量为两平面法向量相加(内角)或相减(外角)
    return Plane(temp ^ (c - b), b);
}
//线面交点取线上任意两点
Point LinePlaneIntersection(Point p1, Point p2, Plane a) {
    Point p0 = a.p0;
    Point n = a.n, v = p2 - p1;
    double t = n * (p0 - p1) / (n * (p2 - p1));  //映射到法向量的比例
    return p1 + v * t;
}
//三面交点
Point PlaneInsertion(Plane a, Plane b, Plane c) {
    //两面交线与两面法线均垂直，法线叉积为其方向矢量
    Point nn = a.n ^ b.n, use = nn ^ a.n;
    Point st = LinePlaneIntersection(a.p0, a.p0 + use, b);  //得交线上一点
    return LinePlaneIntersection(st, st + nn, c);
}
double DistanceToPlane(Point p, Plane a) {
    Point p0 = a.p0, n = a.n;
    return fabs((p - p0) * n / n.length());
}
// 判定四点共面
bool isOnePlane(Point a, Point b, Point c, Point d) {
    double t = (d - a) * ((b - a) ^ (c - a));
    return dcmp(t) == 0;
}
//-------------------------------------------------------------------
//已知3点坐标，求平面ax+by+cz+d=0;
void getPlane(Point p1, Point p2, Point p3, double &a, double &b, double &c,
              double &d) {
    a = ((p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y));
    b = ((p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z));
    c = ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));
    d = (0 - (a * p1.x + b * p1.y + c * p1.z));
}
/*
    题意：给定四点，求是否能够成四面体，若能则求出其内接圆心和半径
    分析：
        是否能构成四面体：
   三点成面的法线和另一点与三点中任一点相连的向量是否垂直？ 四面体内接球 球心：
   任意三个角平分面的交点 半径： 交点到任意面的距离
*/
int main() {
    Point p[4];
    while (~scanf("%lf%lf%lf", &p[0].x, &p[0].y, &p[0].z)) {
        for (int i = 1; i <= 3; i++)
            scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
        if (isOnePlane(p[0], p[1], p[2], p[3])) {
            puts("O O O O");
            continue;
        }
        Plane a = jpfPlane(p[3], p[2], p[1],
                           p[0]),  // 三个角平分面的交点即为圆心
            b = jpfPlane(p[3], p[0], p[1], p[2]),
              c = jpfPlane(p[3], p[1], p[0], p[2]);
        Plane d(p[0], p[1], p[2]);
        Point center = PlaneInsertion(a, b, c);
        double r = DistanceToPlane(center, d);
        printf("%.4f %.4f %.4f %.4f\n", center.x, center.y, center.z, r);
    }
}