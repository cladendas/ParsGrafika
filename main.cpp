#include <iostream>
#include <vector>
#include <fstream>
#include "requestH.h"
#include "takeSubStrH.h"

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

    std::string pathGrafika = "";

    takeSubStr(indStart, indEnd, city, str, name, nameEnd, pathGrafika, false, false);
    takeSubStr(indStart, indEnd, city, str, pathChan, pathChanEnd, pathGrafika, false, true);
    takeSubStr(indStart, indEnd, city, str, count, countEnd, pathGrafika, true, false);

    std::cout << '\t' << pathGrafika;
    std::cout << '\n';
}

//парс списка каналов по одному адресу в TgStat
void findStrListChanTgStat(std::string& str, std::string city) {
    int howMany = 20;

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

	int indStart = 0;
	int indEnd = 0;
	int step = 0;
	while (step < howMany) {

        takeSubStr(indStart, indEnd, city, str, pathChan, pathChanEnd, pathGrafika, false, true);
        takeSubStr(indStart, indEnd, city, str, name, nameEnd, pathGrafika, false, false);
        takeSubStr(indStart, indEnd, city, str, count, countEnd, pathGrafika, true, false);

        std::cout << '\t' << pathGrafika;
        std::cout << '\n';
		step++;
	}
}

void resp() {
    std::string resp = "";
    std::string city = "ekaterinburg";
    std::vector<std::string> urls;
    std::string path = "./urls.txt";
    bool what = false;
//    std::string what = "";

	//адрес на выборку региона
//	std::string url = "https://tgstat.ru/tag/volgograd-region";
//	std::string url = "https://tgstat.ru/tag/udmurtia-region";
//	std::string url = "https://tgstat.ru/tag/kaliningrad-region";
//	std::string url = "https://tgstat.ru/tag/nn-region";
	std::string url = "https://tgstat.ru/tag/ekb-region";

    std::cout << "Для какого города (латиница)?\n";
    std::cin >> city;

    if (city.find("-") != std::string::npos) {
        city += "/";
    }

    std::cout << "Что парсим? \n0 = Ссылка на список с TgStat\n1 = Список ссылок на каналы в TgStat\n";
    std::cin >> what;

//    if (what.find("tag") != std::string::npos) {
//        std::cout << "Ищу...\n";
//        request(url, resp);
//        findStrListChanTgStat(resp, city);
//    } else if (what.find("channel") != std::string::npos) {
//        std::string tmp = "";
//        std::string list = "";
//        std::string exampleStr = "https://tgstat.ru/channel/@";
//        std::cout << "Введите список ссылок:\n";
//
//        while (true) {
//            std::cin >> tmp;
//            if (tmp.find(exampleStr) == std::string::npos) {
//                break;
//            }
//            urls.push_back(tmp);
//        }
//
//        std::cout << "\nИщу...\n";
//        for (std::string url : urls) {
//            request(url, resp);
//            findStrPathChanTgStat(resp, city);
//        }
//        std::cout << '\n';
//    }



    if (!what) {
        std::cout << "Введите ссылку:\n";
        std::cin >> url;
        std::cout << "Ищу...\n";
        request(url, resp);
        findStrListChanTgStat(resp, city);
    } else {
        std::string tmp = "";
        std::string list = "";
        std::string exampleStr = "https://tgstat.ru/channel/@";
        std::cout << "Введите список ссылок:\n";

        while (true) {
            std::cin >> tmp;

            if (tmp.find(exampleStr) == std::string::npos) {
                break;
            }

            urls.push_back(tmp);
        }

        std::cout << "\nИщу...\n";
        for (std::string url : urls) {
            request(url, resp);
            findStrPathChanTgStat(resp, city);
        }
        std::cout << '\n';
    }



	// std::ifstream file(path);
	// if (file.is_open()) {
	// 	while(!file.eof()) {
	// 		std::string tmp = "";
	// 		file >> tmp;
	// 		urls.push_back(tmp);
	// 	}
	// }
	// file.close();
}

int main() {
	resp();
	return 0;
}