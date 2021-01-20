#pragma once

struct Node {
	int sector;
	int exposure;
	int speed;
	Node *next_sector;
	Node *next_exposure;
	Node *next_speed;
};

class linkedlist
{
	Node *head_sector;
	Node *head_exposure;
	Node *head_speed;

	void addNodeToSectorChain(Node *prev, Node *cur); 
	void addNodeToExposureChain(Node *prev, Node *cur);
	void addNodeToSpeedChain(Node *prev, Node *cur);
	Node* findSectorNode(int sector, int exposure, int speed);
	Node* findExposureNode(int sector, int exposure, int speed);
	Node* findSpeedNode(int sector, int exposure, int speed);
	void updateNextPointer(Node *cur); 

public:
	linkedlist(void);
	~linkedlist(void);

	void	addNode(int sector, int exposure, int speed); 
	bool	containSector(int sector);
	void	removeSector(int sector);

	void	printListBySector();
	void	printListByExposure();
	void	printListBySpeed();

};

