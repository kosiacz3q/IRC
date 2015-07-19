projectLocation=$(pwd)


cd $projectLocation/core/Release

make clean
make 

cp $projectLocation/core/Release/libcore.so $projectLocation/client/Release/libcore.so
cp $projectLocation/core/Release/libcore.so $projectLocation/server/Release/libcore.so

cd $projectLocation/client/Release/

make clean
make 

cd $projectLocation/server/Release/

make clean
make 

cd $projectLocation/

mkdir -p $projectLocation/bin/Release

mv client/Release/client bin/Release/client
mv server/Release/server bin/Release/server
mv core/Release/libcore.so bin/Release/libcore.so