#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "Open Directory");
    if (!dirPath.isEmpty())
        ui->lblDirectory->setText(dirPath);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                "Open File",
                "",
                "Text File(*.txt);; All File(*.*)");
    ui->lblOpenFile->setText(path);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString path = QFileDialog::getSaveFileName(
                this,
                "Save File",
                "",
                "Text File(*.txt);; All File(*.*)");
    ui->lblSaveFile->setText(path);
}

void MainWindow::on_btnClear_clicked()
{
    ui->txtEdit->clear();
}

void MainWindow::on_btnLoad_clicked()
{
    QFile file("/home/tuan2772/outputMores.txt");
    QTextStream textStream(&file);
    if (file.open(QIODevice::ReadOnly))
    {
        QString str = textStream.readAll();
        ui->txtEdit->setPlainText(str);
        LongestSubstringResult result = LengthOfLongestString(str);
        ui->txtEditout->setPlainText(QString("Longest Substring: %1\nLength: %2").arg(result.substring).arg(result.length));
        file.close();
    }
    else {
        QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
    }
}

void MainWindow::on_btnSave_clicked()
{
    QFile file("/home/tuan2772/outputMores.txt");
    QTextStream textStream(&file);
    if (file.open(QIODevice::WriteOnly))
    {
        QString str = ui->txtEdit->toPlainText();
        textStream << str;
        file.close();
    }
    else {
        QMessageBox::critical(this, "Error", "Can not open file. Please check again.");
    }
}

MainWindow::LongestSubstringResult MainWindow::LengthOfLongestString(const QString &s)
{
    int n = s.length();
    int index[128];
    int maxLength = 0;
    int start = 0;
    int maxStart = 0;

    for (int i = 0; i < 128; i++) {
        index[i] = -1;
    }

    for (int end = 0; end < n; end++) {
        QChar currentChar = s[end];

        // Nếu ký tự hiện tại đã xuất hiện trước đó và nằm trong khoảng của cửa sổ hiện tại
        if (index[currentChar.unicode()] >= start) {
            start = index[currentChar.unicode()] + 1;
        }

        // Cập nhật vị trí xuất hiện cuối cùng của ký tự hiện tại
        index[currentChar.unicode()] = end;

        // Tính độ dài chuỗi con hiện tại và cập nhật maxLength nếu cần thiết
        int currentLength = end - start + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
            maxStart = start;
        }
    }

    QString longestSubstring = s.mid(maxStart, maxLength);
    return {maxLength, longestSubstring};
}
