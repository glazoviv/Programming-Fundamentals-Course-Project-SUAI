#ifndef AEROFLOT_H
#define AEROFLOT_H

#include <string>

typedef __SIZE_TYPE__ size_t;

class QJsonArray;
class QJsonObject;

template <typename T>
class LinkedList;

enum class ERRORS;

struct AEROFLOT
{
    /* Наименование аэропорта (не более 25 букв) */
    std::string strDestination;
    /* Номер перелета (4 цифры) */
    size_t nFlightNumber;
    /* Тип самолета - Одна заглавная буква и 4 цифры */
    std::string strAircraftType;
};

bool operator==(const AEROFLOT& lhs, const AEROFLOT& rhs);

AEROFLOT EnterFlight();

void EditFlight(AEROFLOT& flight);

void EditDestination(std::string& strDestination);
void EditFlightNumber(size_t& nFlightNumber);
void EditAircraftType(std::string& strAircraftType);

QJsonArray AeroflotListToJson(const LinkedList<AEROFLOT>& arrFlight);

LinkedList<AEROFLOT>* JsonToAeroflotList(const QJsonArray& jArr, ERRORS* pError = nullptr);

LinkedList<AEROFLOT>* FindByAircraft(LinkedList<AEROFLOT>* pList, const std::string& strFindAir, ERRORS* pError = nullptr);

QJsonObject AeroflotToJson(const AEROFLOT& flight);

ERRORS PrintFlightList(const LinkedList<AEROFLOT>& arrFlight);

bool PredicateSortByDestination(const AEROFLOT& flight1, const AEROFLOT& flight2);

bool PredicateSortByFlightNumber(const AEROFLOT& flight1, const AEROFLOT& flight2);

bool PredicateSortByAirType(const AEROFLOT& flight1, const AEROFLOT& flight2);

bool CheckAircraftType(const std::string& strAircraftType);

bool CheckDestination(const std::string& strDestination);

bool CheckNumber(int iFlightNumber);


#endif // AEROFLOT_H
