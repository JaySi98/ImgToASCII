#include <CommandParser.h>


CommandParser::CommandParser() :
    result(RESULT_ERROR), 
    ImgURLRegex("(https?:\\/\\/.*\\.(?:png|jpg))/i"), 
    ImgPathRegex("/.*\\.(jpg|png)$/igm"),
    ImgUrl(nullptr),
    ImgPath(nullptr)
{ }

void CommandParser::ParseCommands(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("-h", "Shows program options")
        ("-u", po::value<std::string>()->default_value(""), "image url")
        ("-p", po::value<std::string>()->default_value(""), "image path");
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc),vm);
    po::notify(vm);

    if(vm.count("-u"))
    {
        std::string option = vm["-u"].as<std::string>(); 
        checkURL(option);
    }
    else if(vm.count("-p"))
    {
        std::string option = vm["-p"].as<std::string>();
        checkPath(option);
    }
}

void CommandParser::checkURL(std::string line)
{
    if(regex_match(line, regex(ImgURLRegex), match_partial))
    {
        ImgUrl = const_cast<char*>(line.c_str());
        result = RESULT_OK_URL;
    }
}

void CommandParser::checkPath(std::string line)
{
    if(regex_match(line, regex(ImgPathRegex), match_partial))
    {
        ImgPath = const_cast<char*>(line.c_str());   
        result = RESULT_OK_PATH;
    }
}

char* CommandParser::GetFormat(void)
{
    char* output = nullptr;

    if(result == RESULT_OK_PATH)
        output = const_cast<char*>(filesystem::extension(ImgPath).c_str());
    else if(result == RESULT_OK_URL)
        output = const_cast<char*>(filesystem::extension(ImgUrl).c_str());
    
    return output;
}

char* CommandParser::GetUrl(void)
{
    if(result == RESULT_OK_URL)
        return ImgUrl;
    else
        throw "No valid URL specified";
}

char* CommandParser::GetImagePath(void)
{
    if(result == RESULT_OK_PATH)
        return ImgPath;
    else
        throw "No valid path specified";
}

ParseResult CommandParser::GetResult(void)
{
    return result;
}