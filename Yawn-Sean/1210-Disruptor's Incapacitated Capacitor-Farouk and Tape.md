#### [D. Disruptor's Incapacitated Capacitor](https://codeforces.com/gym/106045/problem/D)

**题意：** 开始有两个平行的圆盘，它们之间的距离是L，现在将其中一个旋转一定角度后圆盘之间距离由于有垂直于平面的绳子牵引会减小，问这个距离是多少

用向量的角度来看，我们可以和容易的表示出这个绳子在旋转之后的向量是怎样的，这个向量的表达式中就有我们需要的答案d，利用向量长度公式解出d即可

```cpp
struct Vec { double x, y, z;};
Vec operator + (Vec a, Vec b) {return (Vec){a.x + b.x, a.y + b.y, a.z + b.z};}

void solve(){
    double r, l, a;
    cin >> r >> l >> a;
    a = a / 180 * pi;
    cout << setprecision(15) << sqrt(l * l + 2 * r * r * (cos(a) - 1)) << endl;
}
```

#### [H. Farouk and Tape](https://codeforces.com/gym/106098/problem/H)

**题意：** 现在有一条很长的丝带，由等长的白色和黑色交替着色，你最多可以询问2000次，每次询问都会给出当前位置丝带的颜色，输出每一段颜色的长度是多少

由于每一段都是等长的，那么假设0位置上是白色，依次询问 $2^0, 2^1, 2^2 ...$ 上的格子的颜色就可以找到一侧第一段黑色出现的位置，(跳过一段黑色是不可能的，即使当前位置是最后一个白色，下一次也一定是黑色，丝带必须等长)

找到第一段黑色之后用二分接着询问就可以确定边界了，两侧边界都确定后结果也就出来了

先倍增再二分，整体复杂度是 $O(logM)$

```cpp
void solve(){
    cout << '?' << ' ' << 0 << endl;
	char a, tmp;
	int l = 0, r;
	cin >> tmp;
	a = tmp;
	fore(i, 1, 60 + 1) {
		cout << '?' << ' ' << fpow(2, i) - 1 << endl;
		cin >> tmp;
		if(tmp != a) {
			r = fpow(2, i) - 1;
			break;
		}
	}
	int ans = 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		cout << '?' << ' ' << mid << endl;
		cin >> tmp;
		if(tmp != a) r = mid;
		else l = mid + 1;
	}
	ans += r - 1;

	r = 0;
	fore(i, 1, 60 + 1) {
		cout << '?' << ' ' << -fpow(2, i) + 1 << endl;
		cin >> tmp;
		if(tmp != a) {
			l = -fpow(2, i) + 1;
			break;
		}
	}
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		cout << '?' << ' ' << mid << endl;
		cin >> tmp;
		if(tmp != a) l = mid;
		else r = mid - 1;
	}
	ans += -r - 1;
	cout << '!' << ' ' << ans << endl;
}
```

