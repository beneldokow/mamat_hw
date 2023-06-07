#include "ip.h"
#include "port.h"

extern int check_args(int argc, char const **argv);
extern void parse_input(GenericField &field);

int main(int argc, char const **argv){
    
    if(check_args(argc, argv)){
        return 1;
    }

    const char *src_ip = "src-ip";
    const char *dst_ip = "dst-ip";
    const char *src_port = "src-port";
    const char *dst_port = "dst-port";

    String entry_rule = argv[1];
    entry_rule.trim();

    String **rule = new String*[2];
    size_t *size = new size_t;
    const char *delim = " =";

    entry_rule.split(delim, rule, size);
    rule[0]->trim();
    rule[1]->trim();

    if(rule[0]->equals(src_ip)){
        Ip::dst_ip = false;
        Ip ip;
        ip.set_value(*rule[1]);
        parse_input(ip);
    }
    else if(rule[0]->equals(dst_ip)){
        Ip::dst_ip = true;
        Ip ip;
        ip.set_value(*rule[1]);
        parse_input(ip);
    }
    else if(rule[0]->equals(src_port)){
        Port::dst_port = false;
        Port port;
        port.set_value(*rule[1]);
        parse_input(port);
    }
    else if(rule[0]->equals(dst_port)){
        Port::dst_port = true;
        Port port;
        port.set_value(*rule[1]);
        parse_input(port);
    }

    delete[] rule;
    delete size;

    return 0;
}