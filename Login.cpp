//
// Created by Maja Frankowska on 15/05/2023.
//

#include "Login.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "Szyfrowanie.h"

namespace login {
    auto loginIn(std::string filePath) -> bool {
        std::fstream file = std::fstream(filePath);
        std::string pass;
        if (!file.is_open()) {
            std::cout << "Nie można otworzyć pliku" << std::endl;
            return false;
        }

        std::getline(file, pass);
        file.open(filePath);

        file.clear();
        file.seekg(0, std::ios::beg);

        std::getline(file, pass);

        std::string userPassword;
        std::string key;

        std::cout << "Hasło: " << std::endl;
        std::cin >> userPassword;

        std::cout << "Klucz: " << std::endl;
        std::cin >> key;

        std::string globalPass;

        globalPass = cipher::decrypt(pass, key);


        if (userPassword == globalPass) {
            std::cout << "Prawidłowe hasło \n" << std::endl;
            file.close();
            return true;
        } else {
            std::cout << "Nieprawidłowe hasło, spróbuj jeszcze raz (masz 3 podejścia wpisania prawidłowego hasła) \n" << std::endl;
            return false;
        }
    }

    auto saveTime(time_t time, std::string filePath) -> void {

        std::fstream loginsOut;
        loginsOut.open("..\\files\\logList.txt", std::ios::out | std::ios::app);

        char *dt = std::ctime(&time);
        loginsOut << filePath << " <--- Last login time -- " << dt << std::endl;
        loginsOut.close();
    }
}

