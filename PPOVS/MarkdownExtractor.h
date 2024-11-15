#ifndef MARKDOWNEXTRACTOR_H
#define MARKDOWNEXTRACTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

class MarkdownExtractor {
public:
    void extract(const string& filename);

private:
    vector<string> headers;
    vector<string> paragraphs;
    vector<string> boldTexts;
    int paragraphCount = 0; // Счетчик абзацев
    int longHeaderCount = 0; // Счетчик заголовков > 10 символов

    void extractHeaders(const string& line);
    void extractParagraphs(const string& line);
    void extractBoldText(const string& line);
    string removeBoldFromHeader(const string& header);
};

#endif // MARKDOWNEXTRACTOR_H
