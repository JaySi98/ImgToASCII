#include <iostream>
#include <Include/Config.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <curl/curl.h>
#include <curl/easy.h>

#include <CommandParser.h>

void PrintCommandParseError(CommandParseResult result);
bool DownloadImage(char* url);
size_t SaveFile(void *ptr, size_t size, size_t nmemb, void* userdata);

int main(int argc, char* argv[])
{   
   CommandParseResult result = CommandParser::ParseCommands(argc, argv);
   if(result == RESULT_OK)
   {
      std::cout << "jest git" << std::endl;
      
      // https://jbzd.com.pl/obr/2473433/co-racja-to-racja.png
      // pobieranie obrazka przy pomocy biblioteki curl
      // przetworzenie obrazka na tekst ASCII przy pomocy biblioteki OpenCV
      if (!DownloadImage(CommandParser::GetUrl()))
      {
         printf("!! Failed to download file: %s\n", argv[1]);
         return -1;
      }

   }
   else
   {
      PrintCommandParseError(result);
   }

   return EXIT_SUCCESS;
}

size_t SaveFile(void *ptr, size_t size, size_t nmemb, void* userdata)
{
   FILE* stream = (FILE*)userdata;
   if (!stream)
   {
      printf("!!! No stream\n");
      return 0;
   }

   size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
   return written;
}

bool DownloadImage(char* url)
{
   FILE* fp = fopen("out.jpg", "wb");
   if (!fp)
   {
      printf("!!! Failed to create file on the disk\n");
      return false;
   }

   CURL* curlCtx = curl_easy_init();
   curl_easy_setopt(curlCtx, CURLOPT_URL, url);
   curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
   curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, SaveFile);
   curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

   CURLcode rc = curl_easy_perform(curlCtx);
   if (rc)
   {
      printf("!!! Failed to download: %s\n", url);
      return false;
   }

   long res_code = 0;
   curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
   if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
   {
      printf("!!! Response code: %ld\n", res_code);
      return false;
   }

   curl_easy_cleanup(curlCtx);

   fclose(fp);

   return true;
}

void PrintCommandParseError(CommandParseResult result)
{
   std::string msg = "";
   switch (result)
   {
      case RESULT_BAD_URL: msg = "Bad url"; break;
      case RESULT_NO_URL:  msg = "Url must be specified. Example: -s <url>"; break;
      default: break;
   }

   std::cout << msg << std::endl;
}
