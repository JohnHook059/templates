#include <vector>
#include <string>
#include <algorithm>

struct big_int {
    std::vector<long long> base;
    int sign;
    const int st = 18;
    const long long mod = 1e18;
    
    big_int(std::string s1 = "0") : sign(1) {
        std::string s = "";
        if (s1[0] == '-') {
            sign = false;
            s1[0] = '0';
        }
        for (int i = 0; i < st - s1.length() % st; ++i)
            s += '0';
        s += s1;
		base.reserve(s.size() / st + 1);
        long long temp = 0;
        for (int i = int(s.length()) - st; i >= 0; i -= st) {
            temp = 0;
            for (int j = 0; j < st; ++j) {
                temp *= 10;
                temp += s[i + j] - '0';
            }
            base.push_back(temp);
        }
    }
    
    big_int& operator = (const big_int& right) {
        if (this == &right) {
            return *this;
        }
        
        base = right.base;
        sign = right.sign;
        return *this;
    }
    
    std::string str() {
        std::string s = "";
        long long temp = 0;
        for (int i = 0; i < base.size(); ++i) {
            temp = base[i];
            for (int j = 0; j < st; ++j) {
                s += temp % 10 + '0';
                temp /= 10;
            }
        }
        std::string ans = "";
        for (int i = int(s.length()) - 1; i >= 0; --i) {
            ans += s[i];
            if (ans == "0")
                ans = "";
        }
        return (ans.length() ? ans : "0");
    }
};


big_int operator + (big_int a, big_int b) {
    big_int ans;
    ans.base.resize(0);
    bool f = false;
    long long temp = 0;
    for (int i = 0; i <= std::max(a.base.size(), b.base.size()); ++i) {
        temp = (a.base.size() > i ? a.base[i] : 0) + (b.base.size() > i ? b.base[i] : 0);
        ans.base.push_back((temp + int(f)) % ans.mod);
        f = temp > ans.mod;
    }
    return ans;
}

big_int operator - (big_int a, big_int b) {
    big_int ans;
    ans.base.resize(0);
    bool f = false;
    bool f2 = false;
    long long temp = 0;
    for (int i = 0; i <= std::max(a.base.size(), b.base.size()); ++i) {
        temp = (a.base.size() > i ? a.base[i] : 0) - (b.base.size() > i ? b.base[i] : 0);
        f2 = temp < 0;
        if (temp < 0) temp += a.mod;
        ans.base.push_back((temp - int(f)) % ans.mod);
        f = f2;
    }
    return ans;
}

// Authors = JohnHook