#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "StampyPlugin.h"

void StampyPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }
}

void StampyPlugin::run() {
   
}

void StampyPlugin::output(std::string file) {
   std::string command = "export OLDPATH=${PYTHONPATH}; export PYTHONPATH=${PYTHON2_DIST_PACKAGES}:${PYTHON2_SITE_PACKAGES}:${PYTHONPATH}; python2 plugins/Stampy/stampy/stampy.py ";
// python2 seq2HLA.py -1 /biorg/data/RNA/UMiami/small/S12_R1.fastq -2 /biorg/data/RNA/UMiami/small/S12_R2.fastq -r "Trevor"

 command += " -G "+PluginManager::addPrefix(parameters["seq1"]);
 command += " "+PluginManager::addPrefix(parameters["seq2"]);
 command += " >& "+file;
 //; export PYTHONPATH=OLDPATH"; 
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<StampyPlugin> StampyPluginProxy = PluginProxy<StampyPlugin>("Stampy", PluginManager::getInstance());
