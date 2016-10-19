#include <map>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

template <typename T>
class Polynomial {
 private:
    map<size_t, T> data;
    void relax() {
        auto ans = data;
        for (const auto& item : data)
            if (item.second == 0)
                ans.erase(item.first);
        data = ans;
    }

 public:
    static string format(const pair<size_t, T>& p) {
        string ans;
        if (p.second != 1 && p.second != -1) {
            ans += to_string(p.second);
            if (p.first != 0) {
                ans += "*x";
                if (p.first != 1)
                    ans += "^" + to_string(p.first);
            }
        } else {
            if (p.first != 0) {
                if (p.second == -1)
                    ans += '-';
                ans += "x";
                if (p.first != 1)
                    ans += "^" + to_string(p.first);
            }
        }

        if (ans.empty())
            ans += to_string(p.second);
        return ans[0] == '-' ? ans : '+' + ans;
    }

    Polynomial(const vector<T>& v) {
        for (size_t i = 0; i != v.size(); ++i)
            data[i] = v[i];
        relax();
    }
    Polynomial(const T& item = T()) {
        data[0] = item;
        relax();
    }
    template <typename In>
    Polynomial(In begin, In end) {
        size_t pos = 0;
        for (In it = begin; it != end; ++it, ++pos)
            data[pos] = *it;
        relax();
    }

    bool operator ==(const Polynomial& other) const;
    bool operator !=(const Polynomial& other) const;
    Polynomial operator +(const Polynomial& other) const;
    Polynomial operator -(const Polynomial& other) const;
    Polynomial operator *(const Polynomial& other) const;
    Polynomial& operator +=(const Polynomial& other);
    Polynomial& operator -=(const Polynomial& other);
    Polynomial& operator *=(const Polynomial& other);

    T operator[](const size_t& pos) const {
        if (data.find(pos) == data.end())
            return T();
        return data.at(pos);
    }

    size_t Degree() const {
        if (data.empty())
            return -1;
        auto temp = data.end();
        --temp;
        return temp->first;
    }

    const typename map<size_t, T>::const_iterator begin() const {
        return data.begin();
    }
    const typename map<size_t, T>::const_iterator end() const {
        return data.end();
    }

    T operator()(const T& x) const {
        T ans = T();
        for (const auto& item : data)
            ans += item.second * pow(x, item.first);
        return ans;
    }

    // friend ostream& operator <<(ostream&, const Polynomial&);
    // Polynomial operator /(const Polynomial& other) const;
    // Polynomial operator %(const Polynomial& other) const;
    // Polynomial operator ,(const Polynomial& other) const;
};

template <typename T>
bool Polynomial<T>::operator ==(const Polynomial<T>& other) const {
    return data == other.data;
}

template <typename T>
bool Polynomial<T>::operator !=(const Polynomial<T>& other) const {
    return data != other.data;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator +(const Polynomial<T>& other) const {
    Polynomial<T> ans = *this;
    ans += other;
    return ans;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator -(const Polynomial<T>& other) const {
    Polynomial<T> ans = *this;
    ans -= other;
    return ans;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator *(const Polynomial<T>& other) const {
    Polynomial<T> ans;
    for (const auto& item1 : data)
        for (const auto& item2 : other.data) {
            auto pos = item1.first + item2.first;
            auto value = item1.second * item2.second;
            ans.data[pos] += value;
        }
    ans.relax();
    return ans;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator +=(const Polynomial<T>& other) {
    for (const auto& item : other.data)
        this->data[item.first] += item.second;
    this->relax();
    return *this;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator -=(const Polynomial<T>& other) {
    for (const auto& item : other.data)
        this->data[item.first] -= item.second;
    this->relax();
    return *this;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator *=(const Polynomial<T>& other) {
    data = (*this * other).data;
    return *this;
}

template <typename T>
ostream& operator <<(ostream& out, const Polynomial<T>& other) {
    vector<string> v;
    for (auto item = other.begin(); item != other.end(); ++item)
        v.push_back(Polynomial<T>::format(*item));

    reverse(v.begin(), v.end());
    string ans = "";
    for (const auto& str : v)
        ans += str;

    if (ans[0] == '+')
        ans.erase(0, 1);
    if (ans == "")
        ans = "0";
    out << ans;
    return out;
}
