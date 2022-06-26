You need to download GCC, SFML-library, googletest, and boost library for running the game.



Commnad to run the game on linux terminal if you have above all: 
  "./CHESS"                   (in the project directory)
To run the tests: 
  "make test && testBin/test" (in the project directory)



---- Using CMake ----
To build the project using cmake if you have required libraries:
                                              (in the project directory)
1) mkdir build && cd build 
2) cmake ..
3) make
To run the project ( from the main directory ) :
  ./bin/main
To run the tests for the project ( from the main directory ):
  ./bin/main_tst



---- To download the required libraries ----
->make sure you already have compiler (GCC) and make if not then install it using :
  "sudo apt-get install build-essential"

->To download SFML library using termainal : 
  "sudo apt-get install libsfml-dev"

->To download googletest, type the following on terminal : 
1) "sudo apt-get install libgtest-dev"        (installing google test)
2) "sudo apt-get install cmake"               (installing cmake)
3) "cd /usr/src/gtest"
4) "sudo cmake CMakeLists.txt"
5) "sudo make"
6) "sudo cp *.a /usr/lib"                     (copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder)

->To download boost library using terminal:
  "sudo apt-get install libboost-all-dev"

HOPE YOU ENJOY THE GAME!
