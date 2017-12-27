import sys
if len(sys.argv)<6:
	print("usage: translation.py <ModelFile> <LinkName> <xTrans> <yTrans> <zTrans> ")
	exit()

x = float(sys.argv[3])
y = float(sys.argv[4])
z = float(sys.argv[5])

print( x, y, z)

def originalTrans(line):
    xyz = line.split('[')[1].split(',')
    x = float(xyz[0])
    y = float(xyz[1])
    z = float(xyz[2].split(']')[0])
    
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
    if linkFound and "translation :" in line and not updated:
        print(originalTrans(line))
        f.write("    translation : [ "+ str(x) + ", " + str(y) + ", " + str(z) + " ]\n")
        updated = True
    else:
        f.write(line)
if not updated:
    print("Translation not updated")
if not linkFound:
    print("Link not found")
f.close()
    
