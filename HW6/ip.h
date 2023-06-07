#ifndef IP_H
#define IP_H

#include "generic-field.h"

#define IP_SIZE 4

class Ip : public GenericField {
    static int ip_rule[IP_SIZE];
    static int ip_mask;

public:
    static bool dst_ip;
    bool match(String packet);
    bool set_value(String value);
    ~Ip(){};
};

#endif