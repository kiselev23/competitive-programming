#include <iostream>
#include <random>
#include <chrono>

using namespace std;

const int MAX_NODES = 1000000;

struct Node {
    int key;        // Ключ для поиска
    int value;      // Значение (опционально)
    int priority;   // Приоритет для свойства кучи
    int left;       // Левый ребенок
    int right;      // Правый ребенок
    
    Node() : key(0), value(0), priority(0), left(0), right(0) {}
    Node(int k, int val, int prio) : key(k), value(val), priority(prio), left(0), right(0) {}
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

// Создание нового узла
int new_node(int key, int value = 0, int priority = -1) {
    if (next_index > MAX_NODES) {
        cerr << "ERROR: Too many nodes!" << endl;
        return 0;
    }
    
    int idx = next_index++;
    if (priority == -1) {
        priority = dist(rng);
    }
    tree[idx] = Node(key, value, priority);
    return idx;
}

// Разделение дерева по ключу
void split(int v, int key, int& l, int& r) {
    if (!v) {
        l = r = 0;
        return;
    }
    
    if (tree[v].key <= key) {
        split(tree[v].right, key, tree[v].right, r);
        l = v;
    } else {
        split(tree[v].left, key, l, tree[v].left);
        r = v;
    }
}

// Слияние двух деревьев
int merge(int l, int r) {
    if (!l) return r;
    if (!r) return l;
    
    if (tree[l].priority > tree[r].priority) {
        tree[l].right = merge(tree[l].right, r);
        return l;
    } else {
        tree[r].left = merge(l, tree[r].left);
        return r;
    }
}

// Вставка элемента с ключом
void insert(int key, int value = 0) {
    int l, r;
    split(root, key, l, r);
    int new_node_idx = new_node(key, value);
    root = merge(merge(l, new_node_idx), r);
}

// Удаление элемента по ключу
void erase(int key) {
    int l, m, r;
    split(root, key, l, r);
    split(l, key - 1, l, m);
    root = merge(l, r);
}

// Поиск элемента по ключу
bool contains(int key) {
    int l, m, r;
    split(root, key, l, r);
    split(l, key - 1, l, m);
    bool found = (m != 0);
    root = merge(merge(l, m), r);
    return found;
}

// Получение значения по ключу
int get(int key) {
    int l, m, r;
    split(root, key, l, r);
    split(l, key - 1, l, m);
    
    int result = -1;
    if (m) {
        result = tree[m].value;
    }
    
    root = merge(merge(l, m), r);
    return result;
}

// Изменение значения по ключу
void set(int key, int value) {
    int l, m, r;
    split(root, key, l, r);
    split(l, key - 1, l, m);
    
    if (m) {
        tree[m].value = value;
    }
    
    root = merge(merge(l, m), r);
}

// Обход дерева в порядке возрастания ключей
void in_order(int v) {
    if (!v) return;
    in_order(tree[v].left);
    cout << "(" << tree[v].key << ":" << tree[v].value << ") ";
    in_order(tree[v].right);
}

// Поиск минимального ключа
int find_min(int v) {
    while (tree[v].left) {
        v = tree[v].left;
    }
    return tree[v].key;
}

// Поиск максимального ключа
int find_max(int v) {
    while (tree[v].right) {
        v = tree[v].right;
    }
    return tree[v].key;
}

// Пример использования
int main() {
    init();
    
    // Вставляем элементы с ключами
    insert(10, 100);
    insert(5, 50);
    insert(15, 150);
    insert(3, 30);
    insert(7, 70);
    
    cout << "Tree in-order: ";
    in_order(root);
    cout << endl;
    
    // Поиск элементов
    cout << "Contains key 7: " << (contains(7) ? "Yes" : "No") << endl;
    cout << "Value at key 7: " << get(7) << endl;
    
    // Изменение значения
    set(7, 700);
    cout << "After changing key 7 to 700: ";
    in_order(root);
    cout << endl;
    // Поиск мин и макс
    cout << "Min key: " << find_min(root) << endl;
    cout << "Max key: " << find_max(root) << endl;
    
    // Удаление элемента
    erase(7);
    cout << "After erasing key 7: ";
    in_order(root);
    cout << endl;
    
    cout << "Contains key 7: " << (contains(7) ? "Yes" : "No") << endl;
    
    return 0;
}
