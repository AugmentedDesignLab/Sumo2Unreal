#pragma once
#include <vector>
#include <memory>
#include "Map.h"

//class declaration
class SimpleEdge;
class SimpleNode;

//List of sorted edges for a particular node
typedef std::vector<SimpleEdge*> EdgeVector;

//Node Map and Edge Map
typedef TMap<const TCHAR*, SimpleNode*> NodeTMap;
typedef TMap<const TCHAR*, SimpleEdge*> EdgeTMap;

//Shared pointer for every node object created
typedef std::unique_ptr<SimpleNode> SimpleNodePtr;
typedef std::unique_ptr<SimpleEdge> SimpleEdgePtr;

class NodeCont
{
public:
	NodeCont() {};
	~NodeCont() {};

	//Maps to store the pointers to the parsed nodes (pointers to the objects created)
	NodeTMap NodeMap;
};

class EdgeCont
{
public:
	EdgeCont() {};
	~EdgeCont() {};

	//Map to store the pointers to the parsed edges (pointers to the objects created)
	EdgeTMap EdgeMap;
};












