#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //qDebug() << "Freeze 4";
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUi()
{

    QString tempUi;
    ui->champName->setText(champ.getName());
    ui->champTitle->setText(champ.getTitle());
    ui->champRegion->setText(champ.getRegion());

    tempUi = "Health: X (+Y per level)";
    //qDebug() << tempUi;
    tempUi.replace("X",QString::number(champ.getHealth()));
    tempUi.replace("Y",QString::number(champ.getHealthPerLevel()));
    ui->health->setText(tempUi);

    tempUi = "Health Regen: X (+Y per level) ";
    tempUi.replace("X",QString::number(champ.getHealthRegen()));
    tempUi.replace("Y",QString::number(champ.getHealthRegenPerLevel()));
    ui->healthRegen->setText(tempUi);

    tempUi = "Mana: X (+Y per level) ";
    tempUi.replace("X",QString::number(champ.getMana()));
    tempUi.replace("Y",QString::number(champ.getManaPerLevel()));
    ui->mana->setText(tempUi);

    tempUi = "Mana Regen: X (+Y per level) ";
    tempUi.replace("X",QString::number(champ.getManaRegen()));
    tempUi.replace("Y",QString::number(champ.getManaRegenPerLevel()));
    ui->manaRegen->setText(tempUi);

    tempUi = "Attack Damage: X \n(+Y per level)";
    tempUi.replace("X",QString::number(champ.getAttackDamage()));
    tempUi.replace("Y",QString::number(champ.getAttackDamagePerLevel()));
    ui->attackDamage->setText(tempUi);

    tempUi = "Armor: X (+Y per level)";
    tempUi.replace("X",QString::number(champ.getArmor()));
    tempUi.replace("Y",QString::number(champ.getArmorPerLevel()));
    ui->armor->setText(tempUi);

    tempUi = "Attack Speed:X \n(+Y% per level)";
    tempUi.replace("X",QString::number(champ.getAttackSpeed()));
    tempUi.replace("Y",QString::number(champ.getAttackSpeedPerLevel()));
    ui->attackSpeed->setText(tempUi);

    tempUi = "Magic Resist: X (+Y per level)";
    tempUi.replace("X",QString::number(champ.getMagicResist()));
    tempUi.replace("Y",QString::number(champ.getMagicResistPerLevel()));
    ui->magicResist->setText(tempUi);

    tempUi = "Movement Speed: X";
    tempUi.replace("X",QString::number(champ.getMovementSpeed()));
    ui->movementSpeed->setText(tempUi);
}

//-----Networking--------------
//calls the webside and pulls the full html code into champPageUrl
void MainWindow::httpCall()
{
    //qDebug() << "Freeze 1";
    // create custom temporary event loop on stac

    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QUrl url = champ.getChampPageUrl();


    QNetworkRequest req( url );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    //QString code = reply;

    if (reply->error() == QNetworkReply::NoError) {

        //qDebug() << "Line 42: code Written";

        champ.setHtmlCode(reply->readAll());

    }
    else {
        //failure
        //qDebug() << reply->errorString();
        delete reply;
    }
}

//takes the champImgUrl and a filePath given and saves the champion image to that path
void MainWindow::downloadFileFromURL(const QString &url, const QString &filePath)
{
    // qDebug() << "Freeze 2";
    if (!m_isReady)
        return;
    m_isReady = false;


    const QString fileName = filePath; // your filePath should end with a forward slash "/"
    //  qDebug() << "Line 116:"<< fileName;
    m_file = new QFile();
    m_file->setFileName(fileName);
    m_file->open(QIODevice::WriteOnly);
    if (!m_file->isOpen()) {
        m_isReady = true;
        //  qDebug() << "in isNotOpen";
        return; // TODO: permission check?
    }
    QEventLoop eventLoop;
    QNetworkAccessManager manager;

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    //  connect(&manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(onDownloadFileComplete(QNetworkReply *)));
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = manager.get(request);
    // qDebug() << eventLoop.isRunning();

    eventLoop.exec();
    //qDebug() << eventLoop.exec();
    if (!m_file->isWritable()) {
        m_isReady = true;
        //return; // TODO: error check
        //  qDebug() << "In isWritable";
    }else{
        m_file->write(reply->readAll());
        m_file->close(); // TODO: delete the file from the system later on
        m_isReady = true;
    }


    // qDebug() << "Line 133: " << fileName;
    champ.setChampSaveLocation(fileName);
}


void MainWindow::on_champList_clicked(const QModelIndex &index)
{
    champ.reset();
    ui->progressBar->setValue(20);
    champ.setStrings(ui->champList->currentItem()->text());
    ui->progressBar->setValue(40);
    downloadFileFromURL(champ.getChampImgUrl(),champ.getChampSaveLocation());
    //qDebug() << "Line 100: " << ui->champList->currentItem()->text();

    httpCall();
    ui->progressBar->setValue(60);
    champ.setStats();
    ui->progressBar->setValue(80);
    setUi();
    ui->champImg->setPixmap(champ.getChampSaveLocation());
    ui->progressBar->setValue(100);

}

void MainWindow::on_goToSite_clicked()
{
    QDesktopServices::openUrl(QUrl(champ.getChampPageUrl()));
}
