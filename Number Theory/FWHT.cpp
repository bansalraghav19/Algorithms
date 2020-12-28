template<class T>
struct FWHT {
  void fhwt_or(vector<T> &A, bool invert) {
    const int n = (int)A.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
      for (int l = 0; l < n; l += s) {
        for (int i = 0; i < h; i++) {
          A[l + i + h] += invert * A[l + i];
        }
      }
    }
  }
  void fhwt_and(vector<T> &A, bool invert) {
    const int n = (int)A.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
      for (int l = 0; l < n; l += s) {
        for (int i = 0; i < h; i++) {
          A[l + i] += invert * A[l + i + h];
        }
      }
    }
  }
  void fhwt_xor(vector<T> &A, bool invert) {
    const int n = (int)A.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
      for (int l = 0; l < n; l += s) {
        for (int i = 0; i < h; i++) {
          T t = A[l + h + i];
          A[l + h + i] = A[l + i] - t;
          A[l + i] += t;
          if (invert) {
            A[l + h + i] /= 2;
            A[l + i] /= 2;
          }
        }
      }
    }
  }
};
