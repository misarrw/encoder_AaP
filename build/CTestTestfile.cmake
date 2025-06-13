# CMake generated Testfile for 
# Source directory: C:/Users/skwor/HSE/c++/encoder_AaP
# Build directory: C:/Users/skwor/HSE/c++/encoder_AaP/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[encoder_test]=] "C:/Users/skwor/HSE/c++/encoder_AaP/build/encoder_test.exe" "--force-colors" "-d")
set_tests_properties([=[encoder_test]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/skwor/HSE/c++/encoder_AaP/CMakeLists.txt;99;add_test;C:/Users/skwor/HSE/c++/encoder_AaP/CMakeLists.txt;0;")
subdirs("_deps/armadillo-build")
subdirs("external")
