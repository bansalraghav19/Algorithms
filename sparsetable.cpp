using FUN = function<int(int, int)>;
template<typename T>
struct sparse_table {
  const int level = 19;
  int N;
  vector<int> v;
  vector<int> floorlogs;
  vector<vector<int>> table;
  T func;
  sparse_table(T lambda) {
    func = lambda;
  }
  void init(vector<int> &v) {
    this->N = (int)v.size() - 1LL;
    this->v = v;
    floorlogs.resize(this->N + 1);
    table.resize(this->N + 1, vector<int>(level + 1));
    precompute();
    Modify();
  }
  void precompute() {
    for (int i = 1; i <= N; i++) {
      table[i][0] = v[i];
      floorlogs[i] = floorlogs[i - 1] + !(!(i - 1) or i & (i - 1));
    }
  }
  void Modify() {
    for (int i = 1; i <= level; i++) {
      for (int j = 1; j + (1LL << i) - 1 <= N; j++) {
        table[j][i] = func(table[j][i - 1], table[j + (1LL << (i - 1))][i - 1]);
      }
    }
  }
  int Query(int l, int r) {
    int msb = floorlogs[r - l + 1];
    return func(table[l][msb], table[r - (1LL << msb) + 1][msb]);
  }
};
