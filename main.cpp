#include <iostream>
#include <fstream>
#include <string>

#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

#include "customlinkedlist.h"
#include "aeroflot.h"
#include "environment.h"

/*
 Предметная область – «Расписание рейсов самолетов».
 Данные о рейсе хранятся в структуре с именем AEROFLOT, содержащей следующие поля:
    * название пункта назначения рейса;
    * номер рейса;
    * тип самолѐта.
 Задание на поиск: найти рейсы, обслуживаемые самолѐтом, тип которого введѐн с клавиатуры.
 */

int main()
{
    size_t nCommand = 1;

    LinkedList<AEROFLOT>* pFlights = new LinkedList<AEROFLOT>();

    while(nCommand != 0)
    {
        ClearConsole();

        ShowMenu();

        nCommand = GetIntValue();

        ClearConsole();

        switch(nCommand)
        {
        case 1:
        {
            AEROFLOT flight = EnterFlight();

            pFlights->Find(flight);

            pFlights->PushFront(flight);
        }
            break;
        case 2:
            //
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
        {
            ERRORS err = PrintFlightList(*pFlights);

            if(err == ERRORS::OBJ_EMPTY)
            {
                std::cout << "List is empty";
            }
        }
            break;
        case 7:
            break;
        case 8:

            break;
        case 0:
            std::cout << "Exit";
            break;
        default:
            std::cout << "Error: command unknown";
            break;
        }

        PressToContinue();
    }

    if(pFlights != nullptr)
    {
        delete pFlights;
    }

    return 0;
}
