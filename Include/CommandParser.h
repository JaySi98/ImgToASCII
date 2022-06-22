#include <string>
#include <iostream>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>


enum ParseResult
{
    RESULT_OK_URL = 0,        
    RESULT_OK_PATH,
    RESULT_BAD_COMMAND,
};

class CommandParser
{
public:
    CommandParser(void);
    ParseResult ParseCommands(int argc, char* argv[]);
    char* GetUrl(void);
    char* GetFormat(void);
    char* GetImagePath(void);

private:
    ParseResult result;
    const std::string ImgURLRegex;
    const std::string ImgPathRegex;
    char* ImgUrl;
    char* ImgPath;

    bool checkForURL(int argc, char* argv[]);
    bool checkForPath(int argc, char* argv[]);
};