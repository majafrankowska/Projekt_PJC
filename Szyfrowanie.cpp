//
// Created by Maja Frankowska on 15/05/2023.
//

#include "Szyfrowanie.h"
#include <iostream>
#include <ranges>

namespace cipher {
    std::string encrypt(const std::string& message, const std::string& key) {
        std::string encryptedMessage;
        encryptedMessage.reserve(message.size());

        for (size_t i = 0; i < message.length(); i++) {
            char ch = message[i];
            char keyChar = key[i % key.length()];

            int sum = ch + keyChar;
            int modulo = sum % 128;

            encryptedMessage += static_cast<char>(modulo);
        }

        return encryptedMessage;
    }

    std::string decrypt(const std::string& message, const std::string& key) {
        std::string decryptedMessage;
        decryptedMessage.reserve(message.size());

        for (size_t i = 0; i < message.length(); i++) {
            char ch = message[i];
            char keyChar = key[i % key.length()];

            int sum = ch - keyChar;
            int modulo = sum % 128;

            decryptedMessage += static_cast<char>(modulo);
        }

        return decryptedMessage;
    }
}
