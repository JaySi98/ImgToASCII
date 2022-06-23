#include <string>
#include <iostream>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace boost;
namespace po = boost::program_options;

enum ParseResult
{
    RESULT_ERROR    = 0x00,
    RESULT_OK_URL   = 0x01,        
    RESULT_OK_PATH  = 0x02,
};

class CommandParser
{
public:
    CommandParser(void);
    void ParseCommands(int argc, char* argv[]);
    
    ParseResult GetResult(void);
    char* GetUrl(void);
    char* GetFormat(void);
    char* GetImagePath(void);

private:
    ParseResult result;
    const std::string ImgURLRegex;
    const std::string ImgPathRegex;
    char* ImgUrl;
    char* ImgPath;

    void checkURL(std::string line);
    void checkPath(std::string line);
};