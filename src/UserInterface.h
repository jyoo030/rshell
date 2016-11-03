#fndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string>
#include <queue>
#include "Executable.h"
#include "Or.h"
#include "And.h"
#include "Connector.h"
#include "SemiColon.h"
#include <unistd.h>
#include <cstdlib>

using namespace std;

class UserInterface
{
    public:
        UserInterface()
        {
            
        };
        
        void run()
        {
            string userInput;
            queue<Connector *> cons;
            queue<Executable *> exes;
            while(true) {
                cout << "$ ";
                getline(cin, userInput);
                parse(userInput, cons, exes);
                bool lastrun = true;
                while (!exes.empty()) {
                    Executable * top = exes.front();
                    if (cons.size() == exes.size()) {
                        Connector * con = cons.front();
                        cons.pop();
                        lastrun = con->evaluate(lastrun);
                        delete con;
                    }
                    if (lastrun) {
                        lastrun = top->run();
                    }
                    exes.pop();
                    delete top;
                }
            }
        };
        
    private:
        void parse(const string &input, queue<Connector *> &cons, queue<Executable *> &exes) {
            int begin = 0;
            int end = 0;
            string holder;
            for(unsigned i = 0; i < input.size(); i++) {
		if (input[i] == '#')
		{
		    if(i != 0)
		    {
		    	end = i;
		    	exes.push(new Executable(input.substr(begin, end - begin)));
		    	i = input.size();
		    }		
		}
                if (input[i] == ';') {
                    end = i;
                    exes.push(new Executable(input.substr(begin, end - begin)));
                    if(i+1 != input.size())
                    {
                        cons.push(new SemiColon());
                    }
                    begin = i+1;
                    i++;
                }
                else if (input[i] == '&' && i+1 != input.size() && input[i+1] == '&') {
                    end = i;
                    exes.push(new Executable(input.substr(begin, end - begin)));
                    if(i+2 != input.size())
                    {
                        cons.push(new And());
                    }
                    begin = i+2;
                    i+=2;
                }
                else if (input[i] == '|' && i+1 != input.size() && input[i+1] == '|') {
                    end = i;
                    exes.push(new Executable(input.substr(begin, end - begin)));
                    if(i+2 != input.size())
                    {
                        cons.push(new Or());
                    }
                    begin = i+2;
                    i+=2;
                }
                else if (i == input.size()-1) {
                    end = i;
                    exes.push(new Executable(input.substr(begin, end + 1 - begin)));
                }
            }
        };
        
};

#endif
