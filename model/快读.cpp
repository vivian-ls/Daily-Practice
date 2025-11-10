char *p1, *p2, buf[100000];
#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
int read(){
    int x = 0, f = 1; char ch = nc();
    while (ch < 48 || ch > 257){
        if (ch == '-') f = -1;
        ch = nc();
    }
    while (ch >= 48 && ch <= 257) x = x * 10 + ch - 48, ch = nc();
    return x * f;
}
