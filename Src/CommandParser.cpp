#include <CommandParser.h>

CommandParseResult CommandParser::result(RESULT_NO_URL); 
const std::string CommandParser::ImgURLRegex("(https?:\\/\\/.*\\.(?:png|jpg))/i");
std::string CommandParser::ImgUrl("");

CommandParseResult CommandParser::ParseCommands(int argc, char* argv[])
{
    result = RESULT_NO_URL;

    // url is not specified
    if(argc < 3 || strcmp(argv[1], "-s") != 0)
    {
        result = RESULT_NO_URL;
    }
    else if(boost::regex_match(argv[2], boost::regex(ImgURLRegex), boost::match_partial))
    {
        ImgUrl = argv[2];        
        result = RESULT_OK;
    }
    else
    {
        result = RESULT_BAD_URL;
    }

    return result;
}

std::string CommandParser::GetUrl(void)
{
    if(result == RESULT_OK)
        return ImgUrl;
    else
        throw "No valid URL specified";
}