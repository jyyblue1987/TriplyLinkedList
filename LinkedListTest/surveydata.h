#pragma once
class surveydata
{
	int m_nSector;
	int m_nSumExposure;
	int m_nSumSpeed;
	int m_nCount;
public:
	surveydata(void);

	void init(); 
	void pushData(int sector, int exposure, int speed);
	void get(int &sector, int &exposure, int &speed);
};

