#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

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
    void process_python(QString);
    void OnReadData();
    void on_selectButton_clicked();
signals:
    void filePath(const QString);

private:
    Ui::MainWindow *ui;
    QProcess* process1;
};
#endif // MAINWINDOW_H
