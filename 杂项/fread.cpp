char buf[100000], *p1 = buf, *p2 = buf;
inline char nc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline bool read(int &x) {
    char c = nc(); x = 0;
    if (c == EOF) return false;
    for (; !isdigit(c); c = nc());
    for (; isdigit(c); x = x * 10 + c - '0', c = nc());
    return true;
}