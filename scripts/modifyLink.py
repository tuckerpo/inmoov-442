import sys

if len(sys.argv)<5:
	print("usage: modifyLink.py <ModelFile> <LinkName> <PropertyName> <AdditionalArguments>")
	exit()

Model = open(sys.argv[1],"r+")
#https://stackoverflow.com/questions/11469228/python-replace-and-overwrite-instead-of-appending
