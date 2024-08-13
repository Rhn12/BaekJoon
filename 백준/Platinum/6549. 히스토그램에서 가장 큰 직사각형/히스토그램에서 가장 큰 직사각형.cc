#include <iostream>
#include <stack>
#include <vector>

long long largestRectangle(std::vector<int>& heights) {
    std::stack<int> s;
    heights.push_back(0);
    long long maxArea = 0;
    int n = heights.size();
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = std::max(maxArea, static_cast<long long>(height) * width);
        }
        s.push(i);
    }
    return maxArea;
}

int main() {
    while (true) {
        int n;
        std::cin >> n;
        if (n == 0) break;
        std::vector<int> heights(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> heights[i];
        }
        std::cout << largestRectangle(heights) << '\n';
    }
    return 0;
}