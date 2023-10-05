#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template <typename T>
vector<T> findLargestSubsequence(vector<T>& sequence, int K) 
{
    vector<T> result;
    stack<T> s;
    size_t n = sequence.size();

    for (size_t i = 0; i < n; ++i) 
    {
        while (!s.empty() && s.top() < sequence[i] && s.size() + n - i - 1 >= K) // размер стека + оставшиеся элементы
        {
            s.pop();
        }
        if (s.size() < K) 
        {
            s.push(sequence[i]);
        }
    }

    while (!s.empty()) 
    {
        result.push_back(s.top());
        s.pop();
    }

    reverse(result.begin(), result.end());

    return result;
}

int main() 
{
    vector<char> sequence = { 'a', 'b', 'b', 'a', 'c', 'b', 'd', 'a', 'e' };
    int K = 4;

    vector<char> result = findLargestSubsequence(sequence, K);

    cout << "Largest subsequence of " << K << " elements: ";
    for (auto elem : result) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
