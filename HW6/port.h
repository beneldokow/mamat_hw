#ifndef PORT_H
#define PORT_H

#include "generic-field.h"

#define PORT_SIZE 2

class Port : public GenericField {
    static int max_port_rule;
    static int min_port_rule;

public:
    static bool dst_port;
    bool match(String packet);
    bool set_value(String value);
    ~Port(){};
};

#endif