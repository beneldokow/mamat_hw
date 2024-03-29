#include "port.h"

//default values
bool Port::dst_port = false;
int Port::min_port_rule = 0;
int Port::max_port_rule = 0;

bool Port::match(String packet) {
    if(packet.equals("")){
        return false;
    }
    packet = packet.trim(); //remove spaces from the start/end of the string
    const char *delim = ",";
    String **port = new String*;
    size_t *size = new size_t;

    packet.split(delim, port, size); //split the packet to the different fields
    if (*size == 0) {
        delete[] *port;
        delete port;
        delete size;
        return false;
    }

    String relevant_port;
    const char *target;

    if(Port::dst_port){ //assign the relevant port
        target = "dst-port";
    }
    else{
        target = "src-port";
    }

    const char *eq_delim = "=";
    String **check = new String*;
    size_t *size_check = new size_t;

    for(int i = 0; i < (int)*size; i++){ //find the relevant port
        (*port)[i] = (*port)[i].trim();
        if((*port)[i].equals("")){
            break;
        }
        (*port)[i].split(eq_delim, check, size_check);
        (*check)[0] = (*check)[0].trim();
        (*check)[1] = (*check)[1].trim();
        if((*check)[0].equals(target)){
            relevant_port = (*check)[1];
            break;
        }
        delete[] *check;
    }

    delete size_check;
    delete[] *check;
    delete check;
    delete[] *port;
    delete port;
    delete size;

    //check if the port is in the range and return the result
    if(relevant_port.to_integer() < min_port_rule || 
    relevant_port.to_integer() > max_port_rule){
        return false;
    }

    return true;
}

bool Port::set_value(String value) {
    const char *delim = "-";
    String **port = new String*;
    size_t *size = new size_t; 

    //split the value to the min and max port
    value.split(delim, port, size);
    if (*size != 2) {
        delete[] *port;
        delete port;
        delete size;
        return false;
    }

    //check if the port rules are valid
    if((*port)[0].to_integer() < 0 || (*port)[0].to_integer() > 65535 ||
       (*port)[1].to_integer() < 0 || (*port)[1].to_integer() > 65535 ||
       (*port)[0].to_integer() > (*port)[1].to_integer()) {
        delete[] *port;
        delete port;
        delete size;
        return false;
    }

    //assign the port rules
    min_port_rule = (*port)[0].to_integer();
    max_port_rule = (*port)[1].to_integer();

    delete[] *port;
    delete port;
    delete size;
    return true;
}