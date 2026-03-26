constexpr int P = 998244353;

class Matrix {
private:
	int sz;
	vector<vector<int>> mat;

public:
	Matrix(int n, int a = 0) : sz(n), mat(n, vector<int>(n, a)) {} // 单行矩阵

	Matrix(const vector<vector<int>>& a) : sz(a.size()), mat(a) {} // 一般二维矩阵

    Matrix(const Matrix& m) : sz(m.size()), mat(m.mat) {}

	int size() const {
		return sz;
	}

	Matrix operator*(const Matrix& m) {
		Matrix tmp(sz);
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				for (int k = 0; k < sz; k++) {
					tmp.mat[i][j] = (tmp.mat[i][j] + (mat[i][k] * m.mat[k][j] % P + P) + P) % P;
                    // + P 处理出现负数取模的情况
				}
			}
		}
		return tmp;
	}

	void operator*=(const Matrix& m) {(*this) = (*this) * m;}
    // 重载括号便于访问，同时支持修改
	int& operator()(int i, int j) {return mat[i][j];}
};
