#include <stdio.h>
#include <dirent.h>
#include <cstdlib>
#include <string.h>
#include <iostream>

using namespace std;

string sconvert(const char *pCh, int arraySize){
	std::string str;
	for(int i=0; i<arraySize; i++){
		if (pCh[i] == ' '){
			str.append("\\\\\\ ");//convert space char to linux system representation
		}
		else{
			str.append(1,pCh[i]);
		}
	}
	return str;
}

int main (int c, char *v[]) {
    int len;
    struct dirent *pDirent;
    DIR *pDir;

    if (c < 2) {
        printf ("Usage: readDir <dirname>\n");
        return 1;
    }
    pDir = opendir (v[1]);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", v[1]);
        return 1;
    }

    while ((pDirent = readdir(pDir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
		//string d_name = sconvert(pDirent->d_name, strlen(pDirent->d_name));
		string d_name;
		d_name.append(pDirent->d_name);
		if (d_name.find(".") != std::string::npos){
			if (d_name.find(".stl") != std::string::npos){
				string arg = "./STLtoDim \"";
				system(arg.append(v[1]).append(pDirent->d_name).append("\"").c_str());
			}
		}
		else {
			string arg = "./readDir \"";
			system(arg.append(v[1]).append(pDirent->d_name).append("/\"").c_str());		
		}
    }
    closedir (pDir);
    return 0;
}