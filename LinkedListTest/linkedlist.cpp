#include "linkedlist.h"
#include <iostream>
#include <stdlib.h>
#include "surveydata.h"

#ifndef NULL
#define NULL 0
#endif

linkedlist::linkedlist(void)
{
	head_sector = NULL;
	head_exposure = NULL;
	head_speed = NULL;
}

linkedlist::~linkedlist(void) {
	freeMemory();
}

linkedlist::linkedlist(const linkedlist& lk)
{
	head_sector = NULL;
	head_exposure = NULL;
	head_speed = NULL;

	Node *cur = lk.head_sector;
	
	while(cur)
	{
		addNode(cur->sector, cur->exposure, cur->speed);
		cur = cur->next_sector;
	}
}

linkedlist& linkedlist::operator = (const linkedlist &lk) 
{ 
	freeMemory();

	Node *cur = lk.head_sector;

	while(cur)
	{
		addNode(cur->sector, cur->exposure, cur->speed);
		cur = cur->next_sector;
	}

	return *this; 
}  


void linkedlist::freeMemory()
{
	Node *cur = NULL;
	Node *next = NULL;

	cur = head_sector;
	while(cur) {
		next = cur->next_sector;
		free(cur);		
		cur = next;
	}
	head_sector = NULL;
	head_exposure = NULL;
	head_speed = NULL;
}


void linkedlist::addNode(int sector, int exposure, int speed) 
{
	Node *node = (Node *) malloc(sizeof(Node));
	node->sector = sector;
	node->exposure = exposure;
	node->speed = speed;
	node->next_sector = NULL;
	node->next_exposure = NULL;
	node->next_speed = NULL;

	if( speed == -1 )
		speed = -1;

	Node *sector_node = findSectorNode(sector, exposure, speed);
	Node *exposure_node = findExposureNode(sector, exposure, speed);
	Node *speed_node = findSpeedNode(sector, exposure, speed);

	addNodeToSectorChain(sector_node, node);
	addNodeToExposureChain(exposure_node, node);
	addNodeToSpeedChain(speed_node, node);
}

void linkedlist::addNodeToSectorChain(Node *prev, Node *cur) 
{
	if( prev == NULL )
	{
		cur->next_sector = head_sector;
		head_sector = cur;
	}
	else
	{
		cur->next_sector = prev->next_sector;
		prev->next_sector = cur;
	}
}

void linkedlist::addNodeToExposureChain(Node *prev, Node *cur) 
{
	if( prev == NULL )
	{
		cur->next_exposure = head_exposure;
		head_exposure = cur;
	}
	else
	{
		cur->next_exposure = prev->next_exposure;
		prev->next_exposure = cur;
	}
}

void linkedlist::addNodeToSpeedChain(Node *prev, Node *cur) 
{
	if( prev == NULL )
	{
		cur->next_speed = head_speed;
		head_speed = cur;
	}
	else
	{
		cur->next_speed = prev->next_speed;
		prev->next_speed = cur;
	}
}


Node* linkedlist::findSectorNode(int sector, int exposure, int speed) 
{
	Node *cur = head_sector;
	Node *next = NULL;

	if( cur != NULL && sector < cur->sector )
		return NULL;

	while(cur) 
	{
		next = cur->next_sector;
		if( next == NULL )
			break;
		if( sector < next->sector )
			break;
		cur = next;
	}

	return cur;
}

Node* linkedlist::findExposureNode(int sector, int exposure, int speed) 
{
	Node *cur = head_exposure;
	Node *next = NULL;

	if( cur != NULL && exposure < cur->exposure )
		return NULL;

	while(cur) 
	{
		next = cur->next_exposure;
		if( next == NULL )
			break;
		if( exposure < next->exposure )
			break;
		cur = next;
	}

	return cur;
}

Node* linkedlist::findSpeedNode(int sector, int exposure, int speed) 
{
	Node *cur = head_speed;
	Node *next = NULL;

	if( cur != NULL && speed < cur->speed )
		return NULL;

	while(cur) 
	{	
		next = cur->next_speed;
		if( next == NULL )
			break;
		if( speed < next->speed )
			break;
		cur = next;
	}

	return cur;
}

bool linkedlist::containSector(int sector) 
{
	Node *cur = head_sector;
	bool exist = false;
	while(cur) {
		if( cur->sector == sector )
		{
			exist = true;
			break;
		}
		cur = cur->next_sector;
	}

	return exist;
}

void linkedlist::removeSector(int sector) 
{
	Node *cur = head_sector;
	Node *prev = head_sector;
	Node *next = NULL;
	bool exist = false;
	while(cur) {
		next = cur->next_sector;

		if( cur->sector == sector )
		{
			updateNextPointer(cur);			
			free(cur);
		}
		else if( cur->sector > sector )
			break;

		cur = next;
	}
}

void linkedlist::updateNextPointer(Node *node) 
{
	if( node == NULL )
		return;

	Node *cur = NULL;
	Node *prev = NULL;
	Node *next = NULL;
	
	prev = NULL;
	cur = head_sector;
	while(cur) {
		next = cur->next_sector;

		if( cur == node )
		{
			if( prev == NULL )
				head_sector = next;
			else
				prev->next_sector = next;
			break;
		}
		prev = cur;
		cur = next;
	}
	
	prev = NULL;
	cur = head_exposure;
	while(cur) {
		next = cur->next_exposure;
		if( cur == node )
		{
			if( prev == NULL )
				head_exposure = next;
			else
				prev->next_exposure = next;
			break;
		}
		prev = cur;
		cur = next;
	}

	prev = NULL;
	cur = head_speed;
	while(cur) {
		next = cur->next_speed;
		if( cur == node )
		{
			if( prev == NULL )
				head_speed = next;
			else
				prev->next_speed = next;
			break;
		}
		prev = cur;
		cur = next;
	}
}

void linkedlist::printHeader(char* header)
{
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << header << std::endl;
	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
}

void linkedlist::printData(Node *cur)
{
	if( cur == NULL )
		return;
	std::cout << "Section: #" << cur->sector << " " << cur->exposure << "% exposure, " << cur->speed << " kh/hr windspeed" << std::endl;	
}

void linkedlist::printListBySector() 
{
	printHeader("Data by Sector");

	Node *cur = head_sector;

	while(cur)
	{
		printData(cur);		
		cur = cur->next_sector;
	}
}

void linkedlist::printListByExposure()
{
	printHeader("Data by Exposure");

	Node *cur = head_exposure;

	while(cur)
	{
		printData(cur);				
		cur = cur->next_exposure;
	}
}


void linkedlist::printListBySpeed()
{
	printHeader("Data by Speed");

	Node *cur = head_speed;

	while(cur)
	{
		printData(cur);				
		cur = cur->next_speed;
	}
}

void linkedlist::printSectorList()
{
	Node *cur = head_sector;
	int sector = -1;
	int prev_sector = -1;
	int i = 0;

	while(cur)
	{
		sector = cur->sector;
		if( sector != prev_sector )
		{
			if( i > 0 )
				std::cout << ", ";
			std::cout << sector;
			i++;
			prev_sector = sector;
		}
		cur = cur->next_sector;
	}

	std::cout << std::endl;
}

void linkedlist::printAverage()
{
	Node *cur = head_sector;
	int sector = -1;
	int prev_sector = -1;
	int i = 0;

	surveydata survey;

	int sector1 = 0, exposure = 0, speed = 0;

	printHeader("Averages per sector");

	while(cur)
	{
		sector = cur->sector;
		if( sector != prev_sector )
		{
			survey.get(sector1, exposure, speed);
			if( sector1 >= 0 )
				std::cout << "Section: #" << sector1 << " " << exposure << "% exposure," << speed << " kh/hr windspeed" << std::endl;	

			survey.init();
			prev_sector = sector;
		}
		survey.pushData(cur->sector, cur->exposure, cur->speed);

		cur = cur->next_sector;
	}

	survey.get(sector1, exposure, speed);
	if( sector1 >= 0 )
		std::cout << "Section: #" << sector1 << " " << exposure << "% exposure," << speed << " kh/hr windspeed" << std::endl;	

	std::cout << std::endl;
}

void linkedlist::printHistogram() 
{
	printHeader("Histogram data for exposure");

	Node *cur = head_exposure;
	int exposure = -1;
	int prev_exposure = -1;
	int count = 0;

	while(cur)
	{
		exposure = cur->exposure;
		if( exposure != prev_exposure && prev_exposure >= 0 )
		{
			std::cout << prev_exposure << ", " << count << std::endl;
			count = 0;	
		}

		if( exposure != prev_exposure )
			prev_exposure = exposure;

		cur = cur->next_exposure;
		count++;
	}

	std::cout << prev_exposure << ", " << count << std::endl;


	printHeader("Histogram data for speed");

	cur = head_speed;
	int speed = -1;
	int prev_speed = -1;
	count = 0;

	while(cur)
	{
		speed = cur->speed;
		if( speed != prev_speed && prev_speed >= 0 )
		{
			std::cout << prev_speed << ", " << count << std::endl;
			count = 0;	
		}

		if( speed != prev_speed )
			prev_speed = speed;

		cur = cur->next_speed;
		count++;
	}

	std::cout << prev_speed << ", " << count << std::endl;
}
