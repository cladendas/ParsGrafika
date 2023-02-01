#include <iostream>
#include <vector>
#include <fstream>
#include "requestH.h"
#include "takeSubStrH.h"
#include "TgStatObjectH.h"
#include "pathGrafikaUTMshortPathH.h"

void writeFile(std::string city, TgStatObject tgStat) {
    std::string path = "../" + city + ".txt";
    std::ofstream file(path, std::ios::app);

    file << tgStat.name;
    file << '\t';
    file << tgStat.channel;
    file << '\t';
    file << tgStat.count;
    file << '\t';
    file << tgStat.path;
    file << '\n';

    file.close();
}

//парс по адресу канала TgStat
void findStrPathChanTgStat(std::string& str, std::string city) {
    int indStart = 0;
    int indEnd = 0;
    TgStatObject tgStat;

    std::string name = "<title>Telegram-канал \"";
    std::string nameEnd = "\" — ";

    std::string pathChan = "\" — ";
    std::string pathChanEnd = " — TGStat<";

    std::string count = "<h2 class=\"mb-1 text-dark\">";
    std::string countEnd = "</h2>";

    tgStat.name = takeSubStr(indStart, indEnd, city, str, name, nameEnd, false);
    tgStat.channel = takeSubStr(indStart, indEnd, city, str, pathChan, pathChanEnd, false);
    tgStat.count = takeSubStr(indStart, indEnd, city, str, count, countEnd, true);
    tgStat.path = buildPathGrafika(city, tgStat.channel);
    writeFile(city, tgStat);
}

//парс по ссылки на список в TgStat
void findStrListChanTgStat(std::string& str, std::string city) {
    int howMany = 15;
    TgStatObject tgStat;

	//строка с именем канала
	std::string name = "<div class=\"font-16 text-dark text-truncate\">";
	std::string nameEnd = "</div>";

	//адрес канала в телеге
	std::string pathChan = "<a href=\"https://tgstat.ru/channel/";
	std::string pathChanEnd = "\" c";

	//кол-во подписчиков
	std::string count = "<div class=\"font-12 text-truncate\"> <b>";
	std::string countEnd = "</b>";

	int indStart = 0;
	int indEnd = 0;
	int step = 0;
	while (step < howMany) {

        tgStat.channel = takeSubStr(indStart, indEnd, city, str, pathChan, pathChanEnd, false);
        tgStat.name = takeSubStr(indStart, indEnd, city, str, name, nameEnd, false);
        tgStat.count = takeSubStr(indStart, indEnd, city, str, count, countEnd, true);
        tgStat.path = buildPathGrafika(city, tgStat.channel);

        writeFile(city, tgStat);
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