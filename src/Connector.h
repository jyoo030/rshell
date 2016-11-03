#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>
using namespace std;

class Connector
{
    public:
        Connector() {};
        virtual bool evaluate(bool) = 0;
        virtual ~Connector() {};
};

#endif