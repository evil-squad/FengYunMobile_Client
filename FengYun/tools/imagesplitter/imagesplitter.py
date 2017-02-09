from PIL import Image
import sys  
import os.path  
from  datetime  import  *    
import random  
import time

from optparse import OptionParser

def main():
	usage = "usage: %prog FILE [OPTION]..."
	parse = OptionParser(usage)
	parse.add_option("-o","--output",dest="output",help="output path to save target image",default=os.getcwd())
	parse.add_option("-s","--size",type="int",dest="blocksize",help="size for each block",default=256)
	parse.add_option("-v","--verbose",action="store_true",dest="verbose",help="print info to stdout",default=False)

	(options,args) = parse.parse_args()
	if len(args) < 1:
		parse.error("incorrect number of arguments!")
	
	filename = args[0]
	imageName = os.path.split(filename)[1]
	imageNameExt = os.path.splitext(imageName)

	outputPath = options.output
	cropSize = options.blocksize
	verbose = options.verbose

	outputPath = os.path.normpath(outputPath)
	if not os.path.exists(outputPath):
		os.mkdir(outputPath)
	
	xIndex = 0
	yIndex = 0
	xNum = 0
	yNum = 0
  
	im = Image.open(filename)
	pSize = im.size

	xNum = pSize[0]/cropSize
	yNum = pSize[1]/cropSize

	if verbose:
		print "size  " ,xNum,'  ',yNum

	for yIndex in range(yNum):
		for xIndex in range(xNum):
			if verbose:
				print "pic : " , xIndex , "_" , yIndex
			box = (xIndex*cropSize,yIndex*cropSize,(xIndex+1)*cropSize,(yIndex+1)*cropSize)  
			region = im.crop(box) 
			name = "%s%s%s_%s%s" % (outputPath + os.path.sep,imageNameExt[0],xIndex,yNum-1-yIndex,imageNameExt[1])
			if verbose:
				print name
			region.save(name)   
			# xIndex = xIndex+1
			# yIndex = yIndex+1
			if verbose:
				print int(time.time());

if __name__ == "__main__":
	main()
