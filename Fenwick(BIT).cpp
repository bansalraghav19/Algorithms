template<typename T>
struct Fenwick {
  vector<T> BIT;
  int N;
  void init(int N) {
    this->N = N;
    BIT.resize(this->N + 10);
  }
  void modify(int r, T value) {
    for (int i = r; i <= N; i = i | (i + 1)) {
      BIT[i] += value;
    }
  }
  T query(int r) {
    T ans = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
      ans += BIT[i];
    }
    return ans;
  }
};
