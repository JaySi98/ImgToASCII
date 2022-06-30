#pragma once

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
    RESULT_HELP     = 0x04,
};

typedef struct
{

}ConversionSettings;

class CommandParser
{
public:
    CommandParser(void);
    void ParseCommands(int argc, char* argv[]);
    std::string GetUrl(void);
    std::string GetFormat(void);
    std::string GetImagePath(void);
    
    ParseResult result;
    ConversionSettings settings;

private:
    void checkURL(std::string line);
    void checkPath(std::string line);
    void parseSettings(int argc, char* argv[]);

    const std::string ImgURLRegex;
    const std::string ImgPathRegex;
    std::string ImgUrl;
    std::string ImgPath;

};