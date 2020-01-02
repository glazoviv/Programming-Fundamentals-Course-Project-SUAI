#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include "errors.h"

typedef __SIZE_TYPE__ size_t;

class QJsonArray;

void ShowMenu();

void PressToContinue();

void ClearConsole();



int GetIntValue();

std::string GetStringValue();


std::string GetDestination();



ERRORS SaveToFile(const QJsonArray& jArr, const std::string& strName);

QJsonArray LoadFromFile(const std::string& strName, ERRORS* pError = nullptr);

#endif // ENVIRONMENT_H
