#include "ip.h"

bool Ip::dst_ip = false;
int Ip::ip_mask = 0;
int Ip::ip_rule[IP_SIZE] = {0};

bool Ip::match(String packet) {

    // if the packet is empty, return false
    if(packet.equals("")){
        return false;
    }

    // split the packet to different fields
    packet = packet.trim();
    const char *delim = ",";
    String **ip = new String*;
    size_t *size = new size_t;
    packet.split(delim, ip, size);
    if (*size == 0) {
        return false;
    }

    String *relevant_ip = new String;
    const char *target;

    // assign the relevant ip
    if(Ip::dst_ip){
        target = "dst-ip";
    }
    else{
        target = "src-ip";
    }

    const char *eq_delim = "=";
    String **check = new String*;
    size_t *size_check = new size_t;

    //get the relevant ip field
    for(int i = 0; i < (int)*size; i++){
        (*ip)[i] = (*ip)[i].trim();
        (*ip)[i].split(eq_delim, check, size_check);
        (*check)[0] = (*check)[0].trim();
        (*check)[1] = (*check)[1].trim();
        if((*check)[0].equals(target)){
            *relevant_ip = (*check)[1];
        }
        delete[] *check;
    }

    delete size_check;
    delete check;
    delete[] *ip;
    delete ip;
    delete size;

    const char *pt_delim = ".";
    String **relevant_ip_split = new String*;
    size_t *size_relevant_ip = new size_t;
  
    // split the relevant ip to its fields
    (*relevant_ip).split(pt_delim, relevant_ip_split, size_relevant_ip);

    int mask = Ip::ip_mask;

    // check if the ip fields are corresponding to the rule
    for(int i = 0; i < IP_SIZE; i++){
        if(mask > 0){
            if(ip_rule[i] != ((*relevant_ip_split)[i]).to_integer()){
                delete[] *relevant_ip_split;
                delete relevant_ip;
                delete relevant_ip_split;
                delete size_relevant_ip;
                return false;
            }
            mask -= 8;
        }
    }

    delete relevant_ip;
    delete[] *relevant_ip_split;
    delete relevant_ip_split;
    delete size_relevant_ip;
    return true;
}

bool Ip::set_value(String value) {
    const char *delim_ip = ".";
    const char *delim_mask = "/";
    String **ip = new String*;
    String **mask = new String*;
    size_t *size = new size_t; 

    //split the ip to the different fields
    value.split(delim_ip, ip, size);
    if(*size == 0){
        return false;
    }

    //split the mask from the last field
    (*ip)[3].split(delim_mask, mask, size);
    (*ip)[3] = (*mask)[0];

    //check if the ip fields are valid
    for(int i = 0; i < IP_SIZE; i++) {
        if ((*ip)[i].to_integer() < 0 || (*ip)[i].to_integer() > 255) {
            delete[] *ip;
            delete ip;
            delete[] *mask;
            delete mask;
            delete size;
            return false;
        }
    }

    //check if the mask is valid
    if((*mask)[1].to_integer() < 0 || (*mask)[1].to_integer() > 32) {
        delete[] *ip;
        delete ip;
        delete[] *mask;
        delete mask;
        delete size;
        return false;
    }
    
    //set the ip rule and mask
    for(int i = 0; i < IP_SIZE; i++) {
        ip_rule[i] = (*ip)[i].to_integer();
    }

    ip_mask = (*mask)[1].to_integer();

    delete[] *ip;
    delete ip;
    delete[] *mask;
    delete mask;
    delete size;

    return true;
}