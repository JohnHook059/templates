//
//  archiver
//
//  Created by Иван Крючков on 19.10.15.
//  Copyright © 2015 JohnHook. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
using namespace std;

struct el {
    el *left, *right, *father;
    char value;
    double weight;
    bool ok;
    el() : left(nullptr), right(nullptr), father(nullptr), value('\0'), weight(0.0), ok(false) {}
};

struct tree {
    el *top;
    
    tree(tree *left = nullptr, tree *right = nullptr, char value = '\0', double weight = 0.0) {
        el *p = new el;
        p->ok = true;
        p->value = value;
        p->weight = weight;
        if (left != nullptr && right != nullptr) {
            p->father = this->top;
            p->left = left->top;
            p->right = right->top;
            p->weight = left->top->weight + right->top->weight;
        }
        top = p;
    }
    
    bool operator < (const tree& other) const {
        return top->weight > other.top->weight;
    }
};

tree _hafman(string s) {
    map<char, int> m;
    for (int i = 0; i < s.size(); i++)
        m[s[i]]++;
    priority_queue<tree> q;
    for (auto el: m)
        q.push(tree(nullptr, nullptr, el.first, (double) el.second / s.size()));
    while (q.size() > 1) {
        tree a = q.top();
        q.pop();
        tree b = q.top();
        q.pop();
        q.push(tree(&a, &b));
    }
    return q.top();
}
map<char, string> dict;
string dict_str = "", dict_str_2 = "";
void rec(el e, string s) {
    if (e.left == nullptr && e.right == nullptr) {
        dict_str_2 += e.value;
        dict[e.value] = s;
        return;
    }
    
    if (e.left != nullptr && e.left->ok) {
        dict_str += '0';
        rec(*e.left, s + '0');
        dict_str += '1';
    }
    if (e.right != nullptr && e.right->ok) {
        //dict_str += '0';
        rec(*e.right, s + '1');
        //dict_str += '1';
    }
}

//PARSER

int min(int a, int b) {
    return a < b ? a : b;
}
unsigned char stoch(string s) {
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans *= 2;
        ans += s[i] - '0';
    }
    return '\0' + ans;
}
string chtos(unsigned char n) { // lol
    string ans = "";
    while (n) {
        ans += (n % 2 ? '1' : '0');
        n /= 2;
    }
    for (int i = int(ans.size()); i < 8; i++)
        ans += '0';
    reverse(ans.begin(), ans.end());
    return ans;
}

string bstochs(string s) {
    string ans = "", temp = "";
    for (int i = 0; i < s.size(); i += 8) {
        for (int j = i; j < min(i + 8, int(s.size())); j++)
            temp += s[j];
        if (temp.size() == 8) {
            ans += stoch(temp);
            temp = "";
        }
    }
    ans += "##" + temp + "##";
    return ans;
}

//~PARSER

string hafman(string s) {
    dict = map<char, string>();
    dict_str = "";
    dict_str_2 = "";
    rec(*_hafman(s).top, "");
    string ans = "";
    for (char ch: s)
        ans += dict[ch];
    return dict_str_2 + "##" + bstochs(dict_str + '1') + bstochs(ans);
}

string unhafman(string h) {
    map<char, string> dict;
    string s = "";
    string dict_str = "", dict_str_2 = "";
    
    //PARSER
    
    int it = 0;
    while (h[it] != '#' || h[it + 1] != '#') {
        dict_str_2 += h[it];
        it++;
    }
    it += 2;
    
    while (h[it] != '#' || h[it + 1] != '#') {
        dict_str += chtos(h[it]);
        it++;
    }
    it += 2;
    for (; it < h.size() && (h[it] != '#' || h[it + 1] != '#'); it++)
        dict_str += h[it];
    it += 2;
    
    while (h[it] != '#' || h[it + 1] != '#') {
        s += chtos(h[it]);
        it++;
    }
    it += 2;
    for (; it < h.size() && (h[it] != '#' || h[it + 1] == '#'); it++)
        s += h[it];
    
    //~UNPARSER
    
    el *t = new el();
    string key = "";
    int uk = 0;
    for (char ch: dict_str)
        if (ch == '0') {
            key += '0';
            
            el *p = new el();
            p->father = t;
            t->left = p;
            t = p;
        }
        else {
            t->value = dict_str_2[uk];
            dict[dict_str_2[uk++]] = key;
            while (key.back() == '1') {
                key.pop_back();
                
                t = t->father;
            }
            if (!key.empty()) {
                key.back() = '1';
                t = t->father;
                el *p = new el();
                p->father = t;
                t->right = p;
                t = p;
            }
        }
    string ans = "";
    el *et = t;
    for (char ch: s) {
        if (ch == '0')
            t = t->left;
        if (ch == '1')
            t = t->right;
        if (t->value != '\0') {
            ans += t->value;
            t = et;
        }
    }
    
    return ans;
}
// одна буква - проблема?

int main(int argc, const char * argv[]) {
//    char* inp_name;
//    scanf("%ch", inp_name);
//    char *otp_name = inp_name + *".jh";
//    FILE *inp = fopen(inp_name, "r");
//    FILE *otp = fopen(otp_name, "w");
//    char* file, temp;
//    while (fscanf(inp, "%ch", temp) != NULL)
//        file += temp;
//    fclose(inp);
//    fprintf(otp, "%s", hafman(file).c_str());
//    fclose(otp);
    
    string s ="\
    Time to live\n\
    Time to lie\n\
    Time to laugh\n\
    Time to die\n\
    \n\
    Takes it easy, baby\n\
    Take it as it comes\n\
    Don't move too fast\n\
    And you want your love to last\n\
    Oh, you've been movin' much too fast\n\
    \n\
    Time to walk\n\
    Time to run\n\
    Time to aim your arrows\n\
    At the sun\n\
    \n\
    Takes it easy, baby\n\
    Take it as it comes\n\
    Don't move too fast\n\
    And you want your love to last\n\
    Oh, you've been movin' much too fast\n\
    \n\
    Go real slow\n\
    You like it more and more\n\
    Take it as it comes\n\
    Specialize in havin' fun\n\
    \n\
    Takes it easy, baby\n\
    Take it as it comes\n\
    Don't move too fast\n\
    And you want your love to last\n\
    Oh, you've been movin' much too fast\n\
    Movin' much too fast\n\
    Movin' much too fast\n";
    //string s = "missisipi";
    cout << s << endl << hafman(s) << endl << unhafman(hafman(s)) << endl;
    cout << (double) hafman(s).length() / s.length() << endl;;
    //cout << stoch("10001111") << endl << chtos('\217') << endl;
    
    return 0;
}
