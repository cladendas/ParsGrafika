#include <cpr/cpr.h>

//запрос по url
//результат запроса по указателю в resp
std::string request(std::string& url) {
    cpr::Response r = cpr::Get(cpr::Url(url));
    return r.text;
}