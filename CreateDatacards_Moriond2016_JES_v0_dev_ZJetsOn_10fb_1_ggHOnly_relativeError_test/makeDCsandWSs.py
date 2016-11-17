#!/usr/bin/python
#-----------------------------------------------
# Latest update: 2012.08.30
# by Matt Snowball
#-----------------------------------------------
import sys, os, pwd, commands
import optparse, shlex, re
import math
from ROOT import *
import ROOT
from array import array
from datacardClass import *
from inputReader import *

#define function for parsing options
def parseOptions():

    usage = ('usage: %prog [options] datasetList\n'
             + '%prog -h for help')
    parser = optparse.OptionParser(usage)
    
    parser.add_option('-i', '--input', dest='inputDir', type='string', default="",    help='inputs directory')
    parser.add_option('-d', '--is2D',   dest='is2D',       type='int',    default=1,     help='is2D (default:1)')
    parser.add_option('-a', '--append', dest='appendName', type='string', default="",    help='append name for cards dir')
    parser.add_option('-b', action='store_true', dest='noX', default=True ,help='no X11 windows')
    parser.add_option('-t', '--templateDir', type='string', dest='templateDir', default="templates2D" ,help='directory with 2D template histos')
    parser.add_option('-e', '--massError',   dest='massError',       type='int',    default=0,     help='massError (default:0)')
    parser.add_option('-j', '--jet', dest='useJET', type='int', default=0, help='useJET (default:0)')

    parser.add_option('-r', '--refit', dest='useREFIT', type='int', default=0, help='useREFIT (default:0)')
    
    # store options and arguments as global variables
    global opt, args
    (opt, args) = parser.parse_args()

    if (opt.is2D != 0 and opt.is2D != 1):
        print 'The input '+opt.is2D+' is unkown for is2D.  Please choose 0 or 1. Exiting...'
        sys.exit()

    if (opt.appendName == ''):
        print 'Please pass an append name for the cards directory! Exiting...'
        sys.exit()

    if (opt.inputDir == ''):
        print 'Please pass an input directory! Exiting...'
        sys.exit()

# define make directory function
def makeDirectory(subDirName):
    if (not os.path.exists(subDirName)):
        cmd = 'mkdir -p '+subDirName
        status, output = commands.getstatusoutput(cmd)
        if status !=0:
            print 'Error in creating submission dir '+subDirName+'. Exiting...'
            sys.exit()
    else:
        print 'Directory '+subDirName+' already exists. Exiting...'
        sys.exit()


#define function for processing of os command
def processCmd(cmd):
#    print cmd
    status, output = commands.getstatusoutput(cmd)
    if status !=0:
        print 'Error in processing command:\n   ['+cmd+'] \nExiting...'
        sys.exit()



def creationLoop(directory):
    global opt, args
    
#    startMass=[ 380.0, 400.0, 600.0 ]
#    stepSizes=[ 10.0,   20.0, 50.0 ]
#    endVal=[ 1, 10, 9 ]

#    startMass=[ 200.0, 290.0, 350.0, 400.0, 600.0 ]
#    stepSizes=[  2.0,   5.0,   10.0,  20.0,  50.0 ]
#    endVal   =[   45,    12,    4,     10,    9   ]

    startMass=[ 125.0]
    stepSizes=[ 0.1]
    endVal=[     1]

#    startMass=  [ 110.0, 124.5, 126.5, 130.0]
#    stepSizes=  [  0.5,   0.1,   0.5,   1.0]
#    endVal=     [  29,     20,    7,     30]

#    startMass=[ 127.0, 130.0, 160.0]
#    stepSizes=[ 0.5,    1.0,   2.0]
#    endVal=[     6,      30,    21]


    myClass = datacardClass()
    myClass.loadIncludes()

    if(opt.useREFIT) :
       opt.templateDir = 'templates2D_refit'

    if (opt.useJET == 0):
        myReader4e = inputReader(opt.inputDir+"/inputs_4e.txt")
        myReader4e.readInputs()
        theInputs4e = myReader4e.getInputs()
        
        myReader4mu = inputReader(opt.inputDir+"/inputs_4mu.txt")
        myReader4mu.readInputs()
        theInputs4mu = myReader4mu.getInputs()
        
        myReader2e2mu = inputReader(opt.inputDir+"/inputs_2e2mu.txt")
        myReader2e2mu.readInputs()
        theInputs2e2mu = myReader2e2mu.getInputs()

    if (opt.useJET == 1):
        myReader4e_0 = inputReader(opt.inputDir+"_tagged/inputs_4e_0.txt")
        myReader4e_0.readInputs()
        theInputs4e_0 = myReader4e_0.getInputs()
        
        myReader4mu_0 = inputReader(opt.inputDir+"_tagged/inputs_4mu_0.txt")
        myReader4mu_0.readInputs()
        theInputs4mu_0 = myReader4mu_0.getInputs()
        
        myReader2e2mu_0 = inputReader(opt.inputDir+"_tagged/inputs_2e2mu_0.txt")
        myReader2e2mu_0.readInputs()
        theInputs2e2mu_0 = myReader2e2mu_0.getInputs()

        myReader4e_1 = inputReader(opt.inputDir+"_tagged/inputs_4e_1.txt")
        myReader4e_1.readInputs()
        theInputs4e_1 = myReader4e_1.getInputs()
        
        myReader4mu_1 = inputReader(opt.inputDir+"_tagged/inputs_4mu_1.txt")
        myReader4mu_1.readInputs()
        theInputs4mu_1 = myReader4mu_1.getInputs()
        
        myReader2e2mu_1 = inputReader(opt.inputDir+"_tagged/inputs_2e2mu_1.txt")
        myReader2e2mu_1.readInputs()
        theInputs2e2mu_1 = myReader2e2mu_1.getInputs() 

    
    a=0
    while (a < len(startMass) ):
	
	c = 0
        while (c < endVal[a] ): 
            
            mStart = startMass[a]
            step = stepSizes[a]
            mh = mStart + ( step * c ) 
            mhs = str(mh).replace('.0','')

            print mh
            if (opt.useJET == 0):

                print 'useJET == 0'
                makeDirectory(directory+'/HCG/'+mhs)
                makeDirectory(directory+'/HCG_XSxBR/'+mhs)

                myClass.makeCardsWorkspaces(mh,opt.is2D,directory,theInputs4e,opt.templateDir, opt.massError,0,0,opt.useREFIT)
                myClass.makeCardsWorkspaces(mh,opt.is2D,directory,theInputs4mu,opt.templateDir,opt.massError,0,0,opt.useREFIT)

                myClass.makeCardsWorkspaces(mh,opt.is2D,directory,theInputs2e2mu,opt.templateDir,opt.massError,0,0,opt.useREFIT)

            if (opt.useJET == 1):

                print 'useJET == 1'
                makeDirectory(directory+'_tagged/HCG/'+mhs)
                makeDirectory(directory+'_tagged/HCG_XSxBR/'+mhs)
                print '4e 0'
                myClass.makeCardsWorkspaces(mh,opt.is2D,directory+'_tagged',theInputs4e_0,opt.templateDir,opt.massError,1,0,opt.useREFIT)
                print '4mu 0'
                myClass.makeCardsWorkspaces(mh,opt.is2D,directory+'_tagged',theInputs4mu_0,opt.templateDir,opt.massError,1,0,opt.useREFIT)
                print '2e2mu 0'
                myClass.makeCardsWorkspaces(mh,opt.is2D,directory+'_tagged',theInputs2e2mu_0,opt.templateDir,opt.massError,1,0,opt.useREFIT)
                print '4e 1'
                myClass.makeCardsWorkspaces(mh,opt.is2D,directory+'_tagged',theInputs4e_1,opt.templateDir, opt.massError, 1,1,opt.useREFIT)
                print '4mu 1'
                myClass.makeCardsWorkspaces(mh,opt.is2D,directory+'_tagged',theInputs4mu_1,opt.templateDir,opt.massError, 1,1,opt.useREFIT)
                print '2e2mu 1'
                myClass.makeCardsWorkspaces(mh,opt.is2D,directory+'_tagged',theInputs2e2mu_1,opt.templateDir,opt.massError, 1,1,opt.useREFIT)
                
            c += 1
            

	a += 1






# the main procedure
def makeDCsandWSs():
    
    # parse the arguments and options
    global opt, args
    parseOptions()

    if (opt.appendName != ''):
        dirName = 'cards_'+opt.appendName
    

    subdir = ['HCG','HCG_XSxBR','figs']

    for d in subdir:
        if (opt.useJET == 1 or opt.useJET == 2 or opt.useJET == 3 or opt.useJET == 4):
            
            makeDirectory(dirName+'_tagged/'+d)
        else:
            makeDirectory(dirName+'/'+d)
        

    creationLoop(dirName)
    

    sys.exit()



# run the create_RM_cfg() as main()
if __name__ == "__main__":
    makeDCsandWSs()


