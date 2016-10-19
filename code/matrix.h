//matrix.h

#include <vector>
#include <iostream>
#include <stdexcept>
using std::vector;

template <typename T>
class matrix {
private:
    vector<vector<T>> base;
    void elementary_operation1(size_t i, size_t j, T k) {
        for (int it = 0; it < base.back().size(); ++it)
            base[i][it] += base[j][it] * k;
    }
    void elementary_operation2(size_t i, T k) {
        for (int it = 0; it < base.back().size(); ++it)
            base[i][it] = base[i][it] * k;
    }

    void to_stage_type() {
        for (size_t j = 0; j < std::min(base.size(), base.back().size()); ++j)
            for (size_t i = 0; i < base.size(); ++i) {
                if (base[j][j] == 0)
                    break;
                if (i != j)
                    elementary_operation1(i, j, T(-base[i][j], base[j][j]));
            }
    }
    void normalize() {
        for (size_t i = 0; i < std::min(base.size(), base.back().size()); ++i) {
            if (base[i][i] == 0)
                return;
            elementary_operation2(i, T(T(1, 1), base[i][i]));
        }
    }
public:
    matrix(vector<vector<T>> base) : base(base) {
        for (const auto& line : base)
            if (line.size() != base[0].size())
                throw std::out_of_range("");
    }
    size_t get_N() const {
        return base.size();
    }
    size_t get_M() const {
        return base.back().size();
    }
    T operator ()(size_t i, size_t j) const {
        return base[i][j];
    }
    
    void solve() {
        to_stage_type();
        normalize();
    }
};

template <typename T>
std::ostream& operator << (std::ostream& out, const matrix<T>& other) {
    for (size_t i = 0; i < other.get_N(); ++i) {
        for (size_t j = 0; j < other.get_M(); ++j)
            out << other(i, j) << '\t';
        out << '\n';
    }
    return out;
}

template <typename T>
matrix<T> operator *(const matrix<T>& a, const matrix<T>& b) {
    if (a.get_M() != b.get_N())
        return matrix<T>(vector<vector<T>>());
    vector<vector<T>> v(a.get_N(), vector<T>(b.get_M()));
    for (size_t i = 0; i < a.get_N(); ++i)
        for (size_t j = 0; j < b.get_M(); ++j)
            for (size_t r = 0; r < a.get_M(); ++r)
                v[i][j] += a(i, r) * b(r, j);
    return matrix<T>(v);
}

template <typename T>
matrix<T> Transpose(const matrix<T>& m) {
    vector<vector<T>> ans(m.get_N(), vector<T>(m.get_M()));
    for (size_t i = 0; i < m.get_N(); ++i)
        for (size_t j = i; j < m.get_M(); ++j) {
            ans[i][j] = m(j, i);
            ans[j][i] = m(i, j);
        }
    return matrix<T>(ans);
}

template <typename T>
matrix<T> operator +(const matrix<T>& a, const matrix<T>& b) {
    vector<vector<T>> ans(a.get_N(), vector<T>(a.get_M()));
    for (size_t i = 0; i < a.get_N(); ++i)
        for (size_t j = 0; j < a.get_M(); ++j)
            ans[i][j] = a(i, j) + b(i, j);

    return matrix<T>(ans);
}

template <typename T>
matrix<T> operator -(const matrix<T>& a, const matrix<T>& b) {
    vector<vector<T>> ans(a.get_N(), vector<T>(a.get_M()));
    for (size_t i = 0; i < a.get_N(); ++i)
        for (size_t j = 0; j < a.get_M(); ++j)
            ans[i][j] = a(i, j) - b(i, j);
    
    return matrix<T>(ans);
}
