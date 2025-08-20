#include "Harl.hpp"

// Returns one of: "ERROR", "WARNING", "INFO", "DEBUG", or "UNKNOWN"
static std::string pickLevelFromSentence(const std::string& s) 
{
    const std::string errorKeys[] = { "calm", "quiet", "down", "lower" };
    const std::string warnKeys[]  = { "another", "else" };
    const std::string infoKeys[]  = { "cost", "money", "extra" };
    const std::string dbgKeys[]   = { "offer", "order" };

    size_t i;

    for (i = 0; i < sizeof(errorKeys)/sizeof(errorKeys[0]); ++i)
        if (s.find(errorKeys[i]) != std::string::npos) return "ERROR";

    for (i = 0; i < sizeof(warnKeys)/sizeof(warnKeys[0]); ++i)
        if (s.find(warnKeys[i]) != std::string::npos) return "WARNING";

    for (i = 0; i < sizeof(infoKeys)/sizeof(infoKeys[0]); ++i)
        if (s.find(infoKeys[i]) != std::string::npos) return "INFO";

    for (i = 0; i < sizeof(dbgKeys)/sizeof(dbgKeys[0]); ++i)
        if (s.find(dbgKeys[i]) != std::string::npos) return "DEBUG";

    return "UNKNOWN";
}

int main(int ac, char **av) 
{
    if (ac != 2) 
    {
        std::cerr << "If you want to talk to Harl, type: " << av[0] 
                    << " \"message\"" << std::endl;
        std::cout << "Use the double quotes! " << std::endl;
        return 1;
    }

    std::string msg = av[1];
    std::string level = pickLevelFromSentence(msg);

    Harl h;

    if (level == "UNKNOWN") 
    {
        std::cout << GREEN << "Harl says: what are you mumbling about?" << ERASE 
                    << std::endl ;
        std::cout << "[No trigger word found - Try one of the following sentences] " 
                    << std::endl;
        std::cout << "\"What can I offer you today?\"" << std::endl;
        std::cout << "\"Would you like anything else?\"" << std::endl;
        std::cout << "\"That will cost you 1 euro extra\"" << std::endl;
		std::cout << "\"Please calm down.\"" << std::endl;
        std::cout << "\"You need to lower your voice\"" << std::endl;
        return 0;
    }
    std::cout << GREEN << "Harl says: " << ERASE;
    h.complain(level);
    return 0;
}