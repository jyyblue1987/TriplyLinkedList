#include <iostream>
#include <fstream>
#include "datalogger.h"

using namespace std;

void createReport(datalogger& dl,const char* label)
{
    dl.printReport();
}

void listBadSectors(datalogger& dl)
{
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "Bad sectors" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    dl.printSectorList();
}

int main(int argc, char** argv) {

    datalogger data;
    datalogger badSectorData; // a list of items with bad sectors

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <datafile>" << std::endl;
        exit(0);
    }

    // Read the data

    char* datafile = argv[1];
    ifstream inDatafile(datafile);
    int sector;
    int exposure;
    int speed;

    while (!inDatafile.eof()) {
        inDatafile >> sector;
        inDatafile >> exposure;
        inDatafile >> speed;

        if (!inDatafile.eof()) {
            data.addData(sector, exposure, speed);
            if (((exposure < 0) || (speed < 0)) && !badSectorData.containsSector(sector)) {
                badSectorData.addData(sector,exposure,speed);
            }

            if (badSectorData.containsSector(sector)) {
                data.removeSector(sector);
            }
        }
    }
    createReport(data,"Data");
    listBadSectors(badSectorData);

    return(0);
}
