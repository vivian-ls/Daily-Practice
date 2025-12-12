constexpr int P = 998244353;

class Matrix {
private:
	int size_;
	std::vector<std::vector<int>> mat;

public:
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
