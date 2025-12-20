#include "replace.hpp"


Replace::Replace(const std::string& filename, const std::string& s1, const std::string& s2) 
    : filename(filename), s1(s1), s2(s2) {}

bool Replace::proccess()
{
    std::string content;
    std::string line;
    size_t      pos;

    if (s1.empty())
    {
        std::cerr << "Error : s1 cannt be empty" << std::endl;
        return (false);
    }

    std::ifstream infile(filename.c_str());
    if (!infile)
    {
        std::cerr << "Error : cannot open file" << std::endl;
        return (false);
    }

    
    while (std::getline(infile, line))
    {
        
        content += line;
        if (!infile.eof())
            content += '\n';
    }
    
    if (infile.bad())
    {
        std::cerr << "Error : reading file failed" << std::endl;
        return (false);
    }
    

    pos = 0;
    while (true)
    {
        pos = content.find(s1, pos);
        if (pos == std::string::npos)
            break;
        
        content.erase(pos, s1.size());
        content.insert(pos, s2);
        pos += s2.size();
    }

    std::ofstream outfile((filename + ".replace").c_str());
    if (!outfile)
    {
        std::cerr << "Error: cannot create file" << std::endl;
        return (false);
    }

    outfile << content;

    return (true);
}