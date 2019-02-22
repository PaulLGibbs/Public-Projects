#include "champion.h"
#include <QNetworkAccessManager>

champion::champion()
{
    name = "NULL";
    title = "NULL";
    region = "NULL";

    health = 0;
    healthPerLevel= 0;

    healthRegen = 0;
    healthRegenPerLevel = 0;

    mana = 0;
    manaPerLevel = 0;

    manaRegen = 0;
    manaRegenPerLevel = 0;

    attackDamage = 0;
    attackDamagePerLevel = 0;

    armor = 0;
    armorPerLevel = 0;

    attackSpeed = 0;
    attackSpeedPerLevel = 0;

    magicResist = 0;
    magicResistPerLevel = 0;

    movementSpeed = 0;

    //for networking
    //CHAMPNAME MUST BE ALL LOWER CASE
    QString champPageUrl = "http://gameinfo.na.leagueoflegends.com/en/game-info/champions/CHAMPNAME/";
    //CHAMPNAME MUST START WITH A CAPITAL
    QString champImgUrl = "http://ddragon.leagueoflegends.com//cdn/6.24.1//img//champion//CHAMPNAME.png";
    QString champHtmlCode;
    QString champSaveLocation = "assets\\";
}

void champion::reset()
{
    name = "NULL";
    title = "NULL";
    region = "NULL";

    health = 0;
    healthPerLevel= 0;

    healthRegen = 0;
    healthRegenPerLevel = 0;

    mana = 0;
    manaPerLevel = 0;

    manaRegen = 0;
    manaRegenPerLevel = 0;

    attackDamage = 0;
    attackDamagePerLevel = 0;

    armor = 0;
    armorPerLevel = 0;

    attackSpeed = 0;
    attackSpeedPerLevel = 0;

    magicResist = 0;
    magicResistPerLevel = 0;

    movementSpeed = 0;

    //for networking
    //CHAMPNAME MUST BE ALL LOWER CASE
    champPageUrl = "http://gameinfo.na.leagueoflegends.com/en/game-info/champions/CHAMPNAME/";

    //CHAMPNAME MUST START WITH A CAPITAL
    champImgUrl = "http://ddragon.leagueoflegends.com//cdn/6.24.1//img//champion//CHAMPNAME.png";
    champHtmlCode = "NULL";
    champSaveLocation = "assets\\";
}
//
void champion::setStrings(QString name)
{
    if(name.contains(" ")){
        name.remove(" ");
        // qDebug() << "Line 113: space removed" << name;
    }
    if(name.contains(".")){
        name.remove(".");
        //qDebug() << "Line 117: period removed" << name;
    }
    if(name.contains("'")){

        name.remove("'");
        qDebug() << name;
        if(name != "KogMaw" || name != "RekSai"){
            name =  name.toLower();
            name[0] = name[0].toUpper();
            //qDebug() << name;
            //qDebug() << "Line 121: ' removed" << name;
        }
    }
    champPageUrl.replace("CHAMPNAME",name.toLower());
    //qDebug() << "Line 124: " << champPageUrl;

    champImgUrl.replace("CHAMPNAME",name);
    //qDebug() << "Line 127: " << champImgUrl;

    champSaveLocation.append(name);
    champSaveLocation.append(".png");
    qDebug() << "Line 130: " << champSaveLocation;


}
//This does a lot of the Networking, and will set stats for the champ called
void champion::setStats()
{
    QString champCode = champHtmlCode;

    QRegularExpression champName("<h1>(.*)<\\/h1>");
    QRegularExpressionMatch matchName = champName.match(champCode);
    name = matchName.captured(1);
    qDebug() << champCode;
    //qDebug() << name;
    QRegularExpression champTitle("<h3><em>(.*)<\\/em><\\/h3>");
    QRegularExpressionMatch matchTitle = champTitle.match(champCode);
    title = matchTitle.captured(1);
    title.trimmed();
    //qDebug() << title;
    QRegularExpression champRegion("<div class='faction.*>\\n\\s+(\\w+|\\w+\\s\\w+|\\w+\\s\\w+\\s\\w+)");
    QRegularExpressionMatch matchRegion = champRegion.match(champCode);
    region = matchRegion.captured(1);
    //region.replace("\\s+","");
    //qDebug() << region;


    //Pulls champion health from code
    QRegularExpression champHealth("Health:\\n.*\\s.*\\n.*\\s.*\\n.*\\s(\\d+\\.\\d+|\\d+)\\s\\(\\+(\\d+\\.\\d+|\\d+) .*\\)");//use cap 1
    //cap 3 is for HealthPerLevel
    QRegularExpressionMatch matchHealth = champHealth.match(champCode);
    //qDebug() <<"Line 138: " <<  matchHealth.hasMatch();
    QString tempCH;
    if(matchHealth.hasMatch()){
        tempCH = matchHealth.captured(1);

        health = tempCH.toDouble();
        //qDebug() << "Line 137: " << health;
        tempCH = matchHealth.captured(2);
        healthPerLevel = tempCH.toInt();
        //qDebug() << "Line 139: " << healthPerLevel;
    }

    //pulls champion health regen from the code
    QRegularExpression champHealthRegen("Health Regen:\\n.*\\s.*\\n.*\\s.*\\n.*\\s(\\d+\\.\\d+|\\d+)\\s\\(\\+(\\d+\\.\\d+|\\d+).*\\)");//use cap 1
    //cap 3 is for HealthRegenPerLevel
    QRegularExpressionMatch matchHealthRegen = champHealthRegen.match(champCode);
    QString tempCHR;
    if(matchHealthRegen.hasMatch()){
        tempCHR = matchHealthRegen.captured(1);
        // qDebug() << tempCHR;
        healthRegen = tempCHR.toDouble();
        tempCHR = matchHealthRegen.captured(2);
        //qDebug() << tempCHR;
        healthRegenPerLevel = tempCHR.toDouble();
    }

    //pulls champion mana from code NOTE NOT ALL CHAMPS HAVE MANA
    QRegularExpression champMana("Mana:\\n.*\\s.*\\n.*\\s.*\\n.*\\s(\\d+\\.\\d+|\\d+)\\s\\(\\+(\\d+).*\\)");//use cap 1
    //cap 3 is for ManaPerLevel
    QRegularExpressionMatch matchMana = champMana.match(champCode);
    QString tempCM;
    if(matchMana.hasMatch()){
        tempCM = matchMana.captured(1);
        //qDebug() << tempCM;
        mana = tempCH.toDouble();
        tempCM = matchMana.captured(2);
        //qDebug() << tempCM;
        manaPerLevel = tempCM.toDouble();
    }else{
        //qDebug() << "Youre champ has no mana";
        mana = 0;
        manaPerLevel = 0;
    }

    //pulls champManaRegen from code
    QRegularExpression champManaRegen("Mana Regen:\\n.*\\s.*\\n.*\\s.*\\n.*\\s(\\d+\\.\\d+|\\d+)\\s\\(\\+(\\d+\\.\\d+|\\d+).*\\)");//use cap 1
    //use cap 3 for ManaRegenPerLevel
    QRegularExpressionMatch matchManaRegen = champManaRegen.match(champCode);
    QString tempCMR;
    if(matchManaRegen.hasMatch()){
        tempCMR = matchManaRegen.captured(1);
        //qDebug() << tempCMR;
        manaRegen = tempCHR.toDouble();
        tempCMR = matchManaRegen.captured(2);
        //qDebug() << tempCMR;
        manaRegenPerLevel = tempCMR.toDouble();
    }
    //pulls champ AD from code
    QRegularExpression champAttackDamage("Damage:\\n.*\\s.*\\n.*\\s.*\\n.*\\s(\\d+\\.\\d+|\\d+)\\s\\(\\+(\\d+\\.\\d+|\\d+).*\\)");//cap 1
    //cap 3 is for AttackDamagePerLevel
    QRegularExpressionMatch matchAttackDamage = champAttackDamage.match(champCode);
    QString tempCAD;
    if(matchAttackDamage.hasMatch()){
        tempCAD = matchAttackDamage.captured(1);
        //qDebug() << tempCAD;
        attackDamage = tempCAD.toDouble();
        tempCAD = matchAttackDamage.captured(2);
        //qDebug() << tempCAD;
        attackDamagePerLevel = tempCAD.toDouble();
    }

    //pulls champ armor
    QRegularExpression champArmor("Armor:\\n.*\\s.*\\n.*\\s.*\\n.*\\s(\\d+\\.\\d+|\\d+)\\s\\(\\+(\\d+\\.\\d+|\\d+).*\\)");//cap 1
    //cap 3 for ArmorPerLevel
    QRegularExpressionMatch matchArmor = champArmor.match(champCode);
    QString tempAR;
    if(matchArmor.hasMatch()){
        tempAR = matchArmor.captured(1);
        //qDebug() << tempAR;
        armor = tempAR.toDouble();
        tempAR = matchArmor.captured(2);
        //qDebug() << tempAR;
        armorPerLevel = tempAR.toDouble();
    }

    //pulls attack speed
    QRegularExpression champAttackSpeed("Speed:\\n.*\\s.*\\n.*\\s.*\\n.*\\s(\\d+\\.\\d+|\\d+)\\s\\(\\+(\\d+\\.\\d+|\\d+).*\\)");//use cap 1
    //cap 3 is for AttackSpeedPerLevel
    QRegularExpressionMatch matchAttackSpeed = champAttackSpeed.match(champCode);
    QString tempAS;
    if(matchAttackSpeed.hasMatch()){
        tempAS = matchAttackSpeed.captured(1);
        //qDebug() << tempAS;
        attackSpeed = tempAS.toDouble();
        tempAS = matchAttackSpeed.captured(2);
        //qDebug() << tempAS;
        attackSpeedPerLevel = tempAS.toDouble();
    }

    //pulls MR from code NOT ALL CHAMPS HAVE MR PER LEVEL
    QRegularExpression champMagicResist("Resist:\\n.*\\s.*\\n.*\\s.*\\n.*\\s(\\d+\\.\\d+|\\d+)\\s\\(\\+(\\d+\\.\\d+|\\d+).*\\)");//use cap 1
    //cap 3 is for MagicResistPerLevel
    QRegularExpressionMatch matchMagicResist = champMagicResist.match(champCode);
    QString tempMR;
    if(matchMagicResist.hasMatch()){
        tempMR = matchMagicResist.captured(1);
        //qDebug() << tempMR;
        magicResist = tempMR.toDouble();
        tempMR = matchMagicResist.captured(2);
        //qDebug() << tempMR;
        if(tempMR != 0){
            magicResistPerLevel = tempMR.toDouble();
        }else{
            magicResistPerLevel = 0;
        }
    }
    //pulls Movement speed from code
    QRegularExpression champMoveSpeed("Speed:\\n.*\\s.*\\n.*\\s.*\\n.*\\s([0-9]{3})");//use cap 1
    QRegularExpressionMatch matchMoveSpeed = champMoveSpeed.match(champCode);
    QString tempMS;
    if(matchMoveSpeed.hasMatch()){
        tempMS = matchMoveSpeed.captured(1);
        //qDebug() << tempMS;
        movementSpeed = tempMS.toInt();
    }
}


QString champion::getChampPageUrl()
{
    return champPageUrl;
}


QString champion::getChampImgUrl()
{
    return champImgUrl;
}

void champion::setHtmlCode(QString reply)
{
    champHtmlCode = reply;
}

QString champion::getChampSaveLocation()
{
    return champSaveLocation;
}

void champion::setChampSaveLocation(QString path)
{
    champSaveLocation = path;
}

QString champion::getName()
{
    return name;
}

QString champion::getTitle()
{
    return title;
}

QString champion::getRegion()
{
    return region;
}

double champion::getHealth()
{
    return health;
}

double champion::getHealthPerLevel()
{
    return healthPerLevel;
}

double champion::getHealthRegen()
{
    return healthRegen;
}

double champion::getHealthRegenPerLevel()
{
    return healthRegenPerLevel;
}

double champion::getMana()
{
    return mana;
}

double champion::getManaPerLevel()
{
    return manaPerLevel;
}

double champion::getManaRegen()
{
    return manaRegen;
}

double champion::getManaRegenPerLevel()
{
    return manaRegenPerLevel;
}

double champion::getAttackDamage()
{
    return attackDamage;
}

double champion::getAttackDamagePerLevel()
{
    return attackDamagePerLevel;
}

double champion::getArmor()
{
    return armor;
}

double champion::getArmorPerLevel()
{
    return armorPerLevel;
}

double champion::getAttackSpeed()
{
    return attackSpeed;
}

double champion::getAttackSpeedPerLevel()
{
    return attackSpeedPerLevel;
}

double champion::getMagicResist()
{
    return magicResist;
}

double champion::getMagicResistPerLevel()
{
    return magicResistPerLevel;
}

int champion::getMovementSpeed()
{
    return movementSpeed;
}


