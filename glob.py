import glob2

#path = '**/*.txt'
#for file in glob2.glob(path):
#    print(file)
sources = glob2.glob('./src/*.cpp') + glob2.glob('./src/**/*.cpp')
for i in sources:
    print(i)
