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
        for (size_t j = 0; j < std::min(base.size(), base.back().size()); ++j) {
            if (base[j][j] == 0)
                for (size_t i = j + 1; i < base.size(); ++i)
                    if (base[i][j] != 0) {
                        elementary_operation1(j, i, 1);
                        std::cout << "NUM " << 1 << '\n';
                        std::cout << *this << '\n';
                    }
            for (size_t i = 0; i < base.size(); ++i) {
                if (base[j][j] == 0)
                    break;
                if (i != j) {
                    std::cout << "NUM " << T(-base[i][j], base[j][j]) << '\n';
                    elementary_operation1(i, j, T(-base[i][j], base[j][j]));
                    std::cout << *this << '\n';
                }
            }
        }
    }
    void normalize() {
        for (size_t i = 0; i < std::min(base.size(), base.back().size()); ++i) {
            if (base[i][i] == 0)
                return;
            elementary_operation2(i, T(T(1, 1), base[i][i]));
            std::cout << *this << '\n';
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
    
    matrix<T> inverse() const {
        vector<vector<T>> v(base.size(), vector<T>(base.back().size() * 2)), ans(base.size(), vector<T>(base.back().size()));
        for (size_t i = 0; i < base.size(); ++i) {
            copy(base[i].begin(), base[i].end(), v[i].begin());
            v[i][i + base.back().size()] = 1;
        }
        matrix<T> mtrx(v);
        mtrx.solve();
        for (size_t i = 0; i < base.size(); ++i)
            for (size_t j = base.back().size(); j < base.back().size() * 2; ++j)
                ans[i][j - base.back().size()] = mtrx.base[i][j];
        return matrix<T>(ans);
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
        throw std::out_of_range("");
    vector<vector<T>> v(a.get_N(), vector<T>(b.get_M()));
    for (size_t i = 0; i < a.get_N(); ++i)
        for (size_t j = 0; j < b.get_M(); ++j)
            for (size_t r = 0; r < a.get_M(); ++r)
                v[i][j] += a(i, r) * b(r, j);
    return matrix<T>(v);
}

template <typename T>
matrix<T> Transpose(const matrix<T>& m) {
    vector<vector<T>> ans(m.get_M(), vector<T>(m.get_N()));
    for (size_t i = 0; i < m.get_N(); ++i)
        for (size_t j = 0; j < m.get_M(); ++j)
            ans[j][i] = m(i, j);
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

template <typename T>
matrix<T> delij(const matrix<T>& m, size_t ii, size_t jj) {
    vector<vector<T>> v(m.get_N() - 1, vector<T>(m.get_M() - 1));
    for (size_t i = 0; i < m.get_N() - 1; ++i)
        for (size_t j = 0; j < m.get_M() - 1; ++j)
            v[i][j] = m(i + (i >= ii), j + (j >= jj));
    return matrix<T>(v);
}

template <typename T>
T determinant(const matrix<T>& m) {
    if (m.get_N() != m.get_M())
        throw std::out_of_range("");
    
    if (m.get_N() == 1)
        return m(0, 0);
    T ans;
    for (size_t i = 0; i < m.get_N(); ++i)
        ans += T(i % 2 ? -1 : 1) * m(i, 0) * determinant(delij(m, i, 0));
    return ans;
}
