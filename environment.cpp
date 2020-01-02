#include "environment.h"

#include <iostream>
#include <string>
#include <regex>

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>



void ClearConsole()
{
    std::cout << "\x1B[2J\x1B[H" << std::endl;
}

void PressToContinue()
{
    std::cout << "\nTo continue, press any key..."
              << std::endl;

    std::cin.get();
    std::cin.get();
}

void ShowMenu()
{
    std::cout   << " Menu:"
                << "\n 1.Add flight"
                << "\n 2.Edit flight"
                << "\n 3.Remove flight"
                << "\n 4.Find flights operated by air"
                << "\n 5.Display the entire list of flights"
                << "\n 6.Sort flights list"
                << "\n 7.Save database"
                << "\n 8.Load database"
                << "\n 0.Exit"
                << std::endl;
}

int GetIntValue()
{
    bool bFirst = true;

    bool bCheck = false;

    const std::regex regex("(\\+|-)?[[:digit:]]+");

    std::string strValue;

    do
    {
        if (bFirst)
        {
            bFirst = false;
        }
        else
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. The value must be integer." << std::endl;
        }

        strValue = GetStringValue();

        bCheck = regex_match(strValue, regex);

    } while(!bCheck);

    int iValue = atoi(strValue.c_str());

    return iValue;
}


std::string GetStringValue()
{
    bool bFirst = true;
    std::string strValue;

    do
    {
        if (bFirst)
        {
            bFirst = false;
        }
        else
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. The value must be a string.\n";
        }

        std::cin >> strValue;

    } while (!std::cin.good());

    return strValue;
}

ERRORS SaveToFile(const QJsonArray &jArr, const std::string &strName)
{
    if(jArr.isEmpty() || strName.empty())
    {
        return ERRORS::INVALID_ARGUMENT;
    }

    const QString strFileName = QString::fromStdString(strName);
    QFile saveFile(strFileName);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        return ERRORS::FILE_OPEN_ERROR;
    }

    QJsonDocument saveDoc(jArr);
    saveFile.write(saveDoc.toJson());

    return ERRORS::NO_ERROR;
}

QJsonArray LoadFromFile(const std::string &strName, ERRORS *pError)
{
    if(strName.empty())
    {
        if(pError != nullptr)
        {
            *pError = ERRORS::INVALID_ARGUMENT;
        }

        return {};
    }

    const QString strFileName = QString::fromStdString(strName);
    QFile loadFile(strFileName);

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        if(pError != nullptr)
        {
            *pError = ERRORS::FILE_OPEN_ERROR;
        }

        return {};
    }

    QByteArray arrData = loadFile.readAll();

    QJsonDocument loadDoc = QJsonDocument::fromJson(arrData);

    if(pError != nullptr)
    {
        *pError = ERRORS::NO_ERROR;
    }

    return loadDoc.array();
}
