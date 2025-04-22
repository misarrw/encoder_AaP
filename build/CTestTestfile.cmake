# CMake generated Testfile for 
# Source directory: /Users/aidasardarova/Documents/HSE/A&P/encoder_AaP
# Build directory: /Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[encoder_test]=] "/Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/build/encoder_test" "--force-colors" "-d")
set_tests_properties([=[encoder_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/CMakeLists.txt;42;add_test;/Users/aidasardarova/Documents/HSE/A&P/encoder_AaP/CMakeLists.txt;0;")
subdirs("external")
