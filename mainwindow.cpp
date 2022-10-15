#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(100,100,800,600);
    QMenu *fileMenu = new QMenu("File");
    menuBar()->addMenu(fileMenu);
    QAction *actOpen = new QAction("Open text file");
    actOpen->setShortcut(QKeySequence::Open);
    QAction *actSave = new QAction("Save text file");
    actSave->setShortcut(QKeySequence::Save);
    QAction *actQuit = new QAction("Quit");
    actQuit ->setShortcut(QKeySequence::Quit);

    fileMenu -> addAction(actOpen);
    fileMenu -> addAction(actSave);
    fileMenu->addSeparator();
    fileMenu -> addAction(actQuit);


    m_memo = new QTextEdit();

//    m_memo->setTextBackgroundColor(QColor::black());
    setCentralWidget(m_memo);
    m_memo->acceptRichText();

    connect(actQuit,&QAction::triggered,this,&MainWindow::close);
    connect(actSave,&QAction::triggered,this,&MainWindow::safeTF);
    connect(actOpen,&QAction::triggered,this,&MainWindow::openTF);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openTF()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Simple np","","Text file (*.txt)");
    if (!filePath.isEmpty()){
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream out(&file);
            m_memo->setText(out.readAll());
            file.close();
        }else QMessageBox::critical(this,"Simple np","Cannot open file!!");
    }
}

void MainWindow::safeTF()
{
    QString filePath = QFileDialog::getSaveFileName(this,"Simple np","","Text file (*.txt)");
    if (!filePath.isEmpty()){
        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream in(&file);
            in << m_memo->toPlainText();
            file.close();
        }else QMessageBox::critical(this,"Simple np","Cannot open file!!");
    }
}


