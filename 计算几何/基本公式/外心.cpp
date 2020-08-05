inline point waixin(const point& a, const point& b, const point& c) {
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) * 0.5;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) * 0.5;
    double d = a1 * b2 - a2 * b1;
    point ans;
    ans.x = a.x + (c1 * b2 - c2 * b1) / d;
    ans.y = a.y + (a1 * c2 - a2 * c1) / d;
    return ans;
}

