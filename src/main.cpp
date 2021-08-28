#include <iostream>
#include "curl/curl.h"

using namespace std;

int main()
{
    //for testing CURL
    CURL *req = curl_easy_init();
    CURLcode res;
    curl_easy_cleanup(req);

    printf("Test\nTest2\n");
}