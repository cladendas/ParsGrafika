#include <iostream>
#include <vector>
#include <fstream>
#include "requestH.h"
#include "takeSubStrH.h"

void writeFile(std::string city, std::string data) {
    std::string path = "../" + city + ".txt";
    std::ofstream file(path, std::ios::app);

    file << data;

    file.close();
}

//парс по адресу канала TgStat
void findStrPathChanTgStat(std::string& str, std::string city) {
    int indStart = 0;
    int indEnd = 0;

    std::string name = "<title>Telegram-канал \"";
    std::string nameEnd = "\" — ";

    std::string pathChan = "\" — ";
    std::string pathChanEnd = " — TGStat<";

    std::string count = "<h2 class=\"mb-1 text-dark\">";
    std::string countEnd = "</h2>";

    std::string data = "";
    std::string pathGrafika = "";

    data += takeSubStr(indStart, indEnd, city, str, name, nameEnd, pathGrafika, false, false);
    data += takeSubStr(indStart, indEnd, city, str, pathChan, pathChanEnd, pathGrafika, false, true);
    data += takeSubStr(indStart, indEnd, city, str, count, countEnd, pathGrafika, true, false);

    data += '\n';
    writeFile(city, data);
    data = "";
}

//парс по ссылки на список в TgStat
void findStrListChanTgStat(std::string& str, std::string city) {
    int howMany = 10;

	//строка с именем канала
	std::string name = "<div class=\"font-16 text-dark text-truncate\">";
	std::string nameEnd = "</div>";

	//адрес канала в телеге
	std::string pathChan = "<a href=\"https://tgstat.ru/channel/";
	std::string pathChanEnd = "\" c";

	//кол-во подписчиков
	std::string count = "<div class=\"font-12 text-truncate\"> <b>";
	std::string countEnd = "</b>";

    std::string pathGrafika = "";
    std::string data = "";

	int indStart = 0;
	int indEnd = 0;
	int step = 0;
	while (step < howMany) {

        data += takeSubStr(indStart, indEnd, city, str, pathChan, pathChanEnd, pathGrafika, false, true);
        data += takeSubStr(indStart, indEnd, city, str, name, nameEnd, pathGrafika, false, false);
        data += takeSubStr(indStart, indEnd, city, str, count, countEnd, pathGrafika, true, false);

        data += '\n';
        writeFile(city, data);
        data = "";
		step++;
	}
}

void resp(std::string city, std::string url) {
    std::string resp = "";
    std::string tmpCity = "";
    std::vector<std::string> urls;
    bool what = false;

    if (city.find("-") != std::string::npos) {
        tmpCity += "/";
    }

    if (url.find(".ru/tag") != std::string::npos) {
        std::cout << "Ищу 1...\n";
        resp = request(url);
        findStrListChanTgStat(resp, city);
    } else if (url.find(".ru/channel") != std::string::npos) {
        std::cout << "\nИщу 2...\n";
        resp = request(url);
        findStrPathChanTgStat(resp, city);
        std::cout << '\n';
    }
}

void readFile() {
    std::string path = "../param.txt";
    std::string city = "";
    std::string data = "";
    //первая строка в файле относится к наименованию города
    bool cityFlag = true;
    std::ifstream file1(path);

    if (file1.is_open()) {
        while(!file1.eof()) {
            if (cityFlag) {
                file1 >> city;
                cityFlag = false;
            }
            file1 >> data;

            resp(city, data);
        }
    }
    file1.close();
}

int main() {
    readFile();
	return 0;
}