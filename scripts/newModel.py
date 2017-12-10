import sys

#print("hello")
#print("argument list:", str(sys.argv))

if len(sys.argv)<4:
	print("usage: newModel.py <ModelName> <rootLinkName> <STLFile>")
	exit()

newModel = open(sys.argv[1]+".body","w+")
newModel.writelines(["format: ChoreonoidBody\n",
			    "formatVersion: 1.0\n",
				"angleUnit: degree\n",
				"name: "+str(sys.argv[1])+"\n",
				"rootLink: "+str(sys.argv[2])+"\n",
				"links:\n",
				"  -\n",
				"    name: "+sys.argv[2]+"\n",
				"    jointType: free\n",
				"    translation: [ 0, 0, 0.1605 ]\n",
				"    rotation : [ 1, 0, 0, 0]\n",
			 	"    jointId: 0\n",
				"    centerOfMass: [ 0.014070775509439625, -0.0010642631392533723, 0.018082091556018958 ]\n",
				"    mass: 0.16852\n",
				"    inertia: [\n",
				"      7.5307790665527126e-05, -1.7122423225418951e-06, -7.9600885666462265e-06,\n",
				"      -1.7122423225418951e-06, 9.8462174358634891e-05, 1.6233365559722733e-06,\n",
				"      -7.9600885666462265e-06, 1.6233365559722733e-06, 0.00012629712705606254 ]\n",
				"    elements:\n",
				"      Shape:\n",
				"        geometry: { type: Resource, uri: \""+str(sys.argv[3])+"\" }"])
newModel.close()
