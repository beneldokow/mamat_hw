#ifndef PORT_H
#define PORT_H

#include "generic-field.h"

#define PORT_SIZE 2

class Port : public GenericField {
    static int max_port_rule;
    static int min_port_rule;

public:
    static bool dst_port; // true if dst-port, false if src-port

/**
 * @brief checks if the given packet matches the port rule.
 * @param packet - the packet to check.
 * @return true if the packet matches the port rule, false otherwise.
 */
    bool match(String packet);

/**
 * @brief sets the port rule.
 * @param value - the value to set the port rule to.
 * @return true if the set went well, false otherwise.
 */
    bool set_value(String value);
/**
 * @brief destructor.
 */
    ~Port(){};
};

#endif