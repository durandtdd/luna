#include <iostream>
#include <string>

#include "java-class-file.hpp"


struct Options
{
    bool name = false;
    bool base = false;
    bool interfaces = false;
    bool fields = false;
    bool methods = false;

    bool help = false;
    std::string str;
    std::string error;

    void parse(int argc, char** argv);
};


void Options::parse(int argc, char **argv)
{
    for(int k=1; k<argc; k++)
    {
        std::string arg(argv[k]);

        if(arg == "--help")
        {
            help = true;
        }
        else if(arg == "--name")
        {
            name = true;
        }
        else if(arg == "--super")
        {
            base = true;
        }
        else if(arg == "--interfaces")
        {
            interfaces = true;
        }
        else if(arg == "--fields")
        {
            fields = true;
        }
        else if(arg == "--methods")
        {
            methods = true;
        }
        else if(arg == "--info")
        {
            name = true;
            base = true;
            interfaces = true;
            fields = true;
            methods = true;
        }
        else
        {
            if(arg[0] == '-' || str != "")
            {
                error = "Unknown option: " + arg;
                return;
            }
            else
            {
                str = arg;
            }
        }
    }
}


std::string help()
{
    return "";
}


void printName(const Class& cl)
{
    std::cout << "Name:\n";
    std::cout << "    " << cl.name << "\n";
    std::cout << "\n";
}


void printBase(const Class& cl)
{
    std::cout << "Super:\n";
    std::cout << "    " << cl.base << "\n";
    std::cout << "\n";
}


void printInterfaces(const Class& cl)
{
    std::cout << "Interfaces:\n";
    for(const std::string& interface: cl.interfaces)
        std::cout << "    " << interface << "\n";
    std::cout << "\n";
}


void printFields(const Class& cl)
{
    std::cout << "Fields:\n";
    for(const Field& field: cl.fields)
        std::cout << "    " << field.str() << "\n";
    std::cout << "\n";
}


void printMethods(const Class& cl)
{
    std::cout << "Methods:\n";
    for(const Method& method: cl.methods)
        std::cout << "    " << method.str() << "\n";
    std::cout << "\n";
}


int main(int argc, char** argv)
{
    Options opt;
    opt.parse(argc, argv);

    if(opt.error != "")
    {
        std::cout << opt.error << std::endl;
        std::cout << help() << std::endl;
    }
    else if(opt.help)
    {
        std::cout << help() << std::endl;
    }
    else
    {
        try
        {
            JavaClassFile file(opt.str);
            Class cl = file.javaClass();

            if(opt.name)
                printName(cl);

            if(opt.base)
                printBase(cl);

            if(opt.interfaces)
                printInterfaces(cl);

            if(opt.fields)
                printFields(cl);

            if(opt.methods)
                printMethods(cl);
        }
        catch(const Error& error)
        {
            std::cerr << error.what() << std::endl;
        }
    }

    return 0;
}

