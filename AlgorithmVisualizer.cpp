#include "AlgorithmVisualizer.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGridLayout>
#include <QWidget>
#include <QThread>
#include <QTimer>
AlgorithmVisualizer::AlgorithmVisualizer(QWidget *parent)
    : QMainWindow(parent), gridDisplay(new GridDisplay(this)){
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->addWidget(gridDisplay);
    dfsButton = new QPushButton("Run DFS", this);
    layout->addWidget(dfsButton);
    bfsButton = new QPushButton("Run BFS", this);
    layout->addWidget(bfsButton);
    connect(dfsButton, &QPushButton::clicked, this, &AlgorithmVisualizer::requestDFS);
    connect(bfsButton, &QPushButton::clicked, this, &AlgorithmVisualizer::requestBFS);
}
AlgorithmVisualizer::~AlgorithmVisualizer()
{
}
GridDisplay::GridDisplay(QWidget* parent) 
    : QWidget(parent){

    m_scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(m_scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(500, 500);
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    int rows = 10;
    int cols = 10;
    int cellSize = 40;
    // populate vector of vector<rects> with rects
    gridCells.resize(rows);
    for (int x = 0; x < rows; x++) {
        gridCells[x].resize(cols);
        for (int y = 0; y < cols; y++) {
            QColor color = QColor::fromHsv(360, 255, 200);
            QGraphicsRectItem* rect = m_scene->addRect(
                y * cellSize,
                x * cellSize,
                cellSize,
                cellSize,
                QPen(Qt::red),
                QBrush(color)
            );
            gridCells[x][y] = rect;  //cells hold pointer to rect
        }
    }
}
void GridDisplay::onCellUpdated(int row, int col, QColor color){
    {
        if(row >= 0 && row < (int)gridCells.size() &&
            col >= 0 && col < (int)gridCells[0].size())
        {
            gridCells[row][col]->setBrush(QBrush(color));
            GridDisplay::m_scene->update();
        }
    }
}
AlgorithmManager::AlgorithmManager(QObject* parent)
    : QObject(parent), grid(10, std::vector<bool>(10, false)), workerThread(new QThread(this)) {
     {      // We instantiated a thread in the intitializer list and we're moving this instance 
            // of algo manager to that worker thread
            this->moveToThread(workerThread);
            connect(this, &AlgorithmManager::finish, this, [this]() {
                QTimer::singleShot(0, this, &AlgorithmManager::reset);
                });
            workerThread->start();
     }

}
AlgorithmManager::~AlgorithmManager() {
    if (workerThread->isRunning()) {
        workerThread->quit();
        workerThread->wait();
    }
}
void AlgorithmManager::cellUpdated(int row, int col, QColor color) {
    if (grid[row][col] == false) {
        grid[row][col] = true;
        emit updateCell(row, col, color);
    }
}
void AlgorithmManager::cellReset(int row, int col) {
    if (grid[row][col] == true) {
        grid[row][col] = false;
        emit updateCell(row, col, QColor::fromHsv(360, 255, 200));
    }
}
GridDisplay* AlgorithmVisualizer::getGridDisplay() {
    return gridDisplay;
}
void AlgorithmManager::start() {
    workerThread->start();
}
void AlgorithmManager::startDFS() {
    dfs();
    QTimer::singleShot(1000, this, [this]() {
        emit finish();
    });
    
}
void AlgorithmManager::startBFS() {
    bfs();
    emit finish();
}
void AlgorithmManager::reset() {
    for (int i = 0;i < grid.size();i++) {
        for (int j = 0;j < grid.size();j++) {
            cellReset(i, j);
        }
    }
}