#pragma once
#include <QtWidgets/QMainWindow>
#include "AlgorithmVisualizer.h"
#include <vector>
#include <QGraphicsRectItem>
#include <QPushButton>
class GridDisplay;


class AlgorithmVisualizer : public QMainWindow{
    Q_OBJECT

    public:
        AlgorithmVisualizer(QWidget* parent = nullptr);
        ~AlgorithmVisualizer();
        GridDisplay* getGridDisplay();  

    signals:
        void requestBFS();
        void requestDFS(); 

    private:
        GridDisplay* gridDisplay;
        QPushButton* dfsButton;
        QPushButton* bfsButton;
    
};


class GridDisplay : public QWidget{

    Q_OBJECT

    public:
        QGraphicsScene* m_scene;
        std::vector<std::vector<QGraphicsRectItem*>> gridCells;
        GridDisplay(QWidget* parent = nullptr);
    
    public slots:
        void onCellUpdated(int row, int col, QColor color);

};


class AlgorithmManager : public QObject {

    Q_OBJECT

    public:  
        void cellReset(int row, int col);
        void cellUpdated(int row, int col, QColor color);
        std::vector<std::vector<bool>> grid;
        void bfs();
        void dfs();
        AlgorithmManager(QObject* parent = nullptr);
        void start();
        ~AlgorithmManager();

    public slots:
        void startDFS();
        void startBFS();
        void reset();

    private:
        QThread* workerThread;

    signals:
        void finish();
        void updateCell(int row, int col, QColor color);

};
