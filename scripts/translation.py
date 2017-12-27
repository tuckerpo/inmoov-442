import sys
import math
if len(sys.argv)<6:
	print("usage: translation.py <ModelFile> <LinkName> <xTrans> <yTrans> <zTrans> ")
	exit()

def originalTrans(line):
    xyz = line.split('[')[1].split(',')
    x = float(rxyz[0])
    y = float(rxyz[1])
    z = float(rxyz[2].split(']')[0])
    
    print( "Original Translation : ", x, y, z)
    
f = open(sys.argv[1], "r")
lines = f.readlines()
f.close()
f = open(sys.argv[1], "w")
updated = False
linkFound = False
for line in lines:
    if "name:" in line and sys.argv[2] in line:
        linkFound = True
    if linkFound and "translation" in line and not updated:
        print(originalAngles(line))
        f.write("    translation : [ "+ str(x) + ", " + str(y) + ", " + str(z) + " ]\n")
        updated = True
    else:
        f.write(line)
if not updated:
    print("Translation not updated")
if not linkFound:
    print("Link not found")
f.close()
    
