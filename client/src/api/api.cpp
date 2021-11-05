#include "api/api.h"
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;

api::api()
{
    json j = {};
    j["test"] = "TEST";
    j["b"]["a"] = "TEST";

    string str = j.dump(4);
    printf("%s\n", str.c_str());
}