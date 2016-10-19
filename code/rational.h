//rational.h

#include <iostream>

class rational {
private:
    long long numerator, denominator;
    
    static long long gcd(long long a, long long b) {
        a = std::abs(a);
        b = std::abs(b);
        return b ? gcd (b, a % b) : a;
    }
public:
    rational(long long x = 0) : numerator(x), denominator(1) {}
    rational(long long numerator, long long denominator) : numerator(numerator), denominator(denominator) {}
    rational(rational const &numerator, rational const &denominator) :
        numerator(numerator.numerator * denominator.denominator), denominator(denominator.numerator * numerator.denominator) {}
    
    rational operator + (const rational&) const;
    rational operator - (const rational&) const;
    rational operator + () const;
    rational operator - () const;
    rational operator * (const rational&) const;
    rational operator / (const rational&) const;
    rational& operator += (const rational&);
    rational& operator -= (const rational&);
    rational& operator *= (const rational&);
    rational& operator /= (const rational&);
    friend std::istream& operator >>(std::istream&, rational&);
    friend std::ostream& operator << (std::ostream&, rational);
    bool operator == (const rational&) const;
    bool operator != (const rational&) const;
    
    rational normalize() const {
        if (this->numerator == 0)
            return rational(0);
        long long g = gcd(numerator, denominator);
        if (denominator < 0)
            g *= -1;
        return rational(numerator / g, denominator / g);
    }
};

rational rational::operator + (const rational& other) const {
    return rational(numerator * other.denominator + denominator * other.numerator, denominator * other.denominator).normalize();
}

rational rational::operator - (const rational& other) const {
    return rational(numerator * other.denominator - denominator * other.numerator, denominator * other.denominator).normalize();
}

rational rational::operator + () const {
    return *this;
}

rational rational::operator - () const {
    return rational(-numerator, denominator);
}

rational rational::operator * (const rational& other) const {
    return rational(numerator * other.numerator, denominator * other.denominator).normalize();
}

rational rational::operator / (const rational& other) const {
    return rational(numerator * other.denominator, denominator * other.numerator).normalize();
}

rational& rational::operator += (const rational& other) {
    *this = *this + other;
    return *this;
}

rational& rational::operator -= (const rational& other) {
    *this = *this - other;
    return *this;
}

rational& rational::operator *= (const rational& other) {
    *this = *this * other;
    return *this;
}

rational& rational::operator /= (const rational& other) {
    *this = *this / other;
    return *this;
}

std::ostream& operator << (std::ostream& out, rational other) {
    rational for_print = other.normalize();
    if (for_print.denominator == 1)
        out << for_print.numerator;
    else
        out << for_print.numerator << '/' << for_print.denominator;
    return out;
}

bool rational::operator == (const rational& other) const {
    rational a = this->normalize();
    rational b = other.normalize();
    return a.numerator == b.numerator && a.denominator == b.denominator;
}

bool rational::operator != (const rational& other) const {
    return !(*this == other);
}
