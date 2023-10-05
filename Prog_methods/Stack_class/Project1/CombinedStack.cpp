#include <iostream>
#include <vector>
#include <stdexcept>

enum Policy
{
    StaticPolicy,
    LinearPolicy,
    GeometricicPolicy

};

template <typename T>
class CombinedStack
{
    const = 10;
    struct Node
    {
        T chunk;    
        size_t count;
        size_t capacity;
        Node* next;   
        ~Node()
        {
            delete[] chunk;
        }
    };

    Node* currentChunk;
    Node* lastChunk;

    size_t count;

    size_t currentIndex;
    Policy policy;

    size_t getChunkSize()
    {
        switch (policy)
        {
        case Policy::StaticPolicy:
            return staticsize;
            break;
        case Policy::LinearPolicy:
            return staticsize * (index + 1);
            break;
        case Policy::GeometricicPolicy:
            return staticsize * pow(1.631, index);
            break;
        default:
            break;
        }
    }

public:
    CombinedStack(Policy _p = Policy::StaticPolicy)
    {
        currentChunk = new Node{new T[10], nullptr, 0, 10}
        lastChunk = currentChunk;
        count = 0; 
        currentIndex = 0;
        policy = p;
    }

    // Деструктор 
    ~CombinedStack()
    {
        while (count)
        {
            pop();
        }
    };

    void push(T&& rhs)
    {
        if (currentChunk->count == currentChunk->capacity)
        {
            if (currentChunk != lastChank)
            {
                currentChunk = lastChunk;
            }
            else
            {
                size_t newsize = getChunkSize(++currentIndex); // currentIndex + 1
                currentChunk = new Node{ new T[newsize], currentCHunk, 0, newsize};
                //currentIndex++;
            }
        }

        currentChunk->chunk[currentChunk->count++] = rhs;
        count++;
    }

    void pop()
    {
        if (currentChunk->count == 0)
        {
            cutrrentChunk = currentChunk->next;
        }
        
        currentChunk->chunk[currentChunk->count--].~T();

        if (currentChunk->count < currentChunk->capacity / 2 && currentCHunk != lastChunk)
        {
            delete lastCHunk;
            lastChunk = currentChunk;
        }
        count--;
    }

    T& top()
    {
        // эксепшен что не пуст
        return currentChunk->chunk[currentChunk->count - 1];
    }

    size_t size() const
    {
        return count;
    }

private:

};
