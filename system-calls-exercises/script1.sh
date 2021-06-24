#!/bin/bash

echo ">> " g++ -O2 -Wall openreadclosestat.cpp -o openreadclosestat > exampleoutput.txt
g++ -O2 -Wall openreadclosestat.cpp -o openreadclosestat >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " ./openreadclosestat >> exampleoutput.txt
./openreadclosestat >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " ./openreadclosestat Test1 >> exampleoutput.txt
./openreadclosestat Test1 >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " ./openreadclosestat Test2 >> exampleoutput.txt
./openreadclosestat Test2 >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " ./openreadclosestat Test3 >> exampleoutput.txt
./openreadclosestat Test3 >> exampleoutput.txt
echo >> exampleoutput.txt

echo >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " g++ -O2 -Wall popenfgets.cpp -o popenfgets >> exampleoutput.txt
g++ -O2 -Wall popenfgets.cpp -o popenfgets >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " ./popenfgets >> exampleoutput.txt
./popenfgets >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " ./popenfgets Test1 >> exampleoutput.txt
./popenfgets Test1 >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " ./popenfgets Test2 >> exampleoutput.txt
./popenfgets Test2 >> exampleoutput.txt
echo >> exampleoutput.txt

echo ">> " ./popenfgets Test3 >> exampleoutput.txt
./popenfgets Test3 >> exampleoutput.txt
echo >> exampleoutput.txt

echo >> exampleoutput.txt

# WHY DID I DO THIS LIKE THIS!! THIS WAS DUMB

rm openreadclosestat
rm popenfgets

