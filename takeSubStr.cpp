#include <regex>
#include "pathGrafikaUTMshortPathH.h"

std::string takeSubStr(int& indStart, int& indEnd,
                std::string city,
                std::string& str, std::string& subStr, std::string& endSubStr, bool isInt) {
    std::string data = "";
    std::regex reg("[\\s]+");
    str = std::regex_replace(str, reg, " ");
    //первый индекс тега, указывающего на нужное значение
    if ((indStart = str.find(subStr, indStart)) != std::string::npos) {
        indStart += subStr.length(); //крайний индекс тега, указывающего на нужное значение
        indEnd = indStart; //индекс начала нужного значения и конца тега

        //крайний индекс нужного значения
        if ((indStart = str.find(endSubStr, indStart)) != std::string::npos) {
            int size = indStart - indEnd; //длина нужного значения

            //если ожидается int
            //в TgStat три знака в числе разделются пробелом
            if(isInt) {
                std::regex reg("[\\s]+");
                std::string tmpName = str.substr(indEnd, size);
                std::string tmp = std::regex_replace(tmpName, reg, "");
                data = '\t' + tmp;
            } else {
                std::string tmpName = str.substr(indEnd, size); //нужное значение
                data = '\t' + tmpName;
            }
        }
    }

    return data;
}