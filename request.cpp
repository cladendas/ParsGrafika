#include <cpr/cpr.h>

//запрос по url
//результат запроса по указателю в resp
void request(std::string& url, std::string& resp) {
    cpr::Response r = cpr::Get(cpr::Url(url));
    resp = r.text;
}