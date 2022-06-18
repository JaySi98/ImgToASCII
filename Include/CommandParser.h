#include <string>
#include <boost/regex.hpp>
#include <iostream>
enum CommandParseResult
{
    RESULT_OK = 0,    
    RESULT_NO_URL,
    RESULT_BAD_URL,
};

class CommandParser
{
public:
    static CommandParseResult ParseCommands(int argc, char* argv[]);
    static std::string GetUrl(void);

private:
    static CommandParseResult result;
    static const std::string ImgURLRegex;
    static std::string ImgUrl;
};