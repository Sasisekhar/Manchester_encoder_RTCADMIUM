# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/esp-idf/components/bootloader/subproject"
  "D:/My_Files/Career/Education/University/VIT/FYP/ESPIDF/Blinky_ESP32/sample_project/build/bootloader"
  "D:/My_Files/Career/Education/University/VIT/FYP/ESPIDF/Blinky_ESP32/sample_project/build/bootloader-prefix"
  "D:/My_Files/Career/Education/University/VIT/FYP/ESPIDF/Blinky_ESP32/sample_project/build/bootloader-prefix/tmp"
  "D:/My_Files/Career/Education/University/VIT/FYP/ESPIDF/Blinky_ESP32/sample_project/build/bootloader-prefix/src/bootloader-stamp"
  "D:/My_Files/Career/Education/University/VIT/FYP/ESPIDF/Blinky_ESP32/sample_project/build/bootloader-prefix/src"
  "D:/My_Files/Career/Education/University/VIT/FYP/ESPIDF/Blinky_ESP32/sample_project/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/My_Files/Career/Education/University/VIT/FYP/ESPIDF/Blinky_ESP32/sample_project/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/My_Files/Career/Education/University/VIT/FYP/ESPIDF/Blinky_ESP32/sample_project/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
