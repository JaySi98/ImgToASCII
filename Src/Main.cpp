#include <iostream>
#include <Include/Config.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <curl/curl.h>
#include <curl/easy.h>

#include <CommandParser.h>

void PrintCommandParseError(CommandParseResult result);

int main(int argc, char* argv[])
{   
   CommandParseResult result = CommandParser::ParseCommands(argc, argv);
   if(result == RESULT_OK)
   {
      ;
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
