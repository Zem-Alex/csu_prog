// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
    bool isCondition2();
    bool isCondition3();

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

    bool isRedBlackTree();
    void insertToRBT(const Key& k);

    // функция для псевдографического вывода дерева
    void printTree() const;
    void visit(std::function<void(const Key& k, const Data& d)> worker) const;
    bool is_bst_by_data() const;
    std::vector<std::pair<Key, Data>> dump() const;
};

enum class Color
{
    Red,
    Black
};

template<typename Key, typename Data>
bool bst<Key, Data>::isCondition2()
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
            
            if (s.top()->data == Color::Red)
            {
                auto left = s.top()->left;
                auto right = s.top()->right;
                if (left && left->data == Color::Red || right && right->data == Color::Red)
                {
                    return false;
                }
            }
            s.pop();
        }
    }
    return true;
}

template<typename Key, typename Data>
bool bst<Key, Data>::isCondition3()
{
    std::stack<pair<node*, size_t>> s;
    size_t currentHeight = 0;
    int height = -1;
    node* current = root;
    while (current || s.size())
    {
        if (current)
        {
            s.push({ current, current->data == Color::Black ? currentHeight++ : currentHeight });
            current = current->left;
        }
        else
        {
            if (height != -1 && height != currentHeight)
                return false;

            height = currentHeight;
            current = s.top().first->right;
            currentHeight = s.top().second;
            if (s.top().first->data == Color::Black)
                ++currentHeight;

            s.pop();
        }
    }

    return true;
}

template<typename Key, typename Data>
bool bst<Key, Data>::isRedBlackTree()
{
    return isCondition2() && isCondition3();
}

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

template<typename Key, typename Data>
void bst<Key, Data>::insertToRBT(const Key& k)
{
    auto rotateLeft = [](node** r) -> void
    {
        auto tmp = *r;
        *r = (*r)->right;
        tmp->left = (*r)->left;
        (*r)->left = tmp;
    };

    auto rotateRight = [](node** r) -> void
    {
        auto tmp = *r;
        *r = (*r)->left;
        tmp->right = (*r)->right;
        (*r)->right = tmp;
    };

    size_t& ccount = count;

    std::function<bst<Key, Data>::node**(bst<Key, Data>::node**)> insert = [&](bst<Key, Data>::node** r) -> bst<Key, Data>::node** // return addres of pointer start problem vertex after insert in subtree vertex 
    {
        if (*r == nullptr)
        {
            *r = new node{ k, Color::Red };
            ccount++;
            return r;
        }

        if ((*r)->key == k)
            return nullptr;

        auto p = ((*r)->key == k) ? insert(&(*r)->right) : insert(&(*r)->left);

        if (p == nullptr)
            return nullptr;

        if (((*r)->right == *p || (*r)->left == *p) && (*r)->data == Color::Black)
            return nullptr;

        if ((*r)->right == *p || (*r)->left == *p)
            return p;

        if (
            (p == &(*r)->left->left && (*r)->right->data == Color::Red) || // 1a scheme
            (p == &(*r)->right->right && (*r)->left->data == Color::Red) || //  symmetrical 1a
            (p == &(*r)->left->right && (*r)->right->data == Color::Red) || // 1b
            (p == &(*r)->right->left && (*r)->left->data == Color::Red) // 1b symmetrical
            ) 
        {
            (*r)->right->data = Color::Black;
            (*r)->left->data = Color::Black;
            (*r)->data = Color::Red;
            return r; // r - proplem vertex
        }

        if(p == &(*r)->left->left) // shceme 2a
        {
            rotateRight(r);

            (*r)->data = Color::Black;
            (*r)->right->data = Color::Red;
            
            return nullptr;
        }

        if (p == &(*r)->right->right) // shceme 2a
        {
            rotateLeft(r);

            (*r)->data = Color::Black;
            (*r)->left->data = Color::Red;

            return nullptr;
        }

        if (p == &(*r)->left->right) // shceme 2b
        {
            rotateRight(&(*r)->left);

            p = &(*r)->left->left;
        }

        if (p == &(*r)->right->left) // shceme 2b
        {
            rotateLeft(&(*r)->right);

            p = &(*r)->right->right;
        }

    }&(root);

    root->data = Color::Black;

}

int main()
{
    bst<int, Color> rbt;


    rbt.insertToRBT(15);
    /*rbt.insert(13, Color::Black);
    rbt.insert(8, Color::Red);
    rbt.insert(11, Color::Black);
    rbt.insert(1, Color::Black);
    rbt.insert(6, Color::Red);

    rbt.insert(17, Color::Red);
    rbt.insert(15, Color::Black);
    rbt.insert(25, Color::Black);
    rbt.insert(22, Color::Red);
    rbt.insert(27, Color::Red);
    std::cout << rbt.isRedBlackTree();*/




    //bst<std::string, int> t;
    //t.insert("one", 1);
    //cout << t.height() << endl;
    ////cout << t.width() << endl;
    //t.insert("two", 2);
    //t.insert("three", 3);
    //t.insert("four", 4);
    //t.insert("five", 5);
    //t.insert("six", 6);
    //t.insert("seven", 7);
    //t.insert("eight", 8);
    //t.insert("nine", 9);
    //t.insert("ten", 10);
    //t.insert("eleven", 11);
    //t.insert("twelve", 12);
    //t.printTree();
    //std::cout << *t.findnext("nine") << std::endl;
    //std::cout << *t.find("five") << std::endl;
    //(*t.find("five")).get() = 50;
    //std::cout << *t.find("five") << std::endl;
    //// t.remove("one");
    //std::cout << t.size() << std::endl;
    //std::cout << *t.findnext("nine") << std::endl;

    //cout << t.height() << endl;
    //cout << t.width() << endl;
    //return 0;
    //std::cout << "Hello World!\n";
}
