#pragma once
#include <vector>
#include <memory>
#include "Map.h"

//class declaration
class SimpleEdge;
class SimpleNode;

//List of sorted edges for a particular node
typedef std::vector<SimpleEdge*> EdgeContainer;

//Node Map
typedef TMap<const TCHAR*, SimpleNode*> NodeTMap;

//Shared pointer for every node object created
typedef std::unique_ptr<SimpleNode> SimpleNodePtr;

class NodeCont
{
public:
	NodeCont() {};
	~NodeCont() {};

	//Maps to store the pointers to the parsed edges and nodes (pointers to the objects created)
	NodeTMap NodeMap;
};












