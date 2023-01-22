#include <cpr/cpr.h>
void buildPathGrafika(std::string& city, std::string& chanel, std::string& result) {

    std::string total = "https://kursi-risovaniya.ru/" + city + "?utm_source=telegram&utm_medium=banner&utm_campaign=" + chanel;

    std::string shPath = "https://clck.ru/--";

//    request(shPath, shPath);

    cpr::Response r = cpr::Get(cpr::Url(shPath),
                               cpr::Parameters{{"url", total}});
    result = total + '\t' + r.text;
//    result = total;
}
