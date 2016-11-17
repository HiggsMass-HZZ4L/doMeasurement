from subprocess import call

for i in range(10):
    call('python run100Combine.py --index ' + str(i) + ' &', shell=True)
