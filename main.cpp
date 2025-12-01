#include <QtWidgets/QApplication>
#include "Algorithms.h"
#include "vector"
#include <QObject>
#include <QTimer>
#include <QThread>
#include <QApplication>
#include <AlgorithmVisualizer.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AlgorithmManager* manager = new AlgorithmManager();
    AlgorithmVisualizer window;
    window.show();

    //connects algomanager signals to griddisplay/algovisualizer slots
    //this needs to be redone, these connections don't belong here. 
    //think up a flexible system for creating and connecting buttons without redundancy and hardcoding
    QObject::connect(manager, &AlgorithmManager::updateCell,
        window.getGridDisplay(), &GridDisplay::onCellUpdated);
    QObject::connect(&window, &AlgorithmVisualizer::requestDFS,
        manager, &AlgorithmManager::startDFS);
    QObject::connect(&window, &AlgorithmVisualizer::requestBFS,
        manager, &AlgorithmManager::startBFS);
    return app.exec();
    
}
