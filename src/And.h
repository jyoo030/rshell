#ifndef AND_H
#define AND_H

#include "Connector.h"

class And : public Connector
{
    public:
        And(){}
        bool evaluate(bool check){
            return check;
        }
        
};       

#endif