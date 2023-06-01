//
// Created by Maja Frankowska on 15/05/2023.
//

#ifndef PASSWORDMANAGERPJC_LOGIN_H
#define PASSWORDMANAGERPJC_LOGIN_H

#include <string>

namespace login {
    bool loginIn(std::string filePath);

    /**
     * @brief funkcja służy do zalogowania użytkownika do programu
     * @param userPassword, kay
     * @return wartość true jeśli hasło jest poprawne, false jeśli niepoprawne
     */

    void saveTime(time_t time, std::string filePath);

    /**
     * @brief Zapisuje czas ostatniego logowania
     * @param time
     */
}

#endif //PASSWORDMANAGERPJC_LOGIN_H
