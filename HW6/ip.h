#ifndef IP_H
#define IP_H

#include "generic-field.h"

#define IP_SIZE 4

class Ip : public GenericField {
    static int ip_rule[IP_SIZE];
    static int ip_mask;

public:
    static bool dst_ip;

/**
* @brief checks if the given packet matches the ip rule.
* @param packet - the packet to check.
* @return true if the packet matches the ip rule, false otherwise.
*/
    bool match(String packet);

/**
 * @brief sets the ip rule.
 * @param value - the value to set the ip rule to.
 * @return true if the set went well, false otherwise.
 */
    bool set_value(String value);

/**
 * @brief destructor.
 */
    ~Ip(){};
};

#endif