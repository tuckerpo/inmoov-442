import sys

if len(sys.argv)<5:
	print("usage: newLink.py <ModelFile> <NewLinkName> <ParentLinkName> <STLFile>")
	exit()

Model = open(sys.argv[1],"a+")
Model.writelines(["""\n  -
    name: """, sys.argv[2]+"\n",
"    parent: "+sys.argv[3]+"\n",
"""    translation : [ 0.009, 0, -0.047 ]
    rotation : [ 1, 0, 0, 90]
    jointId: 1
    jointType: revolute
    jointAxis: -Y
    jointRange: [ -0.873, 2.269 ]
    centerOfMass: [ 0.0015461746197516959, -0.00033796007273481838, -0.015625257207349728 ]
    mass: 0.02905
    inertia: [
      1.0789525167996373e-05, -3.9905699607782306e-09, 1.7978343823012256e-06,
      -3.9905699607782306e-09, 1.1003152501217637e-05, 4.0040500729103886e-08,
      1.7978343823012256e-06, 4.0040500729103886e-08, 3.259107193487409e-06 ]
    elements:
      Shape:""",
"\n        geometry: { type: Resource, uri: \""+sys.argv[4]+"\" }"])
Model.close()
