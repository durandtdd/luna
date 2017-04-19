
def read_opcodes(path_rsc):
    """ Read opcode from resource file """
    with open(path_rsc + "opcodes.txt", "r") as file:
        text = file.read()
        text = text.replace(".u8", "DUMMY")
        text = text.replace("u8", "UINT8")
        text = text.replace("i8", "INT8")
        text = text.replace("u16", "UINT16")
        text = text.replace("i16", "INT16")
        text = text.replace("u32", "UINT32")
        text = text.replace("i32", "INT32")
        text = text.replace("var", "VAR")
        lines = list(filter(None, text.split("\n")))
        
        opcodes = [None]*256
        for line in lines:
            l = line.split()
            n = int(l[0][2:], 16)
            if l[1] != "_uns":
                opcodes[n] = (l[1], l[2:])
            else:
                opcodes[n] = ("invalid", [])
       
    return opcodes


def generate_warning():
    """ Create warning fot auto-generated files """
    return "/* Auto-generated file, DO NOT MODIFY */\n\n"


def generate_enum(opcodes):
    """ Create enum from opcodes """
    enum = [opcode[0] for opcode in opcodes if opcode[0]!="invalid"]
    enum.append("invalid")
    
    s = "    "
    for k, e in enumerate(enum):
        s += e.upper() + ", "
        if k%8 == 7:
            s += "\n    "
    s += "\n"
    
    return s


def generate_enum_strings(opcodes):
    """ Create enum strings from opcodes """
    enum = [opcode[0] for opcode in opcodes if opcode[0]!="invalid"]
    enum.append("invalid")
    
    s = "    "
    for k, e in enumerate(enum):
        s += "\"" + e + "\", "
        if k%8 == 7:
            s += "\n    "
    s += "\n"
    
    return s


def generate_table(opcodes):
    """ Create table from opcodes """
    s = ""
    for opcode in opcodes:
        s += "    {{{}, {{{}}}}},\n".format(opcode[0].upper(), ",".join(["Operand::" + op for op in opcode[1]]))
    return s
    

def write_mnemonic_enum(path_src, opcodes):
    """ Write mnemonic.cpp and mnemonic.hpp """
    s = generate_warning()
    s += "#pragma once\n\n"
    s += "#include <string>\n\n\n"
    s += "enum Mnemonic\n"
    s += "{\n"
    s += generate_enum(opcodes) + "\n"
    s += "};\n\n"
    s += "std::string mnemonicStr(Mnemonic mnemonic);\n"
    
    with open(path_src + "mnemonic.hpp", 'w') as file:
        file.write(s)
        

    s = generate_warning()
    s += "#include \"mnemonic.hpp\"\n\n\n"
    s += "std::string mnemonicStr(Mnemonic mnemonic)\n"
    s += "{\n"
    s += "    static std::string names[] = {\n"
    s += generate_enum_strings(opcodes);
    s += "    };\n\n"
    s += "    return names[(int)mnemonic];\n" 
    s += "}\n"
    
    with open(path_src + "mnemonic.cpp", 'w') as file:
        file.write(s)
    

def write_opcode_table(path_src, opcodes):
    """ Write opcode.hpp """
    s = generate_warning()
    s += "#include \"opcode.hpp\"\n\n\n"
    s += "Opcode Opcode::table[256] = {\n"
    s += generate_table(opcodes) + "\n"
    s += "};\n\n"
    s += "std::string mnemonicStr(Mnemonic mnemonic);\n"
    
    with open(path_src + "opcode.cpp", 'w') as file:
        file.write(s)
        
        
        
if __name__=='__main__':
    """ Main """
    path_rsc = "./"
    path_src = "../src/decoder/"
    
    opcodes = read_opcodes(path_rsc)
    
    write_mnemonic_enum(path_src, opcodes)
    write_opcode_table(path_src, opcodes)