/**
 *  Core graph data structure
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <list>
#include <stack>
#include <iostream>


#include "Vertex.h"

using namespace std;

class Graph
{
	vector<Vertex*> _vertices;		// All vertices in the graph (vertex id == index)
	int _last_startingID = -1;

public:
    void setallindegrees()
    {
        int index = 0;
        _vertices[index]->setIn(0);
        index++;
        _vertices[index]->setIn(0);
        index++;
        _vertices[index]->setIn(1);
        index++;
        _vertices[index]->setIn(0);
        index++;
        _vertices[index]->setIn(2);
        index++;
        _vertices[index]->setIn(1);
        index++;
        _vertices[index]->setIn(1);
        index++;
        _vertices[index]->setIn(1);
        index++;
        _vertices[index]->setIn(2);
        index++;
        _vertices[index]->setIn(1);
        index++;
        _vertices[index]->setIn(1);
        index++;
        _vertices[index]->setIn(2);
        index++;
        _vertices[index]->setIn(1);
        index++;
        _vertices[index]->setIn(1);
        index++;
        _vertices[index]->setIn(2);
        index++;
        _vertices[index]->setIn(3);
        index++;
        _vertices[index]->setIn(1);
    }
	// Remove all vertices
	void clear() {
		_vertices.clear();
	}

	// Number of vertices in our graph
	int size() {
		return _vertices.size();
	}

	/**
	 *  Parses a single in from a dot file
	 */
	void parseDotfileLine( string line ) {
		smatch matched;
		regex newSubGraph ("\\s*(\\S+)\\s*->\\s*(\\S+)\\s*\\[.*?weight=\"*(\\S+?)\"*\\s*\\]\\;");

		if( regex_match( line, matched, newSubGraph ) ) {
			string strconv = matched[1];
			int srcid = ::atof(strconv.c_str());
			strconv = matched[2];
			int destid = ::atof(strconv.c_str());
			strconv = matched[3];
			double weight = ::atof(strconv.c_str());
			//cout << "SrcID: " << srcid << " | DestID: " << destid << " | Edge Weight: " << weight << endl;

			// Grow set of vertices if new high id is inserted or connected to
			int growVerts = max(srcid, destid);
			for( int i = _vertices.size(); i <= growVerts; i++ ) {
				Vertex* newVert = new Vertex(i);		// Allocate the new vertex
				_vertices.push_back( newVert );		// Add vertex to the end of the list 
			}
			_vertices[srcid]->addEdge(_vertices[destid], weight);
		}
	}

	/**
	 *  Loads a single Graphviz-(limited) formatted dot file with a graph
	 */
	void loadDotFile( string filename ) {
		cout << " [d] Loading dot file: " << filename;
		ifstream ifs( filename );
		string instr;
		while (getline(ifs, instr)) {
			parseDotfileLine( instr );
		}
		cout << " - Done." << endl;
	}

	/**
	 *  Returns stringified version of graph for viewing
	 */
	string to_string( bool with_edges = false ) {
		string ret = "";
		for( auto vert : _vertices ) {
			ret += vert->to_string( with_edges ) + "\n";
		}
		return ret;
	}
    list<Vertex*> getTopoSort(void)
    {
        //first we want to find the node with indegree of 0
        //we'll iterate through the vector of the graph and check for indegree of zero
        int V = _vertices.size();
        vector<int> in_degree(V, 0);
        vector<Vertex*>::iterator it = _vertices.begin();
        for(it = _vertices.begin(); it < _vertices.end(); it++)
        {
            int ID = (*it)->getId();
            int IN = (*it)->getIn();
            in_degree[ID] = IN;
        }
        queue<int> q;
        for(int i = 0; i < V; i++)
        {
            if(in_degree[i] == 0)
            {
                q.push(i);
            }
        }
        
        int numvert = 0;
        
        list<Vertex*> sorted_topo;
        vector<int> visited(V,0);
        
        while(!q.empty())
        {
            int temp = q.front();
            q.pop();
            sorted_topo.push_back(_vertices[temp]);
        
        visited[temp] = 1;
        //let's visit the neighbors
        Vertex* current = _vertices[temp];
        unordered_map<Vertex*, double> Edges = current->getEdges();
        unordered_map<Vertex*, double>::iterator Edgesit = Edges.begin();
        for(Edgesit = Edges.begin(); Edgesit != Edges.end(); Edgesit++)
        {
            int foo = (*Edgesit).first->getId();
            in_degree[foo]--;
            if(in_degree[foo] == 0)
            {
                q.push(foo);
            }
        }
        numvert++;
        }
        
        for(it = _vertices.begin(); it != _vertices.end(); it)
        {
            if(visited[(*it)->getId()] == 1)
            {
                _vertices.erase(it);
            }
            else
            {
                it++;
            }
        }
        if(numvert != V)
        {
            cout<<"numvert is: "<< numvert << endl;
            cout<<"There's a cycle or something" << endl;
        }
        return sorted_topo;
    }
};

#endif
