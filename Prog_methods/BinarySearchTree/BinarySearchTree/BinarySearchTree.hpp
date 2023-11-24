template <typename keyType, typename dataType>
class BinarySearchTree
{
    struct Node
    {
        keyType key;
        dataType data;
        Node* left = nullptr, * right = nullptr;
        //Node() = default;
    } *root = nullptr;

    Node** _find(const keyType& key)
    {
        Node** p = (Node**)&root;
        while (p && (*p)->key != key)
        {
            p = (*p)->key < key ? &((*p)->right) : &((*p)->left);
        }
        return p;
    }

public:
    
    class iterator
    {
        Node* nodePtr = nullptr;
    public:
        iterator() = default;
        iterator(Node* node) : nodePtr(node) {};
        //iterator(iterator&& rhs) = noexcept(true);

        operator bool()
        {
            return nodePtr != nullptr;
        }
        dataType& operator*()
        {
            return this->nodePtr->data;
        }
        iterator& operator++()
        {
            if (this->nodePtr)
            {
                return findNext(this->nodePtr->key);
                //this->nodePtr = nodePtr->right;
            }
            return *this;
        }

        iterator findNext(const keyType& key)
        {
            Node** p = (Node**)&root, **lastleft = nullptr;
            while (p && (*p)->key != key)
                p = (*p)->key < key ? &((*p)->right) : (lastleft = p, &((*p)->left)); // operator ,

            if (*p && (*p)->right == nullptr)
                return lastleft != nullptr ? iterator(*lastleft) : iterator(nullptr);
            else
            {
                p = &(*p)->right;
                while ((*p)->left)
                    p = &((*p)->left);
                return *p;
            }

        }

        iterator findPrev(const keyType& key)
        {
            Node** p = (Node**)&root, ** lastright = nullptr;
            while (p && (*p)->key != key)
            p = (*p)->key < key ? &((*p)->left) : (lastright = p, &((*p)->right)); // operator ,

            if (*p && (*p)->left == nullptr)
                return lastright != nullptr ? iterator(*lastright) : iterator(nullptr);
            else
            {
                p = &(*p)->left;
                while ((*p)->right)
                    p = &((*p)->right);
                return *p;
            }

        }

        iterator find(const keyType& _key) const
        {
            auto p = _find(_key);
            return iterator(*p);
        }

        iterator insert(const keyType& key, const dataType& value)
        {
            auto p = _find(key);
            if (*p)
                (*p)->data = value;
            else
                (*p) = new Node{ key, value, nullptr, nullptr };

            return iterator(*p);
        }
    };

    BinarySearchTree() = default;
    BinarySearchTree(keyType& key, dataType& value)
    {
        this->root = new Node{ key, value, nullptr, nullptr };
    }
    
};