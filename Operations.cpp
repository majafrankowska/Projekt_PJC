//
// Created by Maja Frankowska on 15/05/2023.
//

#include "Operations.h"
#include "Szyfrowanie.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <regex>
#include <filesystem>
#include "Szyfrowanie.h"

namespace operations {

    std::vector<std::string> categories = {"sociale", "praca", "prywatne"};

    auto help() -> void {

        std::cout << " __  __                              _                         _                            _ \n";
        std::cout
                << "|  \\/  |   ___   _ __     __ _    __| |  ____   ___   _ __    | |__     __ _   ___    ___  | |\n";
        std::cout
                << "| |\\/| |  / _ \\ | '_ \\   / _` |  / _` | |_  /  / _ \\ | '__|   | '_ \\   / _` | / __|  / _ \\ | |\n";
        std::cout
                << "| |  | | |  __/ | | | | | (_| | | (_| |  / /  |  __/ | |      | | | | | (_| | \\__ \\ |  __/ | |\n";
        std::cout
                << "|_|  |_|  \\___| |_| |_|  \\__,_|  \\__,_| /___|  \\___| |_|      |_| |_|  \\__,_| |___/  \\___| |_|\n";
        std::cout << std::endl;

        std::cout << "Witaj użytkowniku, znajdujesz się w menadżerze haseł stworzonego przez s24331,\n"
                     "program został stworzony żeby pomóc ci zarządzać i przechowywać swoje hasła.\n" << std::endl;
        std::cout << "Potrzebujesz mieć plik ze swoimi hasłami aby móc korzystać z tego programu.\n"
                     "Możesz utowrzyć nowy plik lub otworzyć istniejący.\n" << std::endl;
        std::cout << "Aby utowrzyć nowy plik, musisz wprowadzić nazwę pliku.\n"
                     "Poleca się używać formatu: \"filename.txt\"\n" << std::endl;
        std::cout << "Aby otworzyć istniejący plik, musisz wybrać plik.\n";
        std::cout << "Aby dodać nowe hasło, musisz wybrać opcję 'dodaj hasło'.\n";
        std::cout << "Aby wyświetlić wszystkie hasła, musisz wybrać opcję 'pokaż hasła'.\n";
        std::cout << "Aby edytować hasło, musisz wybrać opcję 'edytuj hasło'.\n";
        std::cout << "Aby usunąć hasło, musisz wybrać opcję 'usuń hasło'.\n";
        std::cout << "Aby dodać kategorię, musisz wybrać opcję 'dodaj kategorię'.\n";
        std::cout << "Aby usunąć kategorię, musisz wybrać opcję 'usuń kategorię'.\n";
        std::cout << "Aby posortować hasła, musisz wybrać opcję 'posortuj hasła'.\n";
        std::cout << "Aby wyszukać hasła, musisz wybrać opcję 'szukaj hasła'.\n";
        std::cout << "Aby wyświetlić plik, musisz wybrać opcję 'pokaż plik'.\n";
        std::cout << "Aby usunąć plik, musisz wybrać opcję 'usuń plik'.\n";
        std::cout << "Aby zakończyć program, musisz wybrać opcję 'zakończ program'.\n";
        std::cout << "Aby zobaczyć ponownie to menu, musisz wybrać opcję 'pomoc'.\n";
        std::cout << "Aby wyjść z programu, musisz wybrać opcję 'wyjście z programu'.\n" << std::endl;
    }
    auto createFile(const std::string &filePath) -> void {
        std::ofstream file(filePath);
        if (file) {
            std::cout << "Utworzono nowy plik: " << filePath << std::endl;
        } else {
            std::cout << "Nie udało się utworzyć pliku: " << filePath << std::endl;
        }
        file.close();
    }

    auto openFile() -> std::string {

        std::string filePath;
        std::string fileName;
        std::string password;
        std::string key;
        std::ofstream file;

        std::cout << "Witaj użytkowniku! Wybierz opcję:\n" <<
                  " - Jeśli chcesz wybrać ścieżkę pliku z programu: 1 \n"
                  " - Jeśli chcesz napisać ścieżkę absolutną do swojego pliku: 2 \n"
                  " - Jeśli chcesz utwórzyć nowy plik: 3 \n" << std::endl;

        int choice;
        std::cout << "Podaj numer wybranej przez ciebie opcji:";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                std::cout << "1 - \"..\\\\files\\\\login.txt\"" << std::endl;
                std::cout << "2 - \"..\\\\files\\\\login2.txt\"\n" << std::endl;
                int choiceFileNumber;
                std::cout << "Wprowadż numer pliku:";
                std::cin >> choiceFileNumber;
                std::cout << std::endl;
                switch (choiceFileNumber) {
                    case 1:
                        filePath = "..\\files\\login.txt";
                        break;
                    case 2:
                        filePath = "..\\files\\login2.txt";
                        break;
                    default:
                        std::cout << "Wprowadziłeś zły numer pliku" << std::endl;
                        openFile();
                        break;
                }
                break;
            case 2:
                std::cout << "Wprowadź scieżkę absolutną swojego pliku: ";
                std::cin >> filePath;
                while (filePath.length() == 0) {
                    std::cout << "Twoja scieżka do pliku nie zawiera żadnego pliku. Spróbuj jeszcza raz: ";
                    std::cout << "Wprowadź scieżkę absolutną swojego pliku: ";
                    std::cin >> filePath;
                }
                while (filePath.find("\\") == std::string::npos) {
                    std::cout << "Scieżka twojego pliku jest niepoprawna " << std::endl;
                    std::cout << "Wprowadź scieżkę absolutną swojego pliku: ";
                    std::cin >> filePath;
                }
                while (filePath.find(".txt") == std::string::npos) {
                    std::cout << "Scieżka twojego pliku musi się konczyć z .txt" << std::endl;
                    std::cout << "Wprowadź scieżkę absolutną swojego pliku: ";
                    std::cin >> filePath;
                }
                while (filePath.find("G:\\") == std::string::npos && filePath.find("C:\\") == std::string::npos &&
                       filePath.find("D:\\") == std::string::npos && filePath.find("E:\\") == std::string::npos &&
                       filePath.find("F:\\") == std::string::npos && filePath.find("H:\\") == std::string::npos &&
                       filePath.find("I:\\") == std::string::npos && filePath.find("J:\\") == std::string::npos &&
                       filePath.find("K:\\") == std::string::npos && filePath.find("L:\\") == std::string::npos &&
                       filePath.find("M:\\") == std::string::npos && filePath.find("N:\\") == std::string::npos &&
                       filePath.find("O:\\") == std::string::npos && filePath.find("P:\\") == std::string::npos &&
                       filePath.find("Q:\\") == std::string::npos && filePath.find("R:\\") == std::string::npos &&
                       filePath.find("S:\\") == std::string::npos && filePath.find("T:\\") == std::string::npos &&
                       filePath.find("U:\\") == std::string::npos && filePath.find("V:\\") == std::string::npos &&
                       filePath.find("W:\\") == std::string::npos && filePath.find("X:\\") == std::string::npos &&
                       filePath.find("Y:\\") == std::string::npos && filePath.find("Z:\\") == std::string::npos) {
                    std::cout << "Twoja scieżka jest nieprawdiłowa" << std::endl;
                    std::cout << "Wprowadź scieżkę absolutną swojego pliku: ";
                    std::cin >> filePath;
                }
                std::cout << "Scieżka twojego pliku to: " << filePath << std::endl;
                break;
            case 3:
                std::cout << "Podaj nazwę pliku:";
                std::cin >> fileName;
                std::cout << "Podaj nowe hasło dla pliku" << std::endl;
                std::cin >> password;
                std::cout << "Podaj klucz do hasła: ";
                std::cin >> key;

                filePath = "/Users/majafrankowska/Desktop/PasswordManagerPJC/files/" + fileName + ".txt";


                file.open("/Users/majafrankowska/Desktop/PasswordManagerPJC/files/" + fileName + ".txt");
                file << cipher::encrypt(password, key) << std::endl;
                file << "  Password     Category     Login        E-mail           Site           Notes     "
                     << std::endl;
                file.close();

                std::cout << "Plik został utworzony" << std::endl;
                break;
            default:
                std::cout << "Nieprawidłowa scieżka do pliku" << std::endl;
                openFile();
                break;
        }
        return filePath;
    }

    auto deleteFile(std::string filePath) -> void {
        std::string fileName;

        std::cout << "Jeśli chcesz usunąć plik  z programu wybierz: 1" << std::endl;
        std::cout << "Jeśli chcesz wrócić do menu głównego wybierz: 2" << std::endl;

        int choice;
        std::cout << "Podaj numer:";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Pamiętaj o tym, że usunięcie pliku który jest otwarty jest niemożliwe." << std::endl;
                std::cout << "Podaj nazwę pliku do usunięcia: ";
                std::cin >> fileName;
                fileName = "..\\files\\" + fileName + ".txt";

                if (fileName == filePath) {
                    std::cout << "Nie możesz usunąć otwartego pliku" << std::endl;
                    deleteFile(filePath);
                }

                std::cout << "Jesteś pewien, że chcesz usunąć plik? (y/n)";
                char choiceFile;
                std::cin >> choiceFile;
                if (choice == 'y') {
                    std::remove(fileName.c_str());
                    std::cout << "Plik został usunięty" << std::endl;
                } else if (choice == 'n') {
                    std::cout << "Plik nie został usunięty" << std::endl;
                } else {
                    std::cout << "Nieprawidłowy wybór" << std::endl;
                    deleteFile(filePath);
                }
            case 2:
                break;
        }
    }

    auto quit() -> void {
        std::cout << "Dziękuję za skorzystanie z programu, do zobaczenia! " << std::endl;
        exit(0);
    }

    auto addPassword(std::string filePath) -> void {

        std::string password;
        std::string category;
        std::string login;
        std::string email;
        std::string website;
        std::string note;
        int passwordLength;
        std::ofstream file;
        char specialSymbols;
        char lowercaseLetters;
        char uppercaseLetters;
        char numbers;

        std::cout << "Wybierz opcję:\n" << std::endl <<
                  "Jeśli chcesz sam wybrać hasło wybierz: 1\n"
                  "Jeśli chcesz wybrać hasło wygenerowane losowo wybierz: 2\n"
                  "Jeśli chcesz wrócić do menu wybierz: 3\n" << std::endl;
        int choice;
        std::cout << "Wprowadź numer:";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Podaj nowe hasło: ";
                std::cin >> password;
                while (password.length() < 8 || password.length() > 16) {
                    std::cout << "Twoje hasło jest za krótkie lub za długie. Spróbuj jeszcze raz: ";
                    std::cin >> password;
                }
                while (password.find('0') == std::string::npos && password.find('1') == std::string::npos &&
                       password.find('2') == std::string::npos && password.find('3') == std::string::npos &&
                       password.find('4') == std::string::npos && password.find('5') == std::string::npos &&
                       password.find('6') == std::string::npos && password.find('7') == std::string::npos &&
                       password.find('8') == std::string::npos && password.find('9') == std::string::npos) {
                    std::cout << "Twoje hasło musi zawierać conajmniej jedną liczbę. Podaj nowe hasło jeszcze raz: ";
                    std::cin >> password;
                }
                while (password.find('a') == std::string::npos && password.find('b') == std::string::npos &&
                       password.find('c') == std::string::npos && password.find('d') == std::string::npos &&
                       password.find('e') == std::string::npos && password.find('f') == std::string::npos &&
                       password.find('g') == std::string::npos && password.find('h') == std::string::npos &&
                       password.find('i') == std::string::npos && password.find('j') == std::string::npos &&
                       password.find('k') == std::string::npos && password.find('l') == std::string::npos &&
                       password.find('m') == std::string::npos && password.find('n') == std::string::npos &&
                       password.find('o') == std::string::npos && password.find('p') == std::string::npos &&
                       password.find('q') == std::string::npos && password.find('r') == std::string::npos &&
                       password.find('s') == std::string::npos && password.find('t') == std::string::npos &&
                       password.find('u') == std::string::npos && password.find('v') == std::string::npos &&
                       password.find('w') == std::string::npos && password.find('x') == std::string::npos &&
                       password.find('y') == std::string::npos && password.find('z') == std::string::npos) {
                    std::cout
                            << "Twoje hasło musi zawierać conajmniej jedną małą literę. Podaj nowe hasło jeszcze raz: ";
                    std::cin >> password;
                }
                while (password.find('A') == std::string::npos && password.find('B') == std::string::npos &&
                       password.find('C') == std::string::npos && password.find('D') == std::string::npos &&
                       password.find('E') == std::string::npos && password.find('F') == std::string::npos &&
                       password.find('G') == std::string::npos && password.find('H') == std::string::npos &&
                       password.find('I') == std::string::npos && password.find('J') == std::string::npos &&
                       password.find('K') == std::string::npos && password.find('L') == std::string::npos &&
                       password.find('M') == std::string::npos && password.find('N') == std::string::npos &&
                       password.find('O') == std::string::npos && password.find('P') == std::string::npos &&
                       password.find('Q') == std::string::npos && password.find('R') == std::string::npos &&
                       password.find('S') == std::string::npos && password.find('T') == std::string::npos &&
                       password.find('U') == std::string::npos && password.find('V') == std::string::npos &&
                       password.find('W') == std::string::npos && password.find('X') == std::string::npos &&
                       password.find('Y') == std::string::npos && password.find('Z') == std::string::npos) {
                    std::cout
                            << "Twoje hasło musi zawierać conajmniej jedną dużą literę. Podaj nowe hasło jeszcze raz: ";
                    std::cin >> password;
                }
                while (password.find('!') == std::string::npos && password.find('@') == std::string::npos &&
                       password.find('#') == std::string::npos && password.find('$') == std::string::npos &&
                       password.find('%') == std::string::npos && password.find('^') == std::string::npos &&
                       password.find('&') == std::string::npos && password.find('*') == std::string::npos &&
                       password.find('(') == std::string::npos && password.find(')') == std::string::npos &&
                       password.find('-') == std::string::npos && password.find('_') == std::string::npos &&
                       password.find('=') == std::string::npos && password.find('+') == std::string::npos &&
                       password.find('[') == std::string::npos && password.find(']') == std::string::npos &&
                       password.find('{') == std::string::npos && password.find('}') == std::string::npos &&
                       password.find(';') == std::string::npos && password.find('\'') == std::string::npos &&
                       password.find('\"') == std::string::npos && password.find('|') == std::string::npos &&
                       password.find('\\') == std::string::npos && password.find('/') == std::string::npos &&
                       password.find(',') == std::string::npos && password.find('.') == std::string::npos &&
                       password.find('<') == std::string::npos && password.find('>') == std::string::npos &&
                       password.find('?') == std::string::npos && password.find('~') == std::string::npos &&
                       password.find('`') == std::string::npos) {
                    std::cout
                            << "Twoje hasło musi zawierać conajmniej jeden specjalny znak. Podaj nowe hasło jeszcze raz: ";
                    std::cin >> password;
                }
                std::cout << "Podane hasło jest prawidłowe,\n" << std::endl;

                std::cout << "1. Utwórz nową kategorię \n" <<
                          "2. Wybierz kategorię z listy \n";
                int choiceCategory;
                std::cout << "Podaj swój wybór: ";
                std::cin >> choiceCategory;
                if (choiceCategory == 1) {
                    std::cout << "Podaj nową kategorię: ";
                    std::cin >> category;
                    categories.push_back(category);
                } else if (choiceCategory == 2) {
                    std::cout << "Wybierz kategorię z listy: ";
                    for (int i = 0; i < categories.size(); i++) {
                        std::cout << i + 1 << ". " << categories[i] << std::endl;
                    }
                    int choiceCategory2;
                    std::cin >> choiceCategory2;
                    category = categories[choiceCategory2 - 1];
                } else {
                    std::cout << "Błędnie podana kategoria. Sróbuj jeszcze raz: ";
                    addPassword(filePath);
                }
                std::cout << "Podaj nowy login: ";
                std::cin >> login;
                std::cout << "Podaj nowe hasło: ";
                std::cin >> email;
                while (email.find('@') == std::string::npos) {
                    std::cout << "Podałeś nieprawidłowy email, dodaj '@'" << std::endl;
                    std::cout << "Podaj nowy Email: ";
                    std::cin >> email;
                }
                std::cout << "Podaj nową stronę internetową: ";
                std::cin >> website;
                std::cout << "Napisz nową notatkę: ";
                std::cin >> note;
                file.open(filePath, std::ios::app);
                file << '-' << password << '-' << " | " << '=' << category << '=' << " | " << ':' << login << ':'
                     << " | " << '-' << email << ':' << " | " << '=' << website << ':'
                     << " | " << note;
                file.close();
            case 2:
                std::cout << "Podaj długość hasła (8-24): ";
                std::cin >> passwordLength;
                std::cout << "Chcesz użyć specjalnych znaków? (y/n): ";
                std::cin >> specialSymbols;
                std::cout << "Chcesz użyć małych liter? (y/n): ";
                std::cin >> lowercaseLetters;
                std::cout << "Chcesz użyć dużych liter? (y/n): ";
                std::cin >> uppercaseLetters;
                std::cout << "Chcesz użyć liczb? (y/n): ";
                std::cin >> numbers;

                if (passwordLength < 8 || passwordLength > 24) {
                    std::cout << "To nie jest prawidłowa długość hasła" << std::endl;
                    addPassword(filePath);
                } else {
                    password = operations::generatePassword(passwordLength, specialSymbols, lowercaseLetters,
                                                            uppercaseLetters, numbers);
                }

                std::cout << "Twoje hasło to: " << password << std::endl;
                std::cout << "Chcesz je zapisać? (y/n)" << std::endl;
                char saveChoice;
                std::cin >> saveChoice;
                if (saveChoice == 'y') {
                    std::cout << "1. Podaj nową kategorię \n" <<
                              "2. Wybierz z listy \n";
                    int choiceCategory;
                    std::cout << "Podaj swój wybór: ";
                    std::cin >> choiceCategory;
                    if (choiceCategory == 1) {
                        std::cout << "Podaj nową kategorię: \n";
                        std::cin >> category;
                        categories.push_back(category);
                    } else if (choiceCategory == 2) {
                        std::cout << "Wybierz z listy: \n";
                        for (int i = 0; i < categories.size(); i++) {
                            std::cout << i + 1 << ". " << categories[i] << std::endl;
                        }
                        std::cout << std::endl;
                        int choiceCategory2;
                        std::cout << "Podaj swój wybór: ";
                        std::cin >> choiceCategory2;
                        category = categories[choiceCategory2 - 1];
                    } else {
                        std::cout << "Nieprawdiłowy input. Podaj nową kategorię: ";
                        addPassword(filePath);
                    }
                    std::cout << "Podaj login: ";
                    std::cin >> login;
                    std::cout << "Podaj email: ";
                    std::cin >> email;
                    while (email.find('@') == std::string::npos) {
                        std::cout << "Ten email jest nieprawidłowy, musisz dodać '@'" << std::endl;
                        std::cout << "Podaj nowy email: ";
                        std::cin >> email;
                    }
                    std::cout << "Podaj stronę www: ";
                    std::cin >> website;
                    std::cout << "Wpisz notatkę: ";
                    std::cin >> note;
                    std::cout << "Zapisuję..." << std::endl;
                    std::ofstream file;
                    file.open(filePath, std::ios::app);
                    file << '-' << password << '-' << " | " << '=' << category << '=' << " | " << ':' << login
                         << ':' << " | " << '-' << email << ':' << " | " << '=' << website << ':'
                         << " | " << note;
                    file.close();
                    std::cout << "Zapisano pomyślnie." << std::endl;
                } else if (saveChoice == 'n') {
                    std::cout << "WYbrałeś nie zapisanie hasła, spróbuj jeszcze raz.\n" << std::endl;
                    addPassword(filePath);
                } else {
                    std::cout << " Nieprawidłowy wybór\n" << std::endl;
                    addPassword(filePath);
                }
            case 3:
                std::cout << "Wracam do menu...\n" << std::endl;
                break;
            default:
                std::cout << "Nieprawidłowy wybór\n" << std::endl;
                addPassword(filePath);
        }
    }

    auto show(std::string filePath) -> void {
        std::ifstream file;
        file.open(filePath);
        int numberLine = 0;
        while (!file.eof()) {
            std::string line;
            std::getline(file, line);
            std::cout << numberLine << ". " << line << std::endl;
            numberLine++;
        }
        std::cout << std::endl;
    }

    auto editPassword(std::string filePath) -> void {
        std::ifstream file;
        file.open(filePath);
        int numberLine = 0;
        std::string lineSearch;

        std::ofstream temp("..\\files\\temp.txt");

        std::string passwordToEdit;
        std::string newPassword;

        std::cout << "Jeśli chcesz edytować hasło wybierz - 1.\n" <<
                  "Jeśli chcesz wrócić do menu wybierz - 2.\n";

        int choice;
        std::cout << "Podaj swój wybór: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                while (!file.eof()) {
                    std::string line;
                    std::getline(file, line);
                    std::cout << numberLine << ". " << line << std::endl;
                    numberLine++;
                }
                std::cout << std::endl;

                std::cout << "Podaj hasło do edycji: ";
                std::cin >> passwordToEdit;
                std::cout << "Podaj nowe hasło: ";
                std::cin >> newPassword;
                while (newPassword.length() < 8 || newPassword.length() > 16) {
                    std::cout << "Twoje hasło jest za krótkie lub za długie. Spróbuj jeszcze raz: ";
                    std::cin >> newPassword;
                }
                while (newPassword.find('0') == std::string::npos && newPassword.find('1') == std::string::npos &&
                       newPassword.find('2') == std::string::npos && newPassword.find('3') == std::string::npos &&
                       newPassword.find('4') == std::string::npos && newPassword.find('5') == std::string::npos &&
                       newPassword.find('6') == std::string::npos && newPassword.find('7') == std::string::npos &&
                       newPassword.find('8') == std::string::npos && newPassword.find('9') == std::string::npos) {
                    std::cout << "Twoje hasło musi zawierać conajmniej jedną liczbę. Spróbuj jeszcze raz: ";
                    std::cin >> newPassword;
                }
                while (newPassword.find('a') == std::string::npos && newPassword.find('b') == std::string::npos &&
                       newPassword.find('c') == std::string::npos && newPassword.find('d') == std::string::npos &&
                       newPassword.find('e') == std::string::npos && newPassword.find('f') == std::string::npos &&
                       newPassword.find('g') == std::string::npos && newPassword.find('h') == std::string::npos &&
                       newPassword.find('i') == std::string::npos && newPassword.find('j') == std::string::npos &&
                       newPassword.find('k') == std::string::npos && newPassword.find('l') == std::string::npos &&
                       newPassword.find('m') == std::string::npos && newPassword.find('n') == std::string::npos &&
                       newPassword.find('o') == std::string::npos && newPassword.find('p') == std::string::npos &&
                       newPassword.find('q') == std::string::npos && newPassword.find('r') == std::string::npos &&
                       newPassword.find('s') == std::string::npos && newPassword.find('t') == std::string::npos &&
                       newPassword.find('u') == std::string::npos && newPassword.find('v') == std::string::npos &&
                       newPassword.find('w') == std::string::npos && newPassword.find('x') == std::string::npos &&
                       newPassword.find('y') == std::string::npos && newPassword.find('z') == std::string::npos) {
                    std::cout << "Twoje hasło musi zawierać conajmniej jedną małą literę. Spróbuj jeszcze raz: ";
                    std::cin >> newPassword;
                }
                while (newPassword.find('A') == std::string::npos && newPassword.find('B') == std::string::npos &&
                       newPassword.find('C') == std::string::npos && newPassword.find('D') == std::string::npos &&
                       newPassword.find('E') == std::string::npos && newPassword.find('F') == std::string::npos &&
                       newPassword.find('G') == std::string::npos && newPassword.find('H') == std::string::npos &&
                       newPassword.find('I') == std::string::npos && newPassword.find('J') == std::string::npos &&
                       newPassword.find('K') == std::string::npos && newPassword.find('L') == std::string::npos &&
                       newPassword.find('M') == std::string::npos && newPassword.find('N') == std::string::npos &&
                       newPassword.find('O') == std::string::npos && newPassword.find('P') == std::string::npos &&
                       newPassword.find('Q') == std::string::npos && newPassword.find('R') == std::string::npos &&
                       newPassword.find('S') == std::string::npos && newPassword.find('T') == std::string::npos &&
                       newPassword.find('U') == std::string::npos && newPassword.find('V') == std::string::npos &&
                       newPassword.find('W') == std::string::npos && newPassword.find('X') == std::string::npos &&
                       newPassword.find('Y') == std::string::npos && newPassword.find('Z') == std::string::npos) {
                    std::cout << "Twoje hasło musi zawierać conajmniej jedną dużą literę. Spróbuj jeszcze raz:";
                    std::cin >> newPassword;
                }
                while (newPassword.find('!') == std::string::npos && newPassword.find('@') == std::string::npos &&
                       newPassword.find('#') == std::string::npos && newPassword.find('$') == std::string::npos &&
                       newPassword.find('%') == std::string::npos && newPassword.find('^') == std::string::npos &&
                       newPassword.find('&') == std::string::npos && newPassword.find('*') == std::string::npos &&
                       newPassword.find('(') == std::string::npos && newPassword.find(')') == std::string::npos &&
                       newPassword.find('-') == std::string::npos && newPassword.find('_') == std::string::npos &&
                       newPassword.find('=') == std::string::npos && newPassword.find('+') == std::string::npos &&
                       newPassword.find('[') == std::string::npos && newPassword.find(']') == std::string::npos &&
                       newPassword.find('{') == std::string::npos && newPassword.find('}') == std::string::npos &&
                       newPassword.find(';') == std::string::npos && newPassword.find('\'') == std::string::npos &&
                       newPassword.find('\"') == std::string::npos && newPassword.find('|') == std::string::npos &&
                       newPassword.find('\\') == std::string::npos && newPassword.find('/') == std::string::npos &&
                       newPassword.find(',') == std::string::npos && newPassword.find('.') == std::string::npos &&
                       newPassword.find('<') == std::string::npos && newPassword.find('>') == std::string::npos &&
                       newPassword.find('?') == std::string::npos && newPassword.find('~') == std::string::npos &&
                       newPassword.find('`') == std::string::npos) {
                    std::cout << "Hasło musi mieć conajmniej jeden specjalny znak. Podaj nowe hasło jeszcze raz: ";
                    std::cin >> newPassword;
                }
                std::cout << "Hasło jest prawidłowe\n" << std::endl;

                while (file >> lineSearch) {
                    if (lineSearch == passwordToEdit) {
                        lineSearch = newPassword;
                    }
                    lineSearch += " ";
                    temp << lineSearch;
                }
                file.close();
                temp.close();
                remove(filePath.c_str());
                rename("..\\files\\temp2.txt", filePath.c_str());

                std::cout << "Pomyślnie zmieniono hasło " << std::endl;
            case 2:
                break;
        }
    }

    auto removePassword(std::string filePath) -> void {
        std::fstream file;
        std::string line;
        int numberLine = 0;
        int passwordLine;
        int lineNumberToDelete = 1;

        file.open(filePath);

        std::fstream temp;
        temp.open("..\\files\\temp.txt", std::fstream::out);

        std::cout << "Jeśli chcesz usunąć hasło wybierz - 1." << std::endl;
        std::cout << "Jeśli chcesz wrócić do menu wybierz - 2." << std::endl;

        int choice;
        std::cout << "Podaj swój wybór: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                while (!file.eof()) {
                    std::string line;
                    std::getline(file, line);
                    std::cout << numberLine << ". " << line << std::endl;
                    numberLine++;
                }
                std::cout << std::endl;

                std::cout << "Podaj linię hasła do usunięcia: ";
                std::cin >> passwordLine;

                if (passwordLine < 2 || passwordLine > numberLine) {
                    std::cout << "Nieprawidłowy numer\n" << std::endl;
                    removePassword(filePath);
                } else {
                    std::cout << "Usuwam..." << std::endl;
                    while (std::getline(file, line)) {
                        if (lineNumberToDelete != passwordLine) {
                            temp << line << std::endl;
                        }
                        lineNumberToDelete++;
                    }
                    file.close();
                    temp.close();
                    remove(filePath.c_str());
                    rename("..\\files\\temp.txt", filePath.c_str());
                }
            case 2:
                break;
        }
    }

    auto searchPassword(const std::string &filePath) -> void {
        std::fstream file;
        std::string word;
        int numberLine = 0;
        int counter = 0;

        file.open(filePath.c_str());

        std::cout << "Jeśli chcesz przeszukać - 1." << std::endl;
        std::cout << "Jeśli chcesz wrócić do menu - 2." << std::endl;

        int choice;
        std::cout << "Podaj co wybrałeś: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Podaj słowo, które ma mieć: ";
                std::cin >> word;
                std::cout << std::endl;

                std::cout << "Szukam..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::cout << "Znalezione hasła:" << std::endl;

                while (!file.eof()) {
                    std::string line;
                    std::getline(file, line);
                    if (line.find(word) != std::string::npos) {
                        std::cout << numberLine << ". " << line << std::endl;
                        counter++;
                    }
                    numberLine++;
                }
                if (counter == 0) {
                    std::cout << "Nie znaleziono haseł" << std::endl;
                }

                std::cout << std::endl;
            case 2:
                break;
            default:
                std::cout << "Nieprawidłowy numer" << std::endl;
                searchPassword(filePath);
        }
    }

    auto sortPasswords(const std::string &filePath) -> void {
        std::fstream file;
        file.open(filePath);

        std::vector<std::string> passwords;
        std::string lineP;
        std::regex wordRegex("-[a-zA-Z0-9!#$@%^&*()/]+-");
        while (std::getline(file, lineP)) {
            std::string word;
            std::stringstream ss(lineP);
            while (ss >> word) {
                if (regex_match(word, wordRegex)) {
                    passwords.push_back(word);
                }
            }
        }

        std::vector<std::string> logins;
        std::string lineL;
        std::regex wordRegexL(":[a-zA-Z0-9!#$@%^&*()/]+:");
        while (std::getline(file, lineL)) {
            std::string word;
            std::stringstream ss(lineL);
            while (ss >> word) {
                if (regex_match(word, wordRegexL)) {
                    logins.push_back(word);
                }
            }
        }

        std::vector<std::string> emails;
        std::string lineE;
        std::regex wordRegexE("-[a-zA-Z0-9!#$@%.^&*()/]+:");
        while (std::getline(file, lineE)) {
            std::string word;
            std::stringstream ss(lineE);
            while (ss >> word) {
                if (regex_match(word, wordRegexE)) {
                    emails.push_back(word);
                }
            }
        }

        std::vector<std::string> websites;
        std::string lineW;
        std::regex wordRegexW("=[a-zA-Z0-9!#$@%.^&*()/]+:");
        while (std::getline(file, lineW)) {
            std::string word;
            std::stringstream ss(lineW);
            while (ss >> word) {
                if (regex_match(word, wordRegexW)) {
                    websites.push_back(word);
                }
            }
        }

        std::cout << "Podaj typ sortowania jaki chcesz: " << std::endl;
        std::cout << "Jeśli chcesz sortować według długości wybierz - 1." << std::endl;
        std::cout << "Jeśli chcesz sortować według alfabetu wybierz - 2." << std::endl;
        std::cout << "Jeśli chcesz sortować według kategorii wybierz - 3." << std::endl;
        std::cout << "Jeśli chcesz sortować według loginu wybierz - 4." << std::endl;
        std::cout << "Jeśli chcesz sortować według emailu wybierz - 5." << std::endl;
        std::cout << "Jeśli chcesz sortować według strony www wybierz - 6." << std::endl;
        std::cout << "Jeśli chcesz wrócić do menu - 7." << std::endl;

        int sortType;
        std::cout << "Podaj typ sortowania jaki chcesz: \n";
        std::cin >> sortType;

        switch (sortType) {
            case 1:
                std::cout << "Sortowanie według długości..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::sort(passwords.begin(), passwords.end(), [](const std::string &a, const std::string &b) {
                    return a.length() < b.length();
                });
                for (auto &i: passwords) {
                    std::cout << i << std::endl;
                }
                std::cout << std::endl;
                break;
            case 2:
                std::cout << "Sorting według alfabetu..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::sort(passwords.begin(), passwords.end());
                for (auto &i: passwords) {
                    std::cout << i << std::endl;
                }
                std::cout << std::endl;
                break;
            case 3:
                std::cout << "Sorting według kategorii..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::sort(categories.begin(), categories.end());
                for (auto &i: categories) {
                    std::cout << i << std::endl;
                }
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "Sortowanie według loginu..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::sort(logins.begin(), logins.end());
                for (auto &i: logins) {
                    std::cout << i << std::endl;
                }
                std::cout << std::endl;
                break;
            case 5:
                std::cout << "Sortowanie według emiala..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::sort(emails.begin(), emails.end());
                for (auto &i: emails) {
                    std::cout << i << std::endl;
                }
                std::cout << std::endl;
            case 6:
                std::cout << "Sortowanie według strony www..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::sort(websites.begin(), websites.end());
                for (auto &i: websites) {
                    std::cout << i << std::endl;
                }
                std::cout << std::endl;
            case 7:
                std::cout << "Powrót do menu ..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;
            default:
                std::cout << "Nieprawidłowy input" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;
        }
    }

    auto addCategory() -> void {
        std::string categoryName;

        std::cout << "Pomyślenie dodano kategorię.\n" << std::endl;
        std::cout << "Jeśli chcesz wybrać kategorię - 1.\n" << std::endl;
        std::cout << "Jeśli chcesz zobaczyć kategorie - 2.\n" << std::endl;
        std::cout << "Jeśli chcesz wrócić do menu wybierz - 3.\n" << std::endl;

        int choice;
        std::cout << "Podaj swój wybór: \n" << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Podaj kategorię: " << std::endl;
                std::cin >> categoryName;
                categories.push_back(categoryName);
                break;
            case 2:
                for (int i = 0; i < categories.size(); i++) {
                    std::cout << i + 1 << ". " << categories[i] << std::endl;
                }
                std::cout << std::endl;
                break;
            case 3:
                break;
            default:
                std::cout << "Nieprawidłowy input" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                addCategory();
        }
    }

    auto removeCategory(const std::string filePath) -> void {
        std::fstream file;
        int numberLine = 0;
        std::string categoryNameToRemove;
        int lineNumberToDelete = 1;

        file.open(filePath);

        std::fstream temp;
        temp.open("..\\files\\temp.txt", std::fstream::out);


        while (!file.eof()) {
            std::string line;
            std::getline(file, line);
            std::cout << numberLine << ". " << line << std::endl;
            numberLine++;
        }
        std::cout << std::endl;

        std::cout << "Jeśli chcesz usunąć kategorię wybierz - 1." << std::endl;
        std::cout << "Jeśli chcesz wrócić do menu wybierz - 2.\n" << std::endl;

        int choice;
        std::cout << "Podaj swój wybór: \n" << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Uwaga! To usunie wszystkie hasła w tej kategorii \n" << std::endl;
                std::cout << "Podaj kategorię którą chcesz usunąć: ";
                std::cin >> categoryNameToRemove;

                for (int i = 0; i < categories.size(); i++) {
                    if (categories[i] == categoryNameToRemove) {
                        categories.erase(categories.begin() + i);
                    }
                }

                file.seekg(0, std::ios::beg);

                while (!file.eof()) {
                    std::string line;
                    std::getline(file, line);
                    if (line != categoryNameToRemove) {
                        temp << line << std::endl;
                    }

                    file.close();
                    temp.close();
                    remove(filePath.c_str());
                    rename("..\\files\\temp.txt", filePath.c_str());
                }
                std::cout << "Usunięto kategorię\n" << std::endl;
                break;
            case 2:
                break;
            default:
                std::cout << "Nieprawidłowy input" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                removeCategory(filePath);
        }
    }

    auto generatePassword(int passwordLength, char specialSymbols, char lowercaseLetters, char uppercaseLetters,
                          char numbers) -> std::string {
        std::string password;
        srand(time(NULL));
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
        std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string symbol = "!@#$%&";
        std::string number = "0123456789";
        std::string charsToMakePassword = "";

        if (specialSymbols == 'y') {
            charsToMakePassword += symbol;
        }
        if (lowercaseLetters == 'y') {
            charsToMakePassword += alphabet;
        }
        if (uppercaseLetters == 'y') {
            charsToMakePassword += ALPHABET;
        }
        if (numbers == 'y') {
            charsToMakePassword += number;
        }

        for (int i = 0; i < passwordLength; i++) {
            int random = rand() % charsToMakePassword.length();
            password += charsToMakePassword[random];
        }
        return password;
    }
}
