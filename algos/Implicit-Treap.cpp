#include <iostream>
#include <random>
#include <chrono>

using namespace std;

const int MAX_NODES = 1000000;

struct Node {
    int value;      // Значение элемента
    int priority;   // Приоритет для поддержания свойства кучи
    int size;       // Размер поддерева (для неявного ключа)
    int left;       // Левый ребенок (индекс)
    int right;      // Правый ребенок (индекс)
    
    Node() : value(0), priority(0), size(1), left(0), right(0) {}
    Node(int val, int prio) : value(val), priority(prio), size(1), left(0), right(0) {}
};

Node tree[MAX_NODES + 1];
int root = 0;
int next_index = 1;

// Инициализация генератора случайных чисел
random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> dist(0, INT_MAX);

void init() {
    root = 0;
    next_index = 1;
}

// Обновление размера поддерева
void update_size(int v) {
    if (v) {
        tree[v].size = 1;
        if (tree[v].left) tree[v].size += tree[tree[v].left].size;
        if (tree[v].right) tree[v].size += tree[tree[v].right].size;
    }
}

// Создание нового узла
int new_node(int value, int priority = -1) {
    if (next_index > MAX_NODES) {
        cerr << "ERROR: Too many nodes!" << endl;
        return 0;
    }
    
    int idx = next_index++;
    if (priority == -1) {
        priority = dist(rng);
    }
    tree[idx] = Node(value, priority);
    return idx;
}

// Разделение дерева по позиции (неявный ключ)
void split(int v, int pos, int& l, int& r, int add = 0) {
    if (!v) {
        l = r = 0;
        return;
    }
    
    int cur_pos = add;
    if (tree[v].left) {
        cur_pos += tree[tree[v].left].size;
    }
    
    if (cur_pos < pos) {
        split(tree[v].right, pos, tree[v].right, r, cur_pos + 1);
        l = v;
    } else {
        split(tree[v].left, pos, l, tree[v].left, add);
        r = v;
    }
    
    update_size(v);
}

// Слияние двух деревьев
int merge(int l, int r) {
    if (!l) return r;
    if (!r) return l;
    
    if (tree[l].priority > tree[r].priority) {
        tree[l].right = merge(tree[l].right, r);
        update_size(l);
        return l;
    } else {
        tree[r].left = merge(l, tree[r].left);
        update_size(r);
        return r;
    }
}

// Вставка элемента в позицию
void insert(int pos, int value) {
    int l, r;
    split(root, pos, l, r);
    int new_node_idx = new_node(value);
    root = merge(merge(l, new_node_idx), r);
}

// Удаление элемента с позиции
void erase(int pos) {
    int l, m, r;
    split(root, pos, l, r);
    split(r, 1, m, r);
    root = merge(l, r);
}

// Получение значения элемента на позиции
int get(int pos) {
    int l, m, r;
    split(root, pos, l, r);
    split(r, 1, m, r);
    
    int result = 0;
    if (m) {
        result = tree[m].value;
    }
    
    root = merge(merge(l, m), r);
    return result;
}

// Изменение значения элемента на позиции
void set(int pos, int value) {
    int l, m, r;
    split(root, pos, l, r);
    split(r, 1, m, r);
    
    if (m) {
        tree[m].value = value;
    }
    
    root = merge(merge(l, m), r);
}

// Вывод всего дерева (для отладки)
void print(int v) {
    if (!v) return;
    print(tree[v].left);
    cout << tree[v].value << " ";
    print(tree[v].right);
}

// Пример использования
int main() {
    init();
    
    // Вставляем элементы в различные позиции
    insert(0, 10);  // [10]
    insert(1, 20);  // [10, 20]
    insert(1, 15);  // [10, 15, 20]
    insert(0, 5);   // [5, 10, 15, 20]
    
    cout << "Tree after inserts: ";
    print(root);
    cout << endl;
    
    // Получаем и изменяем элементы
    cout << "Element at position 2: " << get(2) << endl; // 15
    
    set(2, 18);
    cout << "After changing position 2 to 18: ";
    print(root);
    cout << endl;
    
    // Удаляем элемент
    erase(1);
    cout << "After removing position 1: ";
    print(root);
    cout << endl;
    
    return 0;
}
