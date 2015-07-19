projectLocation=$(pwd)


cd $projectLocation/core/Debug

make clean
make 

cp $projectLocation/core/Debug/libcore.so $projectLocation/client/Debug/libcore.so

cd $projectLocation/client/Debug/

make clean
make 

cd $projectLocation/server/Debug/

make clean
make 

cd $projectLocation/

mkdir -p $projectLocation/bin/Debug

mv client/Debug/client bin/Debug/client
mv server/Debug/server bin/Debug/server
mv core/Debug/libcore.so bin/Debug/libcore.so