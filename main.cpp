#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string response_data;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    response_data.append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://randomuser.me/api/");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Response data: " << response_data << std::endl;

            try {
                json jsonData = json::parse(response_data);
                auto user = jsonData["results"][0];

                std::cout << "Name: " << user["name"]["first"] << " " << user["name"]["last"] << std::endl;
                std::cout << "Gender: " << user["gender"] << std::endl;
                std::cout << "Email: " << user["email"] << std::endl;
                std::cout << "Phone: " << user["phone"] << std::endl;
            } catch (json::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}