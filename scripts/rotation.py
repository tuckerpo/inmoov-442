import sys
import math
if len(sys.argv)<6:
	print("usage: rotation.py <ModelFile> <LinkName> <xRot> <yRot> <zRot> ")
	exit()

c1 = math.cos(float(sys.argv[3])*3.14159/360.0)
s1 = math.sin(float(sys.argv[3])*3.14159/360.0)
c2 = math.cos(float(sys.argv[4])*3.14159/360.0)
s2 = math.sin(float(sys.argv[4])*3.14159/360.0)
c3 = math.cos(float(sys.argv[5])*3.14159/360.0)
s3 = math.sin(float(sys.argv[5])*3.14159/360.0)

w = c1*c2*c3 - s1*s2*s3
z = c1*c2*s3 + s1*s2*c3
x = s1*c2*c3 + c1*s2*s3
y = c1*s2*c3 - s1*c2*s3

angle = 2.0 * math.acos(w)
norm = x*x+y*y+z*z

if (norm < 0.000000001):  # when all euler angles are zero angle =0 so
	# we can set axis to anything to avoid divide by zero
	x=1
	y=z=0
else:
	norm = math.sqrt(norm)
	x /= norm
	y /= norm
	z /= norm

print (x,y,z, angle/3.14159*180.0, "\n")

def originalAngles(line):
    #print(line)
    rxyz = line.split('[')[1].split(',')
    x = float(rxyz[0])
    y = float(rxyz[1])
    z = float(rxyz[2])
    angle = float(rxyz[3].split(']')[0])*3.14159/180.0
    
    s=math.sin(angle);
    c=math.cos(angle);
    t=1-c;
	
    #print (x,y,z, angle, "\n")

    if x*y*t + z*s > 0.998: # north pole singularity detected
        xRot = 2.0*math.atan2(x*math.sin(angle/2.0),math.cos(angle/2.))
        yRot = 3.14159/2.0
        zRot = 0
        print( "Original Angles : ", xRot/3.14159*180.0, yRot/3.14159*180.0, zRot/3.14159*180.0)
        return
		
    if x*y*t + z*s < -0.998: # south pole singularity detected
        xRot = -2.0*math.atan2(x*math.sin(angle/2.0),math.cos(angle/2.0))
        yRot = -3.14159/2.0
        zRot = 0
        print( "Original Angles : ", xRot/3.14159*180.0, yRot/3.14159*180.0, zRot/3.14159*180.0)
        return
	
    zRot = math.atan2(y * s- x * z * t , x * y * t + z * s)
    xRot = math.atan2(x * s - y * z * t, 1-(y*y+x*x)*t)
    yRot = -math.asin(-(x*z*t)-y*s)  # 1 - (x*x + z*z) * t  
    #zRot = math.atan2(x*y*t + z*s , 1 - (y*y+ z*z ) * t)
    print( "Original Angles : ", xRot/3.14159*180.0, yRot/3.14159*180.0, zRot/3.14159*180.0)
    
f = open(sys.argv[1], "r")
lines = f.readlines()
f.close()
f = open(sys.argv[1], "w")
updated = False
linkFound = False
for line in lines:
    if "name:" in line and sys.argv[2] in line:
        linkFound = True
    if linkFound and "rotation :" in line and not updated:
        print(originalAngles(line))
        f.write("    rotation : [ "+ str(x) + ", " + str(y) + ", " + str(z) + ", " + str(angle/3.14159*180.0) + " ]\n")
        updated = True
    else:
        f.write(line)
if not updated:
    print("Rotation not updated")
if not linkFound:
    print("Link not found")
f.close()
    
