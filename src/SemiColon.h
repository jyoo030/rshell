#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Connector.h"

class SemiColon : public Connector
{
    public:
        SemiColon() {}
        bool evaluate(bool check){
            return true;
        }
};       
#endif