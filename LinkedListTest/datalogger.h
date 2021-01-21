#pragma once

#include "linkedlist.h"
class datalogger
{
	linkedlist m_lk;
public:
	datalogger(void);

	void addData(int sector, int exposure, int speed);
	bool containsSector(int sector);
	void removeSector(int sector);
	void printReport();
	void printSectorList();	
};

