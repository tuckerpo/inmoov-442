import sys
import math
if len(sys.argv)<6:
	print("usage: rotation.py <ModelFile> <LinkName> <xRot> <yRot> <zRot> ")
	exit()

c1 = math.cos(float(sys.argv[3])*3.14/360.0)
s1 = math.sin(float(sys.argv[3])*3.14/360.0)
c2 = math.cos(float(sys.argv[4])*3.14/360.0)
s2 = math.sin(float(sys.argv[4])*3.14/360.0)
c3 = math.cos(float(sys.argv[5])*3.14/360.0)
s3 = math.sin(float(sys.argv[5])*3.14/360.0)

w = c1*c2*c3 - s1*s2*s3
z = c1*c2*s3 + s1*s2*c3
x = s1*c2*c3 + c1*s2*s3
y = c1*s2*c3 - s1*c2*s3

angle = 2.0 * math.acos(w)
norm = x*x+y*y+z*z

if (norm < 0.001):  # when all euler angles are zero angle =0 so
	# we can set axis to anything to avoid divide by zero
	x=1
	y=z=0
else:
	norm = math.sqrt(norm)
	x /= norm
	y /= norm
	z /= norm

print (x,y,z, angle/3.14*180.0);
