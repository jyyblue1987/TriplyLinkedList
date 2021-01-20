#include <iostream>

#include "datalogger.h"


datalogger::datalogger(void)
{
}

void datalogger::freeMemory()
{
	m_lk.freeMemory();
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
	m_lk.printListBySector();
	m_lk.printListByExposure();
	m_lk.printListBySpeed();

	m_lk.printAverage();

	m_lk.printHistogram();

}

void datalogger::printSectorList() 
{
	m_lk.printSectorList();
}