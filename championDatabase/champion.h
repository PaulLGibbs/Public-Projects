#ifndef CHAMPION_H
#define CHAMPION_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QImage>
#include <QPixmap>

#include <QFile>
#include <QLabel>
#include <QRegularExpression>


class champion
{

private:
    //Everything that a champ whiil have:
    QString name;
    QString title;
    QString region;

    double health;
    double healthPerLevel;

    double healthRegen;
    double healthRegenPerLevel;

    double mana;
    double manaPerLevel;

    double manaRegen;
    double manaRegenPerLevel;

    double attackDamage;
    double attackDamagePerLevel;

    double armor;
    double armorPerLevel;

    double attackSpeed;
    double attackSpeedPerLevel;

    double magicResist;
    double magicResistPerLevel;

    int movementSpeed;

    //for networking
    //CHAMPNAME MUST BE ALL LOWER CASE
    QString champPageUrl;
    //CHAMPNAME MUST START WITH A CAPITAL
    QString champImgUrl;
    QString champHtmlCode;
    QString champSaveLocation;


public:
    //Constructor
    champion();
    //resets the info when a new champ is chosen
    void reset();
    //sets the champion strings when a name is chosen
    void setStrings(QString name);
    //can only be ran after httpCall() is done
    void setStats();
    QString getChampPageUrl();
    QString getChampImgUrl();
    void setHtmlCode(QString reply);
    QString getChampSaveLocation();
    void setChampSaveLocation(QString path);

    //ALL GETTERS TO SEND TO UI
    QString getName();
    QString getTitle();
    QString getRegion();

    double getHealth();
    double getHealthPerLevel();

    double getHealthRegen();
    double getHealthRegenPerLevel();

    double getMana();
    double getManaPerLevel();

    double getManaRegen();
    double getManaRegenPerLevel();

    double getAttackDamage();
    double getAttackDamagePerLevel();

    double getArmor();
    double getArmorPerLevel();

    double getAttackSpeed();
    double getAttackSpeedPerLevel();

    double getMagicResist();
    double getMagicResistPerLevel();

    int getMovementSpeed();
};

#endif // CHAMPION_H
