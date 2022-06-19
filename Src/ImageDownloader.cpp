#include <ImageDownloader.h>

bool ImageDownloader::DownloadImage(char* url, char* filePath)
{
   FILE* fp = fopen(filePath, "wb");
   if (!fp)
   {
      std::cout << "Failed to create file on the disk" << std::endl;
      return false;
   }

   CURL* curlCtx = curl_easy_init();
   curl_easy_setopt(curlCtx, CURLOPT_URL, url);
   curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
   curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, SaveFile);
   curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

   CURLcode rc = curl_easy_perform(curlCtx);
   if(rc)
   {
      std::cout << "Failed to download:" << url << std::endl;
      return false;
   }

   long res_code = 0;
   curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
   if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
   {
      std::cout << "Response code: " << res_code << std::endl;
      return false;
   }

   curl_easy_cleanup(curlCtx);
   fclose(fp);

   return true;
}

size_t ImageDownloader::SaveFile(void *ptr, size_t size, size_t nmemb, void* userdata)
{
    FILE* stream = (FILE*)userdata;
   if (!stream)
   {
      std::cout << "No stream" << std::endl;
      return 0;
   }

   size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
   return written;
}