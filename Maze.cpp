#include "Maze.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>

// Constructor: initialize width, height, and grid
Maze::Maze(int width, int height) : width(width), height(height) {
    initGrid();
}

// Initialize grid with walls ('#')
void Maze::initGrid() {
    grid.resize(height, std::vector<char>(width, '#'));
}

// Generate maze using iterative DFS (with stack and random shuffle)
void Maze::generate() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::stack<std::pair<int, int>> stack;
    int startX = 1, startY = 1;
    visited[startY][startX] = true;
    grid[startY][startX] = ' ';
    stack.push({startX, startY});

    // Offsets for 4 directions: right, left, down, up (using step of 2)
    int dx[4] = {2, -2, 0, 0};
    int dy[4] = {0, 0, 2, -2};

    while(!stack.empty()){
        auto [x, y] = stack.top();
        std::vector<int> dirs = {0, 1, 2, 3};
        std::random_shuffle(dirs.begin(), dirs.end());
        bool moved = false;
        for (int dir : dirs) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx > 0 && nx < width-1 && ny > 0 && ny < height-1 && !visited[ny][nx]) {
                visited[ny][nx] = true;
                grid[ny][nx] = ' ';
                // Remove wall between current cell and next cell
                grid[y + dy[dir]/2][x + dx[dir]/2] = ' ';
                stack.push({nx, ny});
                moved = true;
                break;
            }
        }
        if (!moved) {
            stack.pop();
        }
    }
}

// Solve the maze using BFS from (1,1) to (width-2, height-2)
void Maze::solve() {
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::vector<std::vector<std::pair<int,int>>> parent(height, std::vector<std::pair<int,int>>(width, {-1,-1}));
    std::vector<std::pair<int,int>> queue;
    queue.push_back({1,1});
    visited[1][1] = true;
    bool found = false;
    int ex = width - 2, ey = height - 2;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while(!queue.empty()){
        auto [x, y] = queue.front();
        queue.erase(queue.begin());
        if(x == ex && y == ey) {
            found = true;
            break;
        }
        for (int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < width && ny >= 0 && ny < height && !visited[ny][nx] && grid[ny][nx]==' '){
                visited[ny][nx] = true;
                parent[ny][nx] = {x,y};
                queue.push_back({nx,ny});
            }
        }
    }
    if(found){
        // Mark the path with '.' from the exit to the start
        int x = ex, y = ey;
        while(!(x == 1 && y == 1)){
            grid[y][x] = '.';
            auto p = parent[y][x];
            x = p.first;
            y = p.second;
        }
        grid[1][1] = '.';
    }
}

// Print the maze to the terminal
void Maze::print() const {
    for (const auto &row : grid) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}
