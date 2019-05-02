import os
filepath = os.listdir('data/')
filepath.sort()

os.system('g++ Digital.cpp -O3')
for file in filepath:
    os.system('./a.out data/' + file)
