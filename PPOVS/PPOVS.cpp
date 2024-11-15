#include "MarkdownExtractor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <locale>
#include <vector>

using namespace std;


void MarkdownExtractor::extract(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file");
    }

    string line;
    while (getline(file, line)) {
        extractHeaders(line);
        extractParagraphs(line);
        extractBoldText(line);
    }
    file.close();

    // Вывод заголовков
    for (const auto& header : headers) {
        cout << "Заголовок: " << header << endl;
    }
    // Вывод жирного текста
    for (const auto& boldText : boldTexts) {
        cout << "Жирный текст: " << boldText << endl;
    }

    // Вывод количества заголовков больше 10 символов
    cout << "Количество заголовков больше 10 символов: " << longHeaderCount << endl;

    // Вывод количества абзацев
    cout << "Количество абзацев: " << paragraphCount << endl;
}

void MarkdownExtractor::extractHeaders(const string& line) {
    regex headerRegex(R"(^(#+)\s*(.*)$)");
    smatch match;
    if (regex_search(line, match, headerRegex)) {
        string header = match.str(2);
        header = removeBoldFromHeader(header); // Удаляем жирный текст из заголовка
        headers.push_back(header); // Сохраняем заголовок

        if (header.length() > 10) {
            longHeaderCount++; // Увеличиваем счетчик заголовков > 10 символов
        }
    }
}

void MarkdownExtractor::extractParagraphs(const string& line) {
    if (!line.empty() && line[0] != '#') {
        paragraphCount++; // Увеличиваем счетчик абзацев
    }
}

void MarkdownExtractor::extractBoldText(const string& line) {
    regex boldRegex(R"(\*\*(.*?)\*\*)");
    sregex_iterator it(line.begin(), line.end(), boldRegex);
    sregex_iterator end;

    while (it != end && line[0] != '#') {
        boldTexts.push_back(it->str(1)); // Сохраняем жирный текст
        ++it;
    }
}

string MarkdownExtractor::removeBoldFromHeader(const string& header) {
    return regex_replace(header, regex(R"(\*\*(.*?)\*\*)"), "$1"); // Заменяем жирный текст на обычный
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    try {
        MarkdownExtractor extractor;
        extractor.extract("C:/Users/Danilka/Desktop/123.md");
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
