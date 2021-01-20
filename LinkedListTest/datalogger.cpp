#include <iostream>

#include "datalogger.h"


datalogger::datalogger(void)
{
}

void datalogger::addData(int sector, int exposure, int speed) 
{
	m_lk.addNode(sector, exposure, speed);
}

bool datalogger::containsSector(int sector) 
{
	return m_lk.containSector(sector);	
}

void datalogger::removeSector(int sector) 
{
	m_lk.removeSector(sector);
}

void datalogger::printReport() 
{
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "Data by sector" << std::endl;
	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	m_lk.printListBySector();
	m_lk.printListByExposure();
	m_lk.printListBySpeed();
}

void datalogger::printSectorList() 
{
	m_lk.printSectorList();
}