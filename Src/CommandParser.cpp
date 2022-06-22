#include <CommandParser.h>


CommandParser::CommandParser() :
    result(RESULT_BAD_COMMAND), 
    ImgURLRegex("(https?:\\/\\/.*\\.(?:png|jpg))/i"), 
    ImgPathRegex(""),
    ImgUrl(nullptr),
    ImgPath(nullptr)
{ }

ParseResult CommandParser::ParseCommands(int argc, char* argv[])
{
    result = RESULT_BAD_COMMAND;

    if(checkForURL(argc, argv))
    {
        result = RESULT_OK_URL;
    }
    else if(checkForPath(argc, argv))
    {
        result = RESULT_OK_PATH;
    }
    else
    {
        result = RESULT_BAD_COMMAND;
    }

    return result;
}

bool CommandParser::checkForURL(int argc, char* argv[])
{
    bool status = false;
    if(argc >= 3)
    {
        if(strcmp(argv[1], "-u") == 0 && boost::regex_match(argv[2], boost::regex(ImgURLRegex), boost::match_partial))
        {
            ImgUrl = argv[2];   
            status = true;
        }
    }

    return status;
}

bool CommandParser::checkForPath(int argc, char* argv[])
{
    bool status = false;
    if(argc >= 3)
    {
        if(strcmp(argv[1], "-s") == 0 && boost::regex_match(argv[2], boost::regex(ImgPathRegex), boost::match_partial))
        {
            ImgPath = argv[2];   
            status = true;
        }
    }

    return status;
}

char* CommandParser::GetUrl(void)
{
    if(result == RESULT_OK_URL)
        return ImgUrl;
    else
        throw "No valid URL specified";
}
char* CommandParser::GetFormat(void)
{
    char* output = nullptr;

    if(result == RESULT_OK_PATH)
        output = const_cast<char*>(boost::filesystem::extension(ImgUrl).c_str());
    else if(result == RESULT_OK_URL)
        output = const_cast<char*>(boost::filesystem::extension(ImgPath).c_str());
    
    return output;
}

char* CommandParser::GetImagePath(void)
{
    if(result == RESULT_OK_PATH)
        return ImgPath;
    else
        throw "No valid path specified";
}