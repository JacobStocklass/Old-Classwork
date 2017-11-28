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

#include "Vertex.h"

using namespace std;

class Graph
{
	vector<Vertex*> _vertices;		// All vertices in the graph (vertex id == index)
	int _last_startingID = -1;

public:
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

};

#endif
