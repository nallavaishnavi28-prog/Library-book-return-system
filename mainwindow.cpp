#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPropertyAnimation>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    top = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (top == MAX - 1)
    {
        QMessageBox::information(this, "Stack", "Stack is FULL!");
        return;
    }

    QString book = ui->lineEdit->text();
     if (book.isEmpty())
    {
        QMessageBox::warning(this, "Input", "Enter Book Name!");
        return;
    }
    top++;
    stack[top] = book;
    QFrame *box = new QFrame(ui->stackFrame);
    box->setFrameShape(QFrame::Box);
    box->setStyleSheet("background-color: lightblue;");
    box->setFixedSize(140, 30);

    QLabel *label = new QLabel(book, box);
    label->setAlignment(Qt::AlignCenter);

    int startX = 30;
    int startY = 10;

    int endY = 230 - (top * 35);

    box->move(startX, startY);
    box->show();
    QPropertyAnimation *anim = new QPropertyAnimation(box, "pos");
    anim->setDuration(400);
    anim->setStartValue(QPoint(startX, startY));
    anim->setEndValue(QPoint(startX, endY));
    anim->start();

    bookBoxes[top] = box;

    ui->lineEdit->clear();
    ui->stackCountLabel->setText("Stack Size: " + QString::number(top + 1) + " / 5");
    //ui->logListWidget->addItem("PUSH: " + book);
    ui->logListWidget->addItem(QString("PUSH: %1").arg(book));
    updateStackColor();
}


void MainWindow::on_popButton_clicked()
{
    if (top == -1)
    {
        QMessageBox::information(this, "Stack", "Stack is EMPTY!");
        return;
    }

    QFrame *box = bookBoxes[top];
    QString removed = stack[top];
    int startX = box->x();
    int startY = box->y();

    //  Animate box moving UP and OUT
    QPropertyAnimation *anim = new QPropertyAnimation(box, "pos");
    anim->setDuration(400);
    anim->setStartValue(QPoint(startX, startY));
    anim->setEndValue(QPoint(startX, -50));

    connect(anim, &QPropertyAnimation::finished, this, [=]() {
        delete box;
    });

    anim->start();

    top--;
    ui->stackCountLabel->setText("Stack Size: " + QString::number(top + 1) + " / " + QString::number(MAX));
    ui->logListWidget->addItem(QString("POP: %1").arg(removed));
    updateStackColor();
}

void MainWindow::updateStackColor()
{
    if (top == -1)
        ui->stackFrame->setStyleSheet("background-color: #e0ffe0;"); // green
    else if (top == MAX - 1)
        ui->stackFrame->setStyleSheet("background-color: #ffe0e0;"); // red
    else
        ui->stackFrame->setStyleSheet("background-color: #fff7cc;"); // yellow
}


void MainWindow::on_peekButton_clicked()
{
    if (top == -1)
    {
        QMessageBox::information(this, "Stack", "Stack is EMPTY!");
        return;
    }

    QMessageBox::information(this, "Top Book", "Top Book: " + stack[top]);
}


void MainWindow::on_emptyButton_clicked()
{
    if (top == -1)
        QMessageBox::information(this, "Stack", "Stack is EMPTY");
    else
        QMessageBox::information(this, "Stack", "Stack is NOT empty");
}

void MainWindow::on_fullButton_clicked()
{
    if (top == MAX - 1)
        QMessageBox::information(this, "Stack", "Stack is FULL");
    else
        QMessageBox::information(this, "Stack", "Stack is NOT full");
}

