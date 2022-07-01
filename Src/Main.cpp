#include <iostream>
#include <Include/Config.h>
#include <CommandParser.h>
#include <ImageConverter.h>
#include <ImageDownloader.h>

bool DownloadImage(std::string url, std::string path);
bool ConvertImage(std::string imagePath, ConversionParams params);

int main(int argc, char* argv[])
{   
   CommandParser commandParser;
   commandParser.ParseCommands(argc, argv);

   if(commandParser.result == RESULT_OK_URL)
   {  
      std::string downloadFileName = "image" + commandParser.GetFormat();

      if(!DownloadImage(commandParser.GetUrl(), downloadFileName))
      {
         std::cout << "Failed to download file: " <<  commandParser.GetUrl() << std::endl;
         return EXIT_FAILURE;         
      }

      if(!ConvertImage(downloadFileName, commandParser.params))
      {
         std::cout << "Failed to convert image: " << std::endl;
         return EXIT_FAILURE;
      }   
   }
   else if(commandParser.result == RESULT_OK_PATH)
   {
      if(!ConvertImage(commandParser.GetImagePath(), commandParser.params))
      {
         std::cout << "Failed to convert image: " << std::endl;
         return EXIT_FAILURE;
      }   
   }
   else
   {
      std::cout << "Url or image path must be specified. Example: -u/-s <url>/<path>" << std::endl;
   }

   return EXIT_SUCCESS;
}

bool DownloadImage(std::string url, std::string path)
{
   bool status = false;
   ImageDownloader downloader;

   if(downloader.DownloadImage(url, path))
   {
      status = true;
   }

   return status;
}

bool ConvertImage(std::string imagePath, ConversionParams params)
{
   bool status = false;
   ImageConverter converter(imagePath, params);      
   
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
