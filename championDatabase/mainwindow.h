#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "champion.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUi();
    //Downloads the html code from the site provided into champHtmlCode
    void httpCall();
    //Downloads Champion Image
    void downloadFileFromURL(const QString &url, const QString &filePath);

private slots:

    void on_champList_clicked(const QModelIndex &index);

    void on_goToSite_clicked();

private:
    Ui::MainWindow *ui;
    //instance of the champion class
    champion champ;
    QFile *m_file;
    bool m_isReady = true;
    champion champList[128];
    int champCount = 0;
};

#endif // MAINWINDOW_H
