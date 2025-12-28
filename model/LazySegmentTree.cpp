template <class Info, class Tag>
class LazySegmentTree { // 1 - index
public:
	template <class Container>
	LazySegmentTree(const Container& c) : n(c.size() - 1), info((n + 1) << 2, Info()), tag((n + 1) << 2, Tag()) {
		auto build = [&](auto&& build, int l, int r, int x) -> void {
			if (l == r) {
				info[x] = Info(l, c[l]);
				return;
			}
			int mid = (l + r) >> 1;
			build(build, l, mid, x << 1);
			build(build, mid + 1, r, x << 1 | 1);
			pushup(x);
		};

		if (n >= 1) {
			build(build, 1, n, 1);
		}
	}

	void rangeApply(int l, int r, const Tag& t) {
		RangeApply(l, r, t, 1, n, 1);
	}

	Info rangeQuery(int l, int r) {
		return RangeQuery(l, r, 1, n, 1);
	}

	void Modify(int p, const Tag& t) {
		RangeApply(p, p, t, 1, n, 1);
	}

	template<class F>
	int findFirst(int l, int r, F&& f) {
		return findFirst(l, r, 1, n, 1, f);
	}

	template<class F>
	int findLast(int l, int r, F&& f) {
		return findLast(l, r, 1, n, 1, f);
	}

private:
	int n;
	std::vector<Info> info;
	std::vector<Tag> tag;

	void pushup(int x) {
		info[x] = info[x << 1] + info[x << 1 | 1];
	}

	void pushdown(int l, int r, int x) {
		info[x << 1].Apply(tag[x]);
		info[x << 1 | 1].Apply(tag[x]);
		tag[x << 1].Apply(tag[x]);
		tag[x << 1 | 1].Apply(tag[x]);
		tag[x].status = false;
	}

	void RangeApply(int l, int r, const Tag& t, int s, int e, int x) {
		if (s >= l && e <= r) {
			info[x].Apply(t);
			tag[x].Apply(t);
			return;
		}
		pushdown(s, e, x);
		int mid = (s + e) >> 1;
		if (mid >= l) {
			RangeApply(l, r, t, s, mid, x << 1);
		}
		if (mid + 1 <= r) {
			RangeApply(l, r, t, mid + 1, e, x << 1 | 1);
		}
		pushup(x);
	}

	Info RangeQuery(int l, int r, int s, int e, int x) {
		if (s >= l && e <= r) {
			return info[x];
		}
		pushdown(s, e, x);
		Info ans = Info();
		int mid = (s + e) >> 1;
		if (mid >= l) {
			ans = (ans + RangeQuery(l, r, s, mid, x << 1));
		}
		if (mid + 1 <= r) {
			ans = (ans + RangeQuery(l, r, mid + 1, e, x << 1 | 1));
		}
		return ans;
	}

	template<class F>
	int findFirst(int l, int r, int s, int e, int x, F&& f) {
		if (e < l || s > r) {
			return -1;
		}
		if (s >= l && e <= r && f(info[x]) == false) {
			return -1;
		}
		if (s == e) {
			return s;
		}
		pushdown(s, e, x);
		int mid = (s + e) >> 1;
		int res = findFirst(l, r, s, mid, x << 1, f);
		if (res == -1) {
			res = findFirst(l, r, mid + 1, e, x << 1 | 1, f);
		}

		return res;
	}

	template<class F>
	int findLast(int l, int r, int s, int e, int x, F&& f) {
		if (e < l || s > r) {
			return -1;
		}
		if (s >= l && e <= r && f(info[x]) == false) {
			return -1;
		}
		if (s == e) {
			return s;
		}
		pushdown(s, e, x);
		int mid = (s + e) >> 1;
		int res = findLast(l, r, mid + 1, e, x << 1 | 1, f);
		if (res == -1) {
			res = findLast(l, r, s, mid, x << 1, f);
		}

		return res;
	}
};



struct Tag {
	i64 val;
	bool status = false;
	
	Tag() : val(0) {}
	Tag(i64 v) : val(v), status(true) {}
	
	void Apply(const Tag& t) {
		if (!t.status) {
			return;
		}
		if (!status) {
			(*this) = t;
			return;
		} 
		val += t.val;
	}
};

struct Info {
	int l, r;
	i64 val;
	
	Info() : l(0), r(0), val(0) {}
	Info(int x, i64 v) : l(x), r(x), val(v) {}
	
	void Apply(const Tag& t) {
		if (!t.status) {
			return;
		}
		val += t.val * (r - l + 1);
	}
	
	friend Info operator+(const Info& info1, const Info& info2) {
		if (info1.l == 0) {
			return info2;
		}
		Info res;
		res.l = info1.l;
		res.r = info2.r;
		res.val = info1.val + info2.val;
		
		return res;
	}
};

LazySegmentTree seg(vector<int>(n + 1));


