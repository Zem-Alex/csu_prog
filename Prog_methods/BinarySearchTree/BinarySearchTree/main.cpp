#include <iostream>
#include <string>
#include "BinarySearchTree.hpp"

using namespace std;

int main() {

    // Создание объекта двоичного дерева поиска
    BinarySearchTree<int, int> t(5, 13);

    // Вставка элементов
    t.insert(3, 1337);
    t.insert(7, 1338);
    
    t.insert(4, 1339);

    auto it = t.find(3);

    auto it3 = t.findNext(4);

    // cout << *it3 << endl;



    return 0;
}

