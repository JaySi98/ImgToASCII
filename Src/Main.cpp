#include <iostream>
#include <Include/Config.h>
#include <CommandParser.h>
#include <ImageConverter.h>
#include <ImageDownloader.h>


void PrintCommandParseError(CommandParseResult result);
bool DownloadImage(void);
bool ConvertImage(void);

int main(int argc, char* argv[])
{   
   CommandParseResult result = CommandParser::ParseCommands(argc, argv);
   if(result == RESULT_OK)
   {  
      if(!DownloadImage())
      {
         std::cout << "Failed to download file: " <<  CommandParser::GetUrl() << std::endl;
         return EXIT_FAILURE;         
      }

      if(!ConvertImage())
      {
         std::cout << "Failed to convert image: " << std::endl;
         return EXIT_FAILURE;
      }   
   }
   else
   {
      PrintCommandParseError(result);
   }

   return EXIT_SUCCESS;
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

bool DownloadImage(void)
{
   bool status = false;
   char* url = CommandParser::GetUrl();
   ImageDownloader downloader;

   if(downloader.DownloadImage(url, ""))
   {
      status = true;
   }

   return status;
}

bool ConvertImage()
{
   bool status = false;
   ImageConverter converter("");      
   
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
