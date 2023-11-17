#pragma once 

template <typename keyType, typename dataType>
class BinarySearchTree
{
	/*struct Node
	{
		keyType key;
		dataType data;
		Node* left = nullptr;
		Node* right = nullptr;
	};
	Node* root;   тоже самое снизу*/
	struct Node
	{
		keyType key;
		dataType data;
		Node* left = nullptr;
		Node* right = nullptr;
	}* root = nullptr;
public:
	class iterator
	{
	private:
		Node* nodePtr;
	public:
		bool operator(bool)()
		{
			return nodePtr != nullptr;
		}
		dataType& operator*()
		{
			return nullptr->data;
		}
		iterator operator++()
		{

		}
	};
	BinarySearchTree() {}
	iterator find(const keyType& key);
	iterator insert(const keyType& key, const dataType& data);
	iterator findnext(const keyTyep&);
	iterator findprev(const keyType&);
	void remove(const keyType&);
	~BinarySearchTree();
	
};

