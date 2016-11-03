#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
using namespace std;

class Executable {
    public:
        Executable(){};
        Executable(const string &s)
        {
            exec = s;
        };
        
        virtual bool run() {
            stringstream s2;
            s2.str(exec);
            
            vector<string> a;
            string cmd, tmp;
            s2 >> cmd;
            a.push_back(cmd);
            while (s2 >> tmp) {
            	a.push_back(tmp);
            }
            
            char ** argv = new char * [a.size() + 1];
            for (unsigned i = 0; i < a.size(); i++) {
            	argv[i] = (char *)(a[i].c_str());
            }
            argv[a.size()] = NULL;
            
            pid_t pid = fork();
            if (exec.find("exit") != string::npos) {
                exit(0);
            }
            else if (pid < 0) {
            	perror("error: fork failed");
            	return false;
            }
            else if (pid == 0) {
            	execvp(cmd.c_str(), argv);
            	perror(exec.c_str());
            	exit(0);
            	return false;
            }
            else {
            	if (waitpid(pid, 0, 0) < 0) {
            		perror("error: unable to wait");
            		return false;
            	}
            }
            return true;

        };
    
    protected:
        string exec;
};

#endif
