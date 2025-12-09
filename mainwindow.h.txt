#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#define MAX 5   // stack size
#include<QFrame>
#include<QVector>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_popButton_clicked();
    void on_peekButton_clicked();
    void on_emptyButton_clicked();
    void on_fullButton_clicked();
    void updateStackColor();

private:
    Ui::MainWindow *ui;
    QFrame* bookBoxes[MAX];
    QString stack[MAX];
    int top;
};

#endif // MAINWINDOW_H
