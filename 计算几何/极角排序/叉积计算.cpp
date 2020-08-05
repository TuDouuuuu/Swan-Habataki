//叉积计算极角（精度高，时间长） 
double compare(point a, point b, point c) {//计算极角 ab × ac
    return (b - a) ^ (c - a);
}
bool cmp(point a, point b) {
    double f = compare(p[pos], a, b);
    if (f == 0)
        return a.x - p[pos].x < b.x - p[pos].x;
    else if (f > 0)
        return true;
    else
        return false;
}
 
/*
//如果取的点不是边角要先按照象限排序 
int Quadrant(point a) //象限排序，注意包含四个坐标轴
{
    if (a.x > 0 && a.y >= 0)
        return 1;
    if (a.x <= 0 && a.y > 0)
        return 2;
    if (a.x < 0 && a.y <= 0)
        return 3;
    if (a.x >= 0 && a.y < 0)
        return 4;
}

bool cmp2(point a, point b) //先象限后极角
{
    if (Quadrant(a) == Quadrant(b)) //返回值就是象限
        return cmp(a, b);
    else
        Quadrant(a) < Quadrant(b);
}
*/ 


