struct Point3 be, en; // kuangbin
double ang(Point3 v1, Point3 v2) {
    return acos((v1 * v2) / (v1.len() * v2.len()));
}
struct Line3; // kuangbin

//点p绕向量ov旋转ang角度，旋转方向是向量ov叉乘向量op
Point3 rotate3(Point3 p, Point3 v, double angle) {
    double ret[3][3], a[3];
    v = v / v.len();
    ret[0][0] = (1.0 - cos(angle)) * v.x * v.x + cos(angle);
    ret[0][1] = (1.0 - cos(angle)) * v.x * v.y - sin(angle) * v.z;
    ret[0][2] = (1.0 - cos(angle)) * v.x * v.z + sin(angle) * v.y;
    ret[1][0] = (1.0 - cos(angle)) * v.y * v.x + sin(angle) * v.z;
    ret[1][1] = (1.0 - cos(angle)) * v.y * v.y + cos(angle);
    ret[1][2] = (1.0 - cos(angle)) * v.y * v.z - sin(angle) * v.x;
    ret[2][0] = (1.0 - cos(angle)) * v.z * v.x - sin(angle) * v.y;
    ret[2][1] = (1.0 - cos(angle)) * v.z * v.y + sin(angle) * v.x;
    ret[2][2] = (1.0 - cos(angle)) * v.z * v.z + cos(angle);
    for (int i = 0; i < 3; i++) a[i] = ret[i][0] * p.x + ret[i][1] * p.y + ret[i][2] * p.z;
    return Point3(a[0], a[1], a[2]);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%lf%lf%lf", &be.x, &be.y, &be.z);    // 起始点
        scanf("%lf%lf%lf", &en.x, &en.y, &en.z);    // 目标点
        Point3 face = Point3(1, 0, 0), head = Point3(0, 0, 1);
        int m; char opt[3]; scanf("%d", &m);
        double res = 1.0 * inf;
        while (m--) {
            double d, t; scanf("%lf%s%lf", &d, opt, &t);
            double dx = d * cos(ang(Point3(1, 0, 0), face)), dy = d * cos(ang(Point3(0, 1, 0), face)), dz =
                    d * cos(ang(Point3(0, 0, 1), face));
            Point3 nbe = be + Point3(dx, dy, dz);
            Line3 lane = Line3(be, nbe);

            res = min(res, lane.dispointtoseg(en));
            if (opt[0] == 'U') { // 抬头
                Point3 v = face ^head;
                face = rotate3(face, v, t);
                head = rotate3(head, v, t);
            } else if (opt[0] == 'D') { // 低头
                Point3 v = head ^face;
                face = rotate3(face, v, t);
                head = rotate3(head, v, t);
            } else if (opt[0] == 'L') { // 左转
                face = rotate3(face, head, t);
            } else if (opt[0] == 'R') { // 后转
                Point3 v = head * (-1);
                face = rotate3(face, v, t);
            }
            be = nbe;
        }
        printf("%.2f\n", res);
    }
}
