// DLLMain.cpp
#include <windows.h>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <cctype>

// Функция для разделения строки на слова
std::set<std::string> split_words(const std::string& str) {
    std::set<std::string> words;
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        words.insert(word);
    }
    return words;
}

// Функция для проверки вхождения слов в предложение
bool words_in_sentence(const std::string& sentence, const std::set<std::string>& words) {
    std::string lower_sentence = sentence;
    std::transform(lower_sentence.begin(), lower_sentence.end(), lower_sentence.begin(), ::tolower);

    for (const auto& word : words) {
        std::string lower_word = word;
        std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);

        if (lower_sentence.find(lower_word) == std::string::npos) {
            return false;
        }
    }
    return true;
}

extern "C" __declspec(dllexport) bool CheckWordsAndSentence(const char* sentence, const char* wordsToFind) {
    std::set<std::string> wordsToFindSet = split_words(wordsToFind);

    // Проверка наличия слов в предложении
    if (!words_in_sentence(sentence, wordsToFindSet)) {
        return false;
    }

    // Проверка наличия слов в отдельности
    for (const auto& word : wordsToFindSet) {
        std::string word_str(word);
        if (std::string(sentence).find(word_str) == std::string::npos) {
            return false;
        }
    }

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}