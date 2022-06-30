#include <CommandParser.h>

CommandParser::CommandParser() :
    result(RESULT_ERROR), 
    ImgURLRegex("(https?:\\/\\/.*\\.(?:png|jpg))/i"), 
    ImgPathRegex(".*\\.(jpg|png)$/igm"),
    ImgUrl(""),
    ImgPath("")
{ }

void CommandParser::ParseCommands(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("h", "Shows program options")
        ("u", po::value<std::string>(), "image url")
        ("p", po::value<std::string>(), "image path");
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc),vm);
    po::notify(vm);

    if(vm.count("h"))
    {
        std::cout << desc << std::endl;
        result = RESULT_HELP;
        return;
    }

    if(vm.count("u"))
    {
        std::string option = vm["u"].as<std::string>(); 
        checkURL(option);
        parseSettings(argc,argv);
    }
    else if(vm.count("p"))
    {
        std::string option = vm["p"].as<std::string>();
        checkPath(option);
        parseSettings(argc,argv);
    }
}

void CommandParser::parseSettings(int argc, char* argv[])
{
    po::options_description desc("Comversion settings");
    desc.add_options()
        ("u", po::value<std::string>(), "image url")
        ("p", po::value<std::string>(), "image path");
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc),vm);
    po::notify(vm);

    // TODO
}

void CommandParser::checkURL(std::string line)
{
    if(regex_match(line, regex(ImgURLRegex), match_partial))
    {
        ImgUrl = line;
        result = RESULT_OK_URL;
    }
}

void CommandParser::checkPath(std::string line)
{
    if(regex_match(line, regex(ImgPathRegex), match_partial))
    {
        ImgPath = line;   
        result = RESULT_OK_PATH;
    }
}

std::string CommandParser::GetFormat(void)
{
    std::string output = "";

    if(result == RESULT_OK_PATH)
        output = filesystem::extension(ImgPath);
    else if(result == RESULT_OK_URL)
        output = filesystem::extension(ImgUrl);
    
    return output;
}

std::string CommandParser::GetUrl(void)
{
    if(result == RESULT_OK_URL)
        return ImgUrl;
    else
        throw "No valid URL specified";
}

std::string CommandParser::GetImagePath(void)
{
    if(result == RESULT_OK_PATH)
        return ImgPath;
    else
        throw "No valid path specified";
}