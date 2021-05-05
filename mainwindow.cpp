#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeMatrixModificationButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeMatrixModificationButtons()
{
    static QTableWidget *matrixWidgets[2] {ui->aMatrixTable, ui->bMatrixTable};
    const QPushButton *matrixButtons[2][4] {
        {
            ui->aMatAddRowButton, ui->aMatAddColumnButton,
            ui->aMatRemoveRowButton, ui->aMatRemoveColumnButton
        },
        {
            ui->bMatAddRowButton, ui->bMatAddColumnButton,
            ui->bMatRemoveRowButton, ui->bMatRemoveColumnButton
        }
    };
    const int deltas[4][2] {
        {  0,  1 }, {  1, 0  },
        {  0, -1 }, { -1, 0  }
    };
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            connect(matrixButtons[i][j], &QPushButton::clicked, this, [=] { changeMatrixSize(*matrixWidgets[i], deltas[j][0], deltas[j][1]); });
        }
    }
}

void MainWindow::changeMatrixSize(QTableWidget &matrix, int dw, int dh)
{
    int columns = matrix.columnCount(), rows = matrix.rowCount();
    columns += dw;
    rows += dh;

    matrix.setColumnCount(columns);
    matrix.setRowCount(rows);
}

QTableWidget *operator>>(QTableWidget *display, Matrix &input) {
    unsigned int width = display->columnCount(), height = display->rowCount();
    input.resize(width, height);

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            input[i][j] = ensureItem(display, i, j)->text().toDouble();
        }
    }

    return display;
}

QTableWidget *operator<<(QTableWidget *display, const Matrix &output) {
    unsigned int width = output.getWidth(), height = output.getHeight();
    display->setColumnCount(width);
    display->setRowCount(height);

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            ensureItem(display, i, j)->setText(QString::number(output[i][j]));
        }
    }

    return display;
}

QTableWidgetItem *ensureItem(QTableWidget *table, int i, int j)
{
    QTableWidgetItem *item = table->item(i, j);
    if (item == nullptr) {
        item = new QTableWidgetItem();
        table->setItem(i, j, item);
    }
    return item;
}

void MainWindow::performMath(std::function<Matrix (Matrix&, Matrix&)> operation)
{
    Matrix a, b;
    ui->aMatrixTable >> a;
    ui->bMatrixTable >> b;

    try {
        Matrix result = operation(a, b);
        ui->resultMatrixTable << result;
    }  catch (const std::exception &e) {
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Error occured");
        messageBox.setText(QString::fromLatin1(e.what(), -1));
        messageBox.exec();
    }
}


void MainWindow::on_plusButton_clicked()
{
    performMath([=] (Matrix &a, Matrix &b) { return a + b; });
}

void MainWindow::on_minusButton_clicked()
{
    performMath([=] (Matrix &a, Matrix &b) { return a - b; });
}

void MainWindow::on_multiplyButton_clicked()
{
    performMath([=] (Matrix &a, Matrix &b) { return a * b; });
}
