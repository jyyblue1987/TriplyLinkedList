#include "surveydata.h"


surveydata::surveydata(void)
{
	init();
}

void surveydata::init() 
{
	m_nSector = -1;
	m_nSumExposure = 0;
	m_nSumSpeed = 0;
	m_nCount = 0;
}

void surveydata::pushData(int sector, int exposure, int speed)
{
	m_nSector = sector;
	m_nSumExposure += exposure;
	m_nSumSpeed += speed;
	m_nCount++;
}

void surveydata::get(int &sector, int &exposure, int &speed)
{
	sector = m_nSector;
	if( m_nCount > 0 )
	{
		exposure = m_nSumExposure / m_nCount;
		speed = m_nSumSpeed / m_nCount;
	}
	else
	{
		exposure = 0;
		speed = 0;
	}	
}
