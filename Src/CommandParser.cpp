#include <CommandParser.h>

CommandParser::CommandParser() :
    result(RESULT_ERROR), 
    ImgURLRegex("(https?:\\/\\/.*\\.(?:png|jpg))/i"), 
    ImgPathRegex(".*\\.(jpg|png)$/igm"),
    ImgUrl(""),
    ImgPath("")
{ 
    params.characters = "%W&Q0m$BHD8#RbUAOpgXGhVw49k6PKdq|yY[]}{jECnSo)(uxZl12vat5IeFJ3/7\\TLi?*frs!cz><+\";^=,:'_-`. ";
    params.charWidth  = 2;
    params.charHeight = 4;
    params.settings   = 0;
}

void CommandParser::ParseCommands(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("h", "Shows program options")
        ("u", po::value<std::string>(), "image url")
        ("p", po::value<std::string>(), "image path")
        ("cw",          po::value<int>(),           "charcters width")
        ("ch",          po::value<int>(),           "charcters height")
        ("characters",  po::value<std::string>(),   "characters to use")
        ("dimensions",  po::value<bool>(),          "to keep image dimensions");
    
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
        parseSettings(argc,argv, vm);
    }
    else if(vm.count("p"))
    {
        std::string option = vm["p"].as<std::string>();
        checkPath(option);
        parseSettings(argc,argv, vm);
    }
}

void CommandParser::parseSettings(int argc, char* argv[], po::variables_map& vm)
{
    if(vm.count("cw"))
    {
        params.charWidth = vm["cw"].as<int>(); 
    }
    if(vm.count("ch"))
    {
        params.charHeight = vm["ch"].as<int>();
    }
    if(vm.count("dimensions"))
    {
        params.settings |= SETT_KEEP_DIMENSION; 
    }
    if(vm.count("characters"))
    {
        params.characters = vm["characters"].as<std::string>();
    }
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