#include <iostream>
#include <string>

#include "command-line-interface.hpp"


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
    if(argc <= 2)
    {
        help = true;
        return;
    }

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
        else if(arg == "--all")
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
    return "Java class files analysis tool\n"
            "usage: luna [options] filename\n"
            "\n"
            "Options\n"
            "    --name        Show class name\n"
            "    --super       Show super class name\n"
            "    --interfaces  Show interfaces\n"
            "    --fields      Show fields\n"
            "    --methods     Show methods\n"
            "    --all         Show names, interfaces, fields, methods\n"
            "\n";
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
            CommandLineInterface cli(opt.str);

            if(opt.name)
                cli.printName();

            if(opt.base)
                cli.printSuper();

            if(opt.interfaces)
                cli.printInterfaces();

            if(opt.fields)
                cli.printFields();

            if(opt.methods)
                cli.printMethods();
        }
        catch(const Error& error)
        {
            std::cerr << error.what() << std::endl;
        }
    }

    return 0;
}

