#### [L. Game of Life](https://codeforces.com/gym/106039/problem/L)

**题意：** 给出一个 $n \times n，n \in [2, 8]$ 的矩阵，1代表当前位置的细胞是活着的，0代表没有活细胞，'#'代表不可生存单元，输出迭代k次后的所有位置的状态，具体的规则如下：如果活细胞周围有奇数个活细胞则死亡，死细胞周围有奇数个活细胞的复活，周围指的是周围8格

这里每次迭代都是线性的，没有乘积或者取min/max等操作，也就是下一次这个位置的状态就是看周围8格加上自己的活细胞数是不是奇数，是奇数才能在下一次迭代中存活

可以用矩阵快速幂优化，具体操作就是把原本 $n \times n$ 的矩阵转化为一个边长为 $n \times n$ 的大矩阵，这个矩阵只有第一行是有数据的，剩下的应该都是0

这就是初始矩阵 $A$ ，假设转移矩阵是 $C$ ，那么最后的结果就是矩阵 $A * C^k$ 的第一行数据

转移矩阵怎么求呢？从第某个元素开始，我们要得到这9个格子中1的数量，只需要把周围八个格子编号对应的这一列的行号设置为1就行

```cpp
constexpr int P = 2;

class Matrix {
public:
	int size_;
	std::vector<std::vector<int>> mat;

	Matrix(int n, int a = 0) : size_(n), mat(n, std::vector<int>(n, a)) {}

	Matrix(const std::vector<std::vector<int>>& a) : size_(a.size()), mat(a) {}

    Matrix(const Matrix& m) : size_(m.size()), mat(m.mat) {}

	int size() const {
		return size_;
	}

	Matrix operator*(const Matrix& m) {
		Matrix tmp(size_);
		for (int i = 0; i < size_; i++) {
			for (int j = 0; j < size_; j++) {
				for (int k = 0; k < size_; k++) {
					tmp.mat[i][j] = (tmp.mat[i][j] + (mat[i][k] * m.mat[k][j] % P + P) + P) % P;
				}
			}
		}
		return tmp;
	}

	void operator*=(const Matrix& m) {(*this) = (*this) * m;}
	int& operator()(int i, int j) {return mat[i][j];}
};

Matrix MatrixModPow(Matrix m, int k) {
	Matrix res(m.size());
	for (int i = 0; i < m.size(); i++) {
		res(i, i) = 1;
	}
	while (k) {
		if (k & 1) res = res * m;
		m = m * m;
		k >>= 1;
	}
	return std::move(res);
}


void solve(){
    int n, k;
	cin >> n >> k;
	auto f = [&](int i, int j) -> int {
		return i * n + j;
	};
	auto df = [&](int x) -> pair<int, int> {
		return make_pair(x / n, x % n);
	};
	vector<vector<int>> a(n, vector<int>(n));
	fore(i, 0, n) {
		string s; cin >> s;
		fore(j, 0, n) a[i][j] = s[j] - '0';
	}
	Matrix A(n * n);
	fore(i, 0, n) fore(j, 0, n) {
		if(a[i][j] == '#' - '0') A.mat[0][f(i, j)] = 0;
		else A.mat[0][f(i, j)] = a[i][j];
	}

	Matrix B(n * n);
	fore(x, 0, n) fore(y, 0, n) {
		if(a[x][y] == '#' - '0') continue;
		B.mat[f(x, y)][f(x, y)] = 1;
		fore(i, 0, 8) {
			int xx = x + ddx[i], yy = y + ddy[i];
			if(xx < 0 || xx >= n || yy < 0 || yy >= n || a[xx][yy] == '#' - '0') continue;
			B.mat[f(x, y)][f(xx, yy)] = 1;
		}
	}

	B = MatrixModPow(B, k);
	Matrix ans = A * B;

	fore(i, 0, n * n) {
		auto[x, y] = df(i);
		if(a[x][y] == '#' - '0') cout << '#';
		else cout << ans.mat[0][i];
		if(y == n - 1) cout << endl;
	}
}
```


#### [F. Chinese Innovation](https://codeforces.com/gym/106039/problem/F)

**题意：** 给出一个有 $n$ 个点的图，其中有 $m$ 条边，传送器类型一共有 $k$ 种，先给出普通的 $m$ 条边(u, v, w)，之后依次对于每个城市给出一个 $t$ 代表该城市传送门数量，之后给出 $t$ 行(u, c) 代表传送门类型是 $u$ ，从这里使用花费是 $c$ ，求出单源最短路

如果没有传送门就是单纯的 dj 算法，但是传送门怎么加进图里面呢？

直接在原本的邻接矩阵上修改对于每种类型的门是 $n^2$ 的，每一个点都要和剩下所有点连边，肯定不行

可以给出一个中转点 n + type ，从 $u \to n + type$ 的边权是 $c$ ，从 $n + type \to v$ 的边权是 0，这样对于每个传送器增加的边数就是常数了

时间复杂度是 $O(n + k + (m + M)log(m + M))$ M不会超过2e5，题目已给出

```cpp
void solve(){
    int n, m, k;
	cin >> n >> m >> k;
	int u, v, w;
	vector<vector<pii>> p(n + k + 1);
	fore(i, 1, m + 1) {
		cin >> u >> v >> w;
		p[u].emplace_back(v, w);
		p[v].emplace_back(u, w);
	}
	int c;
	fore(i, 1, n + 1) {
		int t; cin >> t;
		while(t--) {
			cin >> u >> c;
			p[i].emplace_back(u + n, c);
			p[u + n].emplace_back(i, 0);
		}
	}

	vector<int> dis(n + k + 1, inf);
	vector<int> vis(n + k + 1, false);
	dis[1] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.emplace(0, 1);
	while(!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if(vis[u])continue;
		vis[u] = true;
		for(auto[v, w] : p[u]) {
			if(d + w < dis[v]) {
				dis[v] = d + w;
				pq.emplace(dis[v], v);
			}
		}
	}

	cout << dis[n] << endl;
}
```
