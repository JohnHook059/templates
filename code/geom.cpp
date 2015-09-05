#define _USE_MATH_DEFINES

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

const double RAD = 180.0 / M_PI;
const double EPS = 10e-6;

bool isEqual(double a, double b) {
    return abs(a - b) < EPS;
}

template <typename T>
struct Vector {
    T x, y;
    Vector(T x = 0, T y = 0) : x(x), y(y) {}
    
    Vector normalize() {
        T d = sqrt(x * x + y * y);
        return Vector(x / d, y / d);
    }
    
    Vector operator + (Vector v) const {
        return Vector(x + v.x, y + v.y);
    }
    Vector operator - (Vector v) const {
        return Vector(x - v.x, y - v.y);
    }
    Vector operator * (T temp) const {
        return Vector(x * temp, y * temp);
    }
    T operator * (Vector v) const {
        return x * v.x + y * v.y;
    }
    T operator ^ (Vector v) const {
        return x * v.y - y * v.x;
    }
    
    void operator += (Vector v) {
        this = this + v;
    }
    void operator -= (Vector v) {
        this = this - v;
    }
    void operator *= (T temp) {
        this = this * temp;
    }
};

template <typename T>
bool operator == (Vector<T> a, Vector<T> b) {
    return isEqual(a.x, b.x) && isEqual(a.y, b.y);
}

template <typename T>
bool operator != (Vector<T> a, Vector<T> b) {
    return !(a == b);
}

template <typename T>
bool operator < (Vector<T> a, Vector<T> b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

template <typename T>
bool operator >(Vector<T> a, Vector<T> b) {
    return a.x != b.x ? a.x > b.x : a.y > b.y;
}

template <typename T>
istream& operator >> (istream& in, Vector<T>& v) {
    in >> v.x >> v.y;
    return in;
}
template <typename T>
ostream& operator << (ostream& out, Vector<T> v) {
    out << setprecision(6) << v.x << ' ' << v.y << '\n';
    return out;
}

template <typename T>
double getAngle(Vector<T> a, Vector<T> b) {
    return abs(atan2(a ^ b, a * b));
    //return abs(atan2(a ^ b, a * b)) * RAD;
}

template <typename T>
double len(Vector<T> a, Vector<T> b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

template <typename lT, typename vT>
struct Line {
    lT A, B, C;
    Line(Vector<vT> a = Vector<vT>(0, 0), Vector<vT> b = Vector<vT>(0, 0)) {
        A = a.y - b.y;
        B = b.x - a.x;
        C = -A * a.x - B * a.y;
    }
    
    int gcd(int a, int b) {
        return b ? gcd(b, a % b) : a;
    }
    void normalize() {
        int GCD = gcd(A, gcd(B, C));
        A /= GCD;
        B /= GCD;
        C /= GCD;
        
        if (A < 0 || (A == 0 && B < 0)) {
            A *= -1;
            B *= -1;
            C *= -1;
        }
    }
};

template <typename lT, typename vT>
bool operator == (Line<lT, vT> a, Line<lT, vT> b) {
    return isEqual(a.A, b.A) && isEqual(a.B, b.B) && isEqual(a.C, b.C);
}

template <typename lT, typename vT>
bool operator != (Line<lT, vT> a, Line<lT, vT> b) {
    return !(a == b);
}

template <typename lT, typename vT>
istream& operator >> (istream& in, Line<lT, vT>& l) {
    in >> l.A >> l.B >> l.C;
    return in;
}
template <typename lT, typename vT>
ostream& operator << (ostream& out, Line<lT, vT>& l) {
    out << setprecision(6) << l.A << ' ' << l.B << ' ' << l.C << '\n';
    return out;
}

template <typename lT, typename vT>
Vector<double> intersection(Line<lT, vT> f, Line<lT, vT> s) {
    double x = (double)(f.B * s.C - s.B * f.C) / (s.B * f.A - f.B * s.A);
    double y = (double)(f.A * s.C - s.A * f.C) / (s.A * f.B - f.A * s.B);
    return Vector<double>(x, y);
}

template <typename lT, typename vT>
double VtoL(Vector<vT> v, Line<lT, vT> l) {
    return abs((l.A * v.x + l.B * v.y + l.C) / sqrt(sqr(l.A) + sqr(l.B)));
}

template <typename T>
struct Section {
    Vector<T> first, second;
    Section(Vector<T> first = Vector<T>(0, 0), Vector<T> second = Vector<T>(0, 0)) : first(first), second(second) {}
};

template <typename T>
bool intersect_1(Section<T> a, Section<T> b) {
    if (a.first.x > a.second.x) swap(a.first.x, a.second.x);
    if (a.first.y > a.second.y) swap(a.first.y, a.second.y);
    if (b.first.x > b.second.x) swap(b.first.x, b.second.x);
    if (b.first.y > b.second.y) swap(b.first.y, b.second.y);
    return max(a.first.x, b.first.x) <= min(a.second.x, b.second.x) && max(a.first.y, b.first.y) <= min(a.second.y, b.second.y);
}

template <typename T>
bool intersect(Section<T> a, Section<T> b) {
    return intersect_1(a, b)
    && ((a.second - a.first) ^ (b.first - a.first)) * ((a.second - a.first) ^ (b.second - a.first)) <= 0
    && ((b.second - b.first) ^ (a.first - b.first)) * ((b.second - b.first) ^ (a.second - b.first)) <= 0;
}

int main() {

}

// Authors = JohnHook
// TODO API
