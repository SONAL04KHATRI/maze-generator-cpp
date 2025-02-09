#include "Maze.h"

int main(){
    // Set maze dimensions (should be odd numbers for proper generation)
    int width = 41, height = 21;
    Maze maze(width, height);
    maze.generate();
    maze.solve();
    maze.print();
    return 0;
}
