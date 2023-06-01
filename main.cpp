//
// Created by Maja Frankowska on 15/05/2023.
//

#include "Szyfrowanie.h"
#include "Login.h"
#include "Operations.h"
#include "Login.h"
#include <iostream>
#include <vector>
#include <ctime>

auto main() -> int{
    bool isLogIn = false;
    bool quit = false;
    int choiceOption;
    std::string filePath;
    int logAttempts = 0;


    while(!isLogIn){

        std::cout << " __  __                              _                         _                            _ \n";
        std::cout << "|  \\/  |   ___   _ __     __ _    __| |  ____   ___   _ __    | |__     __ _   ___    ___  | |\n";
        std::cout << "| |\\/| |  / _ \\ | '_ \\   / _` |  / _` | |_  /  / _ \\ | '__|   | '_ \\   / _` | / __|  / _ \\ | |\n";
        std::cout << "| |  | | |  __/ | | | | | (_| | | (_| |  / /  |  __/ | |      | | | | | (_| | \\__ \\ |  __/ | |\n";
        std::cout << "|_|  |_|  \\___| |_| |_|  \\__,_|  \\__,_| /___|  \\___| |_|      |_| |_|  \\__,_| |___/  \\___| |_|\n";
        std::cout << std::endl;

        filePath = operations::openFile();

        std::cout << "Aby się zalogować musisz podać hasło poniżej." << std::endl;
        isLogIn = login::loginIn(filePath);
        logAttempts++;
        if(logAttempts > 3){
            std::cout << "Przekroczyłeś możliwą liczbę prób." << std::endl;
            exit(0);
        }
    }

    if(isLogIn) {
        time_t timeNow = time(0);
        login::saveTime(timeNow, filePath);

        while(!quit)
        {
            std::cout << "Dostępne operacje: " << std::endl;;
            std::cout << "1: szukaj hasło       7: usuń kategorię" << std::endl;
            std::cout << "2: posortuj hasła     8: pokaż plik" << std::endl;
            std::cout << "3: dodaj hasło        9: usuń plik" << std::endl;
            std::cout << "4: edytuj hasło      10: help menu" << std::endl;
            std::cout << "5: usuń hasło        11: zamknij program" << std::endl;
            std::cout << "6: dodaj kategorię \n" << std::endl;
            std::cout << "Podaj wybraną opcję: \n";

            std::cin >> choiceOption;

            switch(choiceOption)
            {
                case 1:
                    std::cout << "Wybrałeś 'szukaj hasło'" << std::endl;
                    operations::searchPassword(filePath);
                    break;
                case 2:
                    std::cout << "Wybrałeś 'posortuj hasło'" << std::endl;
                    operations::sortPasswords(filePath);
                    break;
                case 3:
                    std::cout << "Wybrałeś 'dodaj hasło'" << std::endl;
                    operations::addPassword(filePath);
                    break;
                case 4:
                    std::cout << "Wybrałeś 'edytuj hasło'" << std::endl;
                    operations::editPassword(filePath);
                    break;
                case 5:
                    std::cout << "Wybrałeś 'usuń hasło'" << std::endl;
                    operations::removePassword(filePath);
                    break;
                case 6:
                    std::cout << "Wybrałeś 'dodaj kategorię'" << std::endl;
                    operations::addCategory();
                    break;
                case 7:
                    std::cout << "Wybrałeś 'usuń kategorię'" << std::endl;
                    operations::removeCategory(filePath);
                    break;
                case 8:
                    std::cout << "Wybrałeś 'pokaż plik'" << std::endl;
                    operations::show(filePath);
                    break;
                case 9:
                    std::cout << "Wybrałeś 'usuń plik'" << std::endl;
                    operations::deleteFile(filePath);
                    break;
                case 10:
                    std::cout << "Wybrałeś 'help menu'" << std::endl;
                    operations::help();
                    break;
                case 11:
                    std::cout << "Wybrałeś 'zamknij program'" << std::endl;
                    quit = true;
                    operations::quit();
                    break;
                default:
                    std::cout<<"Operacja nie rozpoznana, spróbuj jeszcze raz." << std::endl;
                    break;
            }
        }
    }
}

