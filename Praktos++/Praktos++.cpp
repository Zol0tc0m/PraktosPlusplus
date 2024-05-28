#include <iostream>
#include <windows.h>
#include <string>

typedef bool (*CheckWordsAndSentenceFunc)(const char*, const char*);

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    HINSTANCE hGetProcIDDLL = LoadLibraryA("DLLMain.dll");

    if (hGetProcIDDLL == nullptr) {
        std::cout << "Could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    CheckWordsAndSentenceFunc checkWordsAndSentence = (CheckWordsAndSentenceFunc)GetProcAddress(hGetProcIDDLL, "CheckWordsAndSentence");
    if (!checkWordsAndSentence) {
        std::cout << "Could not locate the function" << std::endl;
        FreeLibrary(hGetProcIDDLL);
        return EXIT_FAILURE;
    }

    std::string sentence, wordsToFind;
    std::cout << "Введите слово или предложение: ";
    std::getline(std::cin, sentence);
    std::cout << "Введите слово или букву, которую хотите найти: ";
    std::getline(std::cin, wordsToFind);

    bool result = checkWordsAndSentence(sentence.c_str(), wordsToFind.c_str());
    std::cout << "Результат: " << (result ? "есть!" : "нету") << std::endl;

    FreeLibrary(hGetProcIDDLL);

    return EXIT_SUCCESS;
}