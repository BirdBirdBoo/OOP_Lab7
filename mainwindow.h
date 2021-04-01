#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <matrix.h>

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

    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_multiplyButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void initializeMatrixModificationButtons();
    void changeMatrixSize(QTableWidget *matric, int dw, int dh);

    void performMath(std::function<Matrix(Matrix&, Matrix&)> operation);

    void testOutput();
};
QTableWidgetItem *ensureItem(QTableWidget *table, int i, int j);

QTableWidget *operator>>(QTableWidget *display, Matrix &input);
QTableWidget *operator<<(QTableWidget *display, const Matrix &output);
#endif // MAINWINDOW_H
