#include <iostream>
#include <Include/Config.h>
#include <CommandParser.h>
#include <ImageConverter.h>
#include <ImageDownloader.h>

bool DownloadImage(char* url, char* path);
bool ConvertImage(std::string imagePath);

int main(int argc, char* argv[])
{   
   char* imageName = "image";
   CommandParser commandParser;
   commandParser.ParseCommands(argc, argv);

   if(commandParser.GetResult() == RESULT_OK_URL)
   {  
      if(!DownloadImage(commandParser.GetUrl(), strcat(imageName,commandParser.GetFormat())))
      {
         std::cout << "Failed to download file: " <<  commandParser.GetUrl() << std::endl;
         return EXIT_FAILURE;         
      }

      if(!ConvertImage(strcat(imageName,commandParser.GetFormat())))
      {
         std::cout << "Failed to convert image: " << std::endl;
         return EXIT_FAILURE;
      }   
   }
   else if(commandParser.GetResult() == RESULT_OK_PATH)
   {
      // TODO
   }
   else
   {
      std::cout << "Url or image path must be specified. Example: -u/-s <url>/<path>" << std::endl;
   }

   return EXIT_SUCCESS;
}

bool DownloadImage(char* url, char* path)
{
   bool status = false;
   ImageDownloader downloader;

   if(downloader.DownloadImage(url, path))
   {
      status = true;
   }

   return status;
}

bool ConvertImage(std::string imagePath)
{
   bool status = false;
   ImageConverter converter(imagePath);      
   
   try
   {
      converter.ConvertToText();
      status = true;
   }
   catch(const std::exception& e)
   {
      std::cerr << e.what() << '\n';
      status = false;
   }

   return status;
}
