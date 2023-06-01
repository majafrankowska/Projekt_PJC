//
// Created by Maja Frankowska on 15/05/2023.
//

#ifndef PASSWORDMANAGERPJC_SZYFROWANIE_H
#define PASSWORDMANAGERPJC_SZYFROWANIE_H

#include <iostream>
#include <string>

namespace cipher {
    std::string encrypt(const std::string& message, const std::string& key);

    std::string decrypt(const std::string& message, const std::string& key);
}


#endif //PASSWORDMANAGERPJC_SZYFROWANIE_H
