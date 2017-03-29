#include <vector>
#include <cstddef>
#include <climits>

template <typename T>
class tree {
private:
    std::vector<T> base, incoordination;
    T (*comp)(const T &, const T &), (*public_comp)(const T &, const T &);
    T neutral, public_neutral;
    
    void relax_incoordination(int v) {
        incoordination[v * 2] = public_comp(incoordination[v * 2], incoordination[v]);
        incoordination[v * 2 + 1] = public_comp(incoordination[v * 2 + 1], incoordination[v]);
        incoordination[v] = public_neutral;
    }
    void recalc(int v) {
        base[v] = comp(public_comp(base[v * 2], incoordination[v * 2]), public_comp(base[v * 2 + 1], incoordination[v * 2 + 1]));
    }
    void _public_update(int left, int right, T arg, int v, int l, int r) {
        if (right <= l || left >= r) return;
        if (left <= l && right >= r) {
            incoordination[v] = public_comp(incoordination[v], arg);
            return;
        }
        relax_incoordination(v);
        _public_update(left, right, arg, v * 2, l, (l + r) / 2);
        _public_update(left, right, arg, v * 2 + 1, (l + r) / 2, r);
        recalc(v);
    }
    T _public_get(int left, int right, int v, int l, int r) {
        if (right <= l || left >= r) return neutral;
        if (left <= l && right >= r)
            return public_comp(base[v], incoordination[v]);
        relax_incoordination(v);
        recalc(v);
        return comp(_public_get(left, right, v * 2, l, (l + r) / 2), _public_get(left, right, v * 2 + 1, (l + r) / 2, r));
    }
public:
    tree(const std::vector<T> &v, T (*comp)(const T &, const T &), T neutral, T (*_public_comp)(const T &, const T &) = NULL, T _public_neutral = NULL) :
    comp(comp), neutral(neutral), public_comp(_public_comp), public_neutral(_public_neutral) {
        if (public_comp == NULL) {
            public_comp = comp;
            public_neutral = neutral;
        }
        
        int st = 1;
        while (st < v.size())
            st <<= 1;
        base.resize(st << 1, neutral);
        incoordination.resize(st << 1, public_neutral);
        for (int i = st; i < st + v.size(); ++i)
            base[i] = v[i - st];
        for (int i = st - 1; i > 0; --i)
            base[i] = comp(base[i << 1], base[(i << 1) + 1]);
    }
    void single_update(int pos, T new_value) {
        pos += base.size() >> 1;
        base[pos] = new_value;
        while (pos > 1) {
            pos >>= 1;
            base[pos] = comp(base[pos << 1], base[(pos << 1) + 1]);
        }
    }
    void public_update(int left, int right, T new_value) {
        _public_update(left, right, new_value, 1, 0, (base.size() >> 1));
    }
    T get(int left, int right) {
        return _public_get(left, right, 1, 0, int(base.size()) / 2);
    }
};


// Дерево полуинтервалов.
// В конструктор подается:
//     1. Вектор элементов того же типа, что и дерево.
//     2. Функция по которой строится дерево.
//     3. Нейтральный элемент.
//     4. Функция массовой операции (опционально)
//     5. Нейтральный элемент по функции массовой операции (опционально).
// Например:
// unsigned int sum(const unsigned int &a, const unsigned int &b) { return a + b; }
// tree<unsigned int> t(*new vector<unsigned int>(N, 0), sum, 0);
// Изменение элемента: single_update(позиция изменяемого элемента, новое значение)
// Массовая операция изменения элементов: public_update(left, right, value)
// Запрос: get(левая граница, правая граница(не включительно))
