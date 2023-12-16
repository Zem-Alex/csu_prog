﻿// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <optional>
#include <stack>
#include <string>
#include <functional>

template <typename Key, typename Data>
class bst
{
    struct node
    {
        Key key;
        Data data;
        node* left = nullptr, * right = nullptr;
    } *root = nullptr;
    size_t count = 0;
    //возвращает адрес указателя, по которому должен располагаться узел с ключом k
    node** _find(const Key& k)const;

    // функция для псевдографического вывода дерева
    void printTree(node* root, int level, bool isRight) const;
public:
    bst() {};
    ~bst();
    std::optional<std::reference_wrapper<Data>> find(const Key& k)const;
    void insert(const Key& k, const Data& d);
    std::optional<Key> findnext(const Key& k)const;
    std::optional<Key> findprev(const Key& k)const;
    void remove(const Key& k);
    size_t size() const { return count; }
    size_t height() const;
    size_t width() const;

    // функция для псевдографического вывода дерева
    void printTree() const;
    void visit(std::function<void(const Key& k, const Data& d)> worker) const;
    bool is_bst_by_data() const;
    std::vector<std::pair<Key, Data>> dump() const;
};

using namespace std;

template<typename Key, typename Data>
void bst<Key, Data>::printTree(node* root, int level, bool isRight) const
{
    if (!root) return;

    for (int i = 0; i < level; i++)
        std::cout << "    ";

    if (level > 0) {
        if (isRight)
            std::cout << "\\-- ";
        else
            std::cout << "|-- ";
    }

    std::cout << root->key << std::endl;

    printTree(root->left, level + 1, false);
    printTree(root->right, level + 1, true);
}

template<typename Key, typename Data>
void bst<Key, Data>::printTree() const
{
    printTree(root, 0, false);
}

template<typename Key, typename Data>
void bst<Key, Data>::visit(std::function<void(const Key& k, const Data& d)> worker) const
{
    std::stack<node*> s;
    node* current = root;
    while (current || s.size())
    {
        if (current)
        {
            s.push(current);
            current = current->left;
        }
        else
        {
            current = s.top()->right;
            worker(s.top()->key,s.top()->data);
            s.pop();
        }
    }
}

template<typename Key, typename Data>
bool bst<Key, Data>::is_bst_by_data() const
{
    bool result = true;
    std::optional<Data> prevdata;
    visit([&result, &prevdata](const Key& k, const Data& d) {
        if (prevdata and !(*prevdata < d))
            result = false;
        prevdata = d;
        });
    return result;
}

template<typename Key, typename Data>
std::vector<std::pair<Key, Data>> bst<Key, Data>::dump() const
{
    std::vector<std::pair<Key, Data>> result;
    visit([&result](const Key& k, const Data& d)
        {
            result.push_back({ k, d });
        });
    return result;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

template<typename Key, typename Data>
typename bst<Key, Data>::node** bst<Key, Data>::_find(const Key& k) const
{
    node** p = (node**)&root;
    while (*p && (*p)->key != k)
        p = (*p)->key < k ? &((*p)->right) : &((*p)->left);
    return p;
}

template<typename Key, typename Data>
bst<Key, Data>::~bst()
{
    std::stack<node*> s;
    node* current = root;
    while (current || s.size())
    {
        if (current)
        {
            s.push(current);
            current = current->left;
        }
        else
        {
            current = s.top()->right;
            delete s.top();
            s.pop();
        }
    }
}

template<typename Key, typename Data>
std::optional<std::reference_wrapper<Data>> bst<Key, Data>::find(const Key& k) const
{
    auto p = _find(k);
    if (*p) return (*p)->data;
    return std::nullopt;
}

template<typename Key, typename Data>
void bst<Key, Data>::insert(const Key& k, const Data& d)
{
    auto p = _find(k);
    if (*p) (*p)->data = d;
    else
    {
        *p = new node{ k,d };
        ++count;
    }
}

template<typename Key, typename Data>
std::optional<Key> bst<Key, Data>::findnext(const Key& k) const
{
    node** p = (node**)&root;
    node** lastleft = nullptr;
    while (*p)
        p = k < (*p)->key ? (lastleft = p, &((*p)->left)) : &((*p)->right);
    return lastleft ? std::optional<Key>((*lastleft)->key) : std::nullopt;
}

template<typename Key, typename Data>
std::optional<Key> bst<Key, Data>::findprev(const Key& k) const
{
    node** p = (node**)&root;
    node** lastright = nullptr;
    while (*p)
        p = k > (*p)->key ? (lastright = p, &((*p)->right)) : &((*p)->left);
    return lastright ? std::optional<Key>((*lastright)->key) : std::nullopt;
}

template<typename Key, typename Data>
void bst<Key, Data>::remove(const Key& k)
{
    auto p = _find(k);
    if (*p == nullptr) return;
    --count;
    if (!(*p)->left or !(*p)->right)
    {
        node* child = (*p)->left ? (*p)->left : (*p)->right;
        delete* p;
        *p = child;
    }
    else
    {
        node** nxt = &((*p)->right);
        while ((*nxt)->left)
            nxt = &(*nxt)->left;
        auto child = (*nxt)->right;
        (*p)->key = std::move((*nxt)->key);
        (*p)->data = std::move((*nxt)->data);
        delete* nxt;
        *nxt = child;
    }
}

template<typename Key, typename Data>
size_t bst<Key, Data>::height() const
{
    std::stack<pair<node*, size_t>> s;
    size_t currentHeight = 0;
    size_t height = 0;
    node* current = root;
    while (current || s.size())
    {
        if (current)
        {
            s.push({ current, currentHeight++ });
            current = current->left;
        }
        else
        {
            height = std::max(height, currentHeight);
            current = s.top().first->right;
            currentHeight = s.top().second + 1;
            s.pop();
        }
    }

    return height;
}

template<typename Key, typename Data>
size_t bst<Key, Data>::width() const
{
    std::stack<pair<node*, int>> s;
    int shift = 0;
    int minshift = 0;
    int maxshift = 0;
    node* current = root;
    while (current || s.size())
    {
        if (current)
        {
            s.push({ current, shift });
            shift--;
            current = current->left;
        }
        else
        {
            minshift = std::min(s.top().second, minshift);
            maxshift = std::max(s.top().second, maxshift);
            shift = s.top().second + 1;
            //s.push({ s.top(), });
            current = s.top().first->right;

            s.pop();
        }
    }
    
    return abs(minshift - maxshift);
}


int main()
{
    bst<std::string, int> t;
    t.insert("one", 1);
    cout << t.height() << endl;
    //cout << t.width() << endl;
    t.insert("two", 2);
    t.insert("three", 3);
    t.insert("four", 4);
    t.insert("five", 5);
    t.insert("six", 6);
    t.insert("seven", 7);
    t.insert("eight", 8);
    t.insert("nine", 9);
    t.insert("ten", 10);
    t.insert("eleven", 11);
    t.insert("twelve", 12);
    t.printTree();
    std::cout << *t.findnext("nine") << std::endl;
    std::cout << *t.find("five") << std::endl;
    (*t.find("five")).get() = 50;
    std::cout << *t.find("five") << std::endl;
    // t.remove("one");
    std::cout << t.size() << std::endl;
    std::cout << *t.findnext("nine") << std::endl;

    cout << t.height() << endl;
    cout << t.width() << endl;
    return 0;
    //std::cout << "Hello World!\n";
}
