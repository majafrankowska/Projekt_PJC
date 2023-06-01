//
// Created by Maja Frankowska on 15/05/2023.
//

#ifndef PASSWORDMANAGERPJC_OPERATIONS_H
#define PASSWORDMANAGERPJC_OPERATIONS_H

#include <iostream>
#include <fstream>

namespace operations {
    void help();

    /**
    * @brief Pomoc dla użytkownika
    */

    std::string openFile();

    /**
     * @brief Funkcja otwiera plik lub tworzy nowy
     * @return filePath
     */

    void deleteFile(std::string filePath);

    /**
     * @brief Funkcja usuwa plik
     * @param filePath Scieżka do pliku
     */

    void quit();

    /**
     * @brief Zamyka program
     */

    void addPassword(std::string filePath);

    /**
    * @brief Funkcja dodaje nowe hasło do pliku na podstawie danych wprowadzonych przez użytkownika lub losowego hasła wygenerowanego przez program
    * @param filePath Scieżka do pliku
    */

    void show(std::string filePath);

    /**
     * @brief Funkcja pokazuje wszystkie hasła w pliku
     * @param filePath Scieżka do pliku
     */


    void editPassword(std::string filePath);

    /**
     * @brief Funkcja edytuje hasło wprowadzone przez użytkownika
     * @param filePath Scieżka do pliku
     */

    void removePassword(std::string filePath);

    /**
    * @brief Funkcja usuwa hasło z pliku
    * @param filePath Scieżka do pliku
    */

    void sortPasswords(const std::string& filePath);

    /**
     * @brief Funkcja wyszukuje hasło na podstawie danych wprowadzonych przez użytkownika
     * @param filePath Scieżka do pliku
     */

    void searchPassword(const std::string& filePath);

    /**
     * @brief Funkcja sortuje hasła według kategorii, loginu, emaila lub strony internetowej
     * @param filePath Scieżka do pliku
     * @return Hasła posortowane według kategorii, loginu, emaila lub strony internetowej
     */

    void addCategory();

    /**
     * @brief Funkcja dodaje kategorię do pliku
     * @param filePath Scieżka do pliku
     *
     */

    void removeCategory(std::string filePath);

    /**
     * @brief Funkcja usuwa kategorię z pliku
     * @param filePath Scieżka do pliku
     *
     */

    std::string generatePassword(int passwordLength, char specialSymbols, char lowercaseLetters, char uppercaseLetters, char numbers);

    /**
     * @brief Generowanie losowego hasła
     * @param passwordLength, specialSymbols, lowercaseLetters, uppercaseLetters, numbers
     * @return password
     */
}

#endif //PASSWORDMANAGERPJC_OPERATIONS_H
