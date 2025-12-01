#include <vector>
#include <AlgorithmVisualizer.h>
#include <QTimer>
#include <queue>
#include <utility>
#include <Algorithms.h>
#include <QThread>
#include <stack>

void AlgorithmManager::bfs(){
    int bfs_offsets[8] = { 0, -1, -1, 0, 0, 1, 1, 0 };
    std::queue<std::pair<int, int>> bfs_queue;
    bfs_queue.push({ 0,0 });
    while (!bfs_queue.empty()) {
        auto temp = bfs_queue.front();
        bfs_queue.pop();
        emit updateCell(temp.first, temp.second, QColor::fromHsv(160, 155, 100));
        QThread::msleep(100);  
        auto rows = grid.size();
        auto cols = grid[0].size();
        for (int off = 0; off < 8; off += 2) {
            int new_row = temp.first + bfs_offsets[off];
            int new_col = temp.second + bfs_offsets[off + 1];
            if (new_row >= 0 && new_row < rows &&
                new_col >= 0 && new_col < cols &&
                !grid[new_row][new_col]) {
                grid[new_row][new_col] = true;
                bfs_queue.push({ new_row, new_col });
            }
        }
    }
}
void AlgorithmManager::dfs() {
    int bfs_offsets[8] = { 0, -1, -1, 0, 0, 1, 1, 0 };
    std::stack<std::pair<int, int>> dfs_stack;
    dfs_stack.push({ 0,0 });
    while (!dfs_stack.empty()) {
        auto temp = dfs_stack.top();
        dfs_stack.pop();
        emit updateCell(temp.first, temp.second, QColor::fromHsv(160, 155, 100));
        QThread::msleep(100);
        auto rows = grid.size();
        auto cols = grid[0].size();
        for (int off = 0; off < 8; off += 2) {
            int new_row = temp.first + bfs_offsets[off];
            int new_col = temp.second + bfs_offsets[off + 1];
            if (new_row >= 0 && new_row < rows &&
                new_col >= 0 && new_col < cols &&
                !grid[new_row][new_col]) {
                grid[new_row][new_col] = true;
                dfs_stack.push({ new_row, new_col });
            }
        }
    }
}


