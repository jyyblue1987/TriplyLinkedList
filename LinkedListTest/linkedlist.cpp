#include "linkedlist.h"
#include <stdlib.h>

#ifndef NULL
#define NULL 0
#endif

linkedlist::linkedlist(void)
{
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
	node->next_sector = NULL;

	Node *sector_node = findSectorNode(sector, exposure, speed);
	Node *exposure_node = findExposureNode(sector, exposure, speed);
	Node *speed_node = findSpeedNode(sector, exposure, speed);

	addNodeToSectorChain(sector_node, node);
}

void linkedlist::addNodeToSectorChain(Node *prev, Node *cur) 
{
	if( prev == NULL )
		head_sector = cur;
	else
	{
		cur->next_sector = prev->next_sector;
		prev->next_sector = cur;
	}
}

void linkedlist::addNodeToExposureChain(Node *prev, Node *cur) 
{
	if( prev == NULL )
		head_exposure = cur;
	else
	{
		cur->next_exposure = prev->next_exposure;
		prev->next_exposure = cur;
	}
}

void linkedlist::addNodeToSpeedChain(Node *prev, Node *cur) 
{
	if( prev == NULL )
		head_speed = cur;
	else
	{
		cur->next_speed = prev->next_speed;
		prev->next_speed = cur;
	}
}


Node* linkedlist::findSectorNode(int sector, int exposure, int speed) 
{
	Node *cur = head_sector;
	while(cur) {
		if( cur->sector < sector )
			break;
		cur = cur->next_sector;
	}

	while(cur) {
		if( cur->exposure < exposure )
			break;
		cur = cur->next_sector;
	}

	while(cur) {
		if( cur->speed < speed )
			break;
		cur = cur->next_sector;
	}

	return cur;
}

Node* linkedlist::findExposureNode(int sector, int exposure, int speed) 
{
	Node *cur = head_exposure;

	while(cur) {
		if( cur->exposure < exposure )
			break;
		cur = cur->next_sector;
	}
 
	while(cur) {
		if( cur->sector < sector )
			break;
		cur = cur->next_sector;
	}

	while(cur) {
		if( cur->speed < speed )
			break;
		cur = cur->next_sector;
	}
	return cur;
}

Node* linkedlist::findSpeedNode(int sector, int exposure, int speed) 
{
	Node *cur = head_speed;


	while(cur) {
		if( cur->speed < speed )
			break;
		cur = cur->next_sector;
	}

	while(cur) {
		if( cur->sector < sector )
			break;
		cur = cur->next_sector;
	}

	while(cur) {
		if( cur->exposure < exposure )
			break;
		cur = cur->next_sector;
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
