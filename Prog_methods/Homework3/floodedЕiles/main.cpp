#include <iostream>
#include <vector>
#include <stack>

int trappedWater(const std::vector<int>& heights) 
{
    if (heights.empty()) 
    {
        return 0;
    }

    std::stack<int> st;
    int waterVolume = 0;

    for (int i = 0; i < heights.size(); ++i) 
    {
        while (!st.empty() && heights[i] > heights[st.top()]) 
        {
            int top = st.top();
            st.pop();
            if (st.empty()) 
            {
                break;
            }
            int distance = i - st.top() - 1;
            int boundedHeight = std::min(heights[i], heights[st.top()]) - heights[top];
            waterVolume += distance * boundedHeight;
        }
        st.push(i);
    }

    return waterVolume;
}

int main() 
{
    std::vector<int> heights = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    int result = trappedWater(heights);
    std::cout << "Volume of trapped water: " << result << std::endl;
    return 0;
}
