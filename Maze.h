#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <utility>

class Maze {
public:
    Maze(int width, int height);
    void generate();
    void solve();
    void print() const;
private:
    int width, height;
    std::vector<std::vector<char>> grid;
    void initGrid();
    void carvePassagesFrom(int x, int y, std::vector<std::vector<bool>> &visited);
};

#endif // MAZE_H
