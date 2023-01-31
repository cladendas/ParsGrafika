#include <cpr/cpr.h>
std::string buildPathGrafika(std::string& city, std::string& channel) {

    std::string total = "https://kursi-risovaniya.ru/" + city + "?utm_source=telegram&utm_medium=banner&utm_campaign=" + channel;

    std::string shPath = "https://clck.ru/--";
    std::string result = "";

    cpr::Response r = cpr::Get(cpr::Url(shPath),
                               cpr::Parameters{{"url", total}});
    result = total + '\t' + r.text;
    return result;
}
