struct sparse_table {
  int N, level;
  using Node = array<int, 3>;
  vector<int> v;
  vector<int> floorlogs;
  vector<vector<Node>> table;
  void init(vector<int> &v) {
    this->N = (int)v.size() - 1LL;
    this->v = v;
    floorlogs.resize(this->N + 1);
    table.resize(this->N + 1, vector<Node>(level + 1));
    precompute();
    level = floorlogs[this->N] + 1;
  }
  void precompute() {
    table[1][0][0] = table[1][0][1] = table[1][0][2] = v[1];
    for (int i = 2; i <= N; i++) {
      table[i][0][0] = table[i][0][1] = table[i][0][2] = v[i];
      floorlogs[i] = floorlogs[i - 1] + !(i & (i - 1));
    }
  }
  void precomputemax() {
    for (int i = 1; i <= level; i++) {
      for (int j = 1; j + (1LL << i) - 1 <= N; j++) {
        table[j][i][0] = max(table[j][i - 1][0], table[j + (1LL << (i - 1))][i - 1][0]);
      }
    }
  }
  void precomputemin() {
    for (int i = 1; i <= level; i++) {
      for (int j = 1; j + (1LL << i) - 1 <= N; j++) {
        table[j][i][1] = min(table[j][i - 1][1], table[j + (1LL << (i - 1))][i - 1][1]);
      }
    }
  }
  void precomputegcd() {
    for (int i = 1; i <= level; i++) {
      for (int j = 1; j + (1LL << i) - 1 <= N; j++) {
        table[j][i][2] = __gcd(table[j][i - 1][2], table[j + (1LL << (i - 1))][i - 1][2]);
      }
    }
  }
  int getmax(int l, int r) {
    int msb = floorlogs[r - l + 1];
    return max(table[l][msb][0], table[r - (1LL << msb) + 1][msb][0]);
  }
  int getmin(int l, int r) {
    int msb = floorlogs[r - l + 1];
    return min(table[l][msb][1], table[r - (1LL << msb) + 1][msb][1]);
  }
  int getgcd(int l, int r) {
    int msb = floorlogs[r - l + 1];
    return __gcd(table[l][msb][2], table[r - (1LL << msb) + 1][msb][2]);
  }
};
