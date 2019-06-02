#include <iostream>
#include <string>


#define CURL_STATICLIB
#include "curl/curl.h"

#ifdef _DEBUG
#	pragma comment(lib, "curl/libcurl_a_debug.lib") 
#else
#	pragma comment(lib, "curl/libcurl_a.lib")
#endif

static int writer(char* data, size_t size, size_t nmemb, std::string* writerData);

int main()
{
	std::cout << "Hello World!" << std::endl;
	std::string replay;

	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl = nullptr;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "192.168.2.74");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &replay);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		CURLcode code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	std::cout << "AND SAGI SAID: " << replay << std::endl;

	return 0;
}

static int writer(char* data, size_t size, size_t nmemb, std::string* writerData)
{
	if (writerData == NULL)
		return 0;

	writerData->append(data, size * nmemb);

	return size * nmemb;
}
