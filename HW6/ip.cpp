#include "ip.h"

bool Ip::match(String packet) {
    
    packet.trim();
    char delim = ',';
    String **ip;
    size_t *size = new size_t;
    packet.split(&delim, ip, size);

    String relevant_ip;
    const char *target;

    if(Ip::dst_ip){
        target = "dst-ip";
    }
    else{
        target = "src-ip";
    }

    delim = '=';
    String **check;
    size_t *size_check = new size_t;

    for(int i = 0; i < (int)*size; i++){
        (*ip)[i].trim();
        (*ip)[i].split(&delim, check, size_check);
        (*check)[0].trim();
        (*check)[1].trim();
        if((*check)[0].equals(target)){
            relevant_ip = (*check)[1];
            break;
        }
    }

    delete size_check;
    delete[] check;
    delete[] ip;
    delete size;

    delim = '.';
    String **relevant_ip_split;
    size_t *size_relevant_ip = new size_t;
    relevant_ip.split(&delim, relevant_ip_split, size_relevant_ip);

    int mask = Ip::ip_mask;
    for(int i = 0; i < IP_SIZE; i++){
        if(mask > 0){
            if(ip_rule[i] != (*relevant_ip_split[i]).to_integer()){
                delete[] relevant_ip_split;
                delete size_relevant_ip;
                return false;
            }
            mask -= 8;
        }
    }

    delete[] relevant_ip_split;
    delete size_relevant_ip;
    return true;
}

bool Ip::set_value(String value) {
    char delim_ip = '.';
    char delim_mask = '/';
    String **ip;
    String **mask;
    size_t *size = new size_t; 

    value.split(&delim_ip, ip, size);
    if (*size != IP_SIZE) {
        delete[] ip;
        delete[] mask;
        delete size;
        return false;
    }

    (*ip)[3].split(&delim_mask, mask, NULL);

    for(int i = 0; i < IP_SIZE; i++) {
        if ((*ip)[i].to_integer() < 0 || (*ip)[i].to_integer() > 255) {
            delete[] ip;
            delete[] mask;
            delete size;
            return false;
        }
    }

    if((*mask)[1].to_integer() < 0 || (*mask)[1].to_integer() > 32) {
        delete[] ip;
        delete[] mask;
        delete size;
        return false;
    }
    
    for(int i = 0; i < IP_SIZE; i++) {
        ip_rule[i] = (*ip)[i].to_integer();
    }

    ip_mask = (*mask)[1].to_integer();

    delete[] ip;
    delete[] mask;
    delete size;

    return true;
}