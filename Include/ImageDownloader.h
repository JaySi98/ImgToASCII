#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>

class ImageDownloader
{
public:
    bool DownloadImage(char* url, char* filePath);

private:
    static size_t SaveFile(void *ptr, size_t size, size_t nmemb, void* userdata);
};