template<class T>
struct FWHT {
  void fhwr_or(vector<T> &v, bool invert) {
    const int n = (int)v.size();
    for (int s = 2, h = 1; s <= n; s >>= 1, h >>= 1) {
      for (int l = 0; l < n; l += s) {
        for (int i = 0; i < h; i++) {
          v[l + i + h] += invert * v[l + i];
        }
      }
    }
  }
  void fhwr_and(vector<T> &v, bool invert) {
    const int n = (int)v.size();
    for (int s = 2, h = 1; s <= n; s >>= 1, h >>= 1) {
      for (int l = 0; l < n; l += s) {
        for (int i = 0; i < h; i++) {
          v[l + i] += !invert * v[l + i + h];
        }
      }
    }
  }
  void fhwr_xor(vector<T> &v, bool invert) {
    const int n = (int)v.size();
    for (int s = 2, h = 1; s <= n; s >>= 1, h >>= 1) {
      for (int l = 0; l < n; l += s) {
        for (int i = 0; i < h; i++) {
          int t = v[l + h + i];
          v[l + h + i] = v[l + i] - t;
          v[l + i] += t;
          if (invert) {
            v[l + h + i] /= 2;
            v[l + i] /= 2;
          }
        }
      }
    }
  }
};
