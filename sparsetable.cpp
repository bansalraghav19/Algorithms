using FUN = function<int(int, int)>;
template<typename T>
struct sparse_table {
  const int level = 19;
  int N;
  using Node = array<int, 3>;
  vector<int> v;
  vector<int> floorlogs;
  vector<vector<Node>> table;
  T func;
  sparse_table(T lambda) {
    func = lambda;
  }
  void init(vector<int> &v) {
    this->N = (int)v.size() - 1LL;
    this->v = v;
    floorlogs.resize(this->N + 1);
    table.resize(this->N + 1, vector<Node>(level + 1));
    precompute();
    Modify();
  }
  void precompute() {
    table[1][0][0] = table[1][0][1] = table[1][0][2] = v[1];
    for (int i = 2; i <= N; i++) {
      table[i][0][0] = table[i][0][1] = table[i][0][2] = v[i];
      floorlogs[i] = floorlogs[i - 1] + !(i & (i - 1));
    }
  }
  void Modify() {
    for (int i = 1; i <= level; i++) {
      for (int j = 1; j + (1LL << i) - 1 <= N; j++) {
        table[j][i][0] = func(table[j][i - 1][0], table[j + (1LL << (i - 1))][i - 1][0]);
      }
    }
  }
  int Query(int l, int r) {
    int msb = floorlogs[r - l + 1];
    return func(table[l][msb][0], table[r - (1LL << msb) + 1][msb][0]);
  }
};
