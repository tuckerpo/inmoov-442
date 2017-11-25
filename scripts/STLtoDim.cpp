// reading an entire binary file
#include <iostream>
#include <fstream>
#include <limits>
#include <stdint.h>

using namespace std;

int main (int c, char *v[]) {

	if (c < 2) {
        printf ("Usage: STLtoDim <STLFile>\n");
        return 1;
    }   

	ifstream ifs (v[1], ios::in | ios::binary);
	if (!ifs.is_open()){
		cout << "Unable to open " << v[1] << "\n";
		return 0;
	}

	unsigned int numFaces = 0;
	uint8_t buf[84];
	ifs.read((char*)buf, 84);
	if(ifs.gcount() == 84){
		numFaces = buf[80] + (buf[81] << 8) + (buf[82] << 16) + (buf[83] << 24);
	}
	else{
		cout << "the gcount is supposed to be 84 but it is " << ifs.gcount() << "\n";
		return 0;
	}

	
	float minX, minY, minZ = std::numeric_limits<float>::max();
	float maxX, maxY, maxZ = -minX;
	for(size_t i = 0; i < numFaces; i++){
	    for(size_t j = 0; j < 3; j++){//skip the normal vector
	        float v;
	        ifs.read((char *)&v, 4);
	    }
	    for(size_t k = 0; k < 3; k++){
	        for(size_t j = 0; j < 3; j++){
	            float v;
	            ifs.read((char *)&v, 4);
	            if (j==0 && v>maxX){maxX = v;}
				if (j==0 && v<minX){minX = v;}
	            if (j==1 && v>maxY){maxY = v;}
				if (j==1 && v<minY){minY = v;}
	            if (j==2 && v>maxZ){maxZ = v;}
				if (j==2 && v<minZ){minZ = v;}
	        }
	    }
	    uint16_t attrib;
	    ifs.read((char *)&attrib, 2);
	}
	ofstream dims;
    dims.open ("dims.csv", std::ios_base::app);
	dims << v[1] << "," << maxX-minX << "," << maxY-minY << "," << maxZ-minZ << "\n"; 
	dims.close();
	return 0;
}
