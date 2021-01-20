#pragma once
class datalogger
{
public:
	datalogger(void);

	void addData(int sector, int exposure, int speed);
	bool containsSector(int sector);
	void removeSector(int sector);
	void printReport();
	void printSectorList();	
};

