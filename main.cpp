#include <iostream>
#include <fstream>
#include <string>
#include <QJsonArray>
#include "customlinkedlist.h"
#include "aeroflot.h"
#include "environment.h"

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
            std::cout << "Add flight\n\n";

            const AEROFLOT flight = EnterFlight();

            const LinkedList<AEROFLOT>::Node*const pNode = pFlights->Find(flight);

            if(pNode != nullptr)
            {
                std::cout << "Error: flight is already available";
            }
            else
            {
                pFlights->PushFront(flight);
            }
        }
            break;
        case 2:
        {
            std::cout << "Edit flight\n\n";

            std::cout << "Search editable flight:\n";

            AEROFLOT flight = EnterFlight();

            LinkedList<AEROFLOT>::Node*const pNode = pFlights->Find(flight);

            if(pNode != nullptr)
            {
                EditFlight(flight);

                const LinkedList<AEROFLOT>::Node*const pFindEqual = pFlights->Find(flight);

                bool bUniq = true;

                if(pFindEqual != nullptr)
                {
                    if(pFindEqual != pNode)
                    {
                        bUniq = false;
                    }
                }

                if(bUniq)
                {
                    pNode->m_value = flight;

                    std::cout << "Sucess edit";
                }
                else
                {
                    std::cout << "Error: flight have yet. Changes discarded";
                }

            }
            else
            {
                std::cout << "Error: flight not found";
            }
        }
            break;
        case 3:
        {
            std::cout << "Remove flight\n\n";

            const AEROFLOT flight = EnterFlight();

            LinkedList<AEROFLOT>::Node*const pNode = pFlights->Find(flight);

            if(pNode == nullptr)
            {
                std::cout << "Error: flight not found";
            }
            else
            {
                pFlights->Remove(pNode);
            }
        }
            break;
        case 4:
        {
            std::cout << "Find flights operated by air\n\n";

            std::string strAircraft;

            bool bFirst = true;
            std::cout <<  "Enter aircraft type:";
            do
            {
                if(bFirst)
                {
                    bFirst = false;
                }
                else
                {
                    std::cout << "The type of aircraft must consist of one capital letter and 4 digits" << std::endl;
                }

                strAircraft = GetStringValue();
            }
            while(!CheckAircraftType(strAircraft));



            LinkedList<AEROFLOT>* pFinded = FindByAircraft(pFlights, strAircraft);

            const ERRORS err =  PrintFlightList(*pFinded);

            if(err == ERRORS::OBJ_EMPTY)
            {
                std::cout << "Error: Not Found";
            }

            if(pFinded != nullptr)
            {
                delete pFinded;
            }
        }
            break;
        case 5:
        {
            std::cout << "Display the entire list of flights\n\n";

            const ERRORS err = PrintFlightList(*pFlights);

            if(err == ERRORS::OBJ_EMPTY)
            {
                std::cout << "Error: List is empty";
            }
        }
            break;
        case 6:
        {
            std::cout << "Sort flights list\n\n";

            std::cout << "Enter sort by:"
                      << "\n 1. Destination"
                      << "\n 2. Flight number"
                      << "\n 3. Aircraft type"
                      << "\n Another integer - without sort"
                      << std::endl;

            int iSort = GetIntValue();

            switch (iSort)
            {
            case 1:
                pFlights->SortBySelection(PredicateSortByDestination);
                break;
            case 2:
                pFlights->SortBySelection(PredicateSortByFlightNumber);
                break;
            case 3:
                pFlights->SortBySelection(PredicateSortByAirType);
                break;
            }
        }
            break;
        case 7:
        {
            std::cout << "Save database\n\n";

            const QJsonArray jArrFlights = AeroflotListToJson(*pFlights);

            std::cout << "Enter filename with extension: ";

            const std::string strName = GetStringValue();

            const ERRORS errSave = SaveToFile(jArrFlights, strName);

            if(errSave == ERRORS::FILE_OPEN_ERROR)
            {
                std::cout << "Error: Cannot open file";
            }
            else if(errSave == ERRORS::INVALID_ARGUMENT)
            {
                std::cout << "Error: List is empty or filename is invalid";
            }
            else
            {
                std::cout << "Success save";
            }
        }
            break;
        case 8:
        {
            std::cout << "Load database\n\n";

            std::cout << "Enter filename with extension: ";

            const std::string strName = GetStringValue();

            ERRORS errLoad;

            const QJsonArray jArrFlights = LoadFromFile(strName, &errLoad);

            if(errLoad == ERRORS::INVALID_ARGUMENT)
            {
                std::cout << "Error: filename is invalid";
            }
            else if (errLoad == ERRORS::FILE_OPEN_ERROR)
            {
                std::cout << "Error: Cannot open file";
            }
            else
            {
                LinkedList<AEROFLOT>* pNewFlights = JsonToAeroflotList(jArrFlights);

                if(pNewFlights == nullptr)
                {
                    std::cout << "Error: File is invalid";
                }
                else
                {
                    if(pFlights != nullptr)
                    {
                        delete pFlights;
                    }

                    pFlights = pNewFlights;

                    std::cout << "Success load";
                }
            }
        }
            break;
        case 0:
            std::cout << "Exit\nThanks for using my program" << std::endl;
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
