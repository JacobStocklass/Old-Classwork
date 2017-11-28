#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

class Vertex
{
private:
	int _id;                    // ID (key) of given vertice
	bool _known = false;        // Dijkstra's algorithm "known" flag
	Vertex* _path = nullptr;    // Dijkstra's algorithm parent vertex pointer
	    // Weight of path through graph - starts at a true infinity (inf)
	double _path_weight = std::numeric_limits<double>::infinity();

	unordered_map<Vertex*, double> _edges;  // Adjacent nodes to this vertice


public:

	Vertex() { }

	Vertex(int id) {
		_id = id;
	}

	string to_string( bool with_edges = false ) {
		//cout << "Vertex self address: " << this  << endl;
		string ret = "V- ID: " + std::to_string(_id);
		ret += "\t| k: "; ( _known ) ? ret += "T" : ret += "F";
		ret += "\t| pw: " + std::to_string(_path_weight);
		ret += "\t| p: ";
		if( _path ) {
			ret += std::to_string( _path->getId() );
		} else {
			ret += "null";
		}

		if( with_edges ) {
		ret += " | Edges:";
			for( auto edge : _edges ) {
				ret += "\n     edge to: " + std::to_string( edge.first->getId() );
				ret += " | weight: " + std::to_string( edge.second);
			}
		}
		return(ret);
	}

	/* Just a bunch of accessors and setters */
	int getId() const { return _id; }

	double getPathWeight() const { return _path_weight; }
	void setPathWeight(double weight) { _path_weight = weight; }

	bool is_known() const { return _known; }
	void set_known() { _known = true; }
	void unset_known() { _known = false; }
	
	void set_path(Vertex *path) { _path = path; }
	Vertex *get_path() { return _path; }

	void addEdge(Vertex *vertex, double weight) { _edges[vertex] = weight; }
	double getEdgeWeight(Vertex *edge) { return _edges[edge]; }
	unordered_map<Vertex *, double> &getEdges() { return _edges; }
	void removeEdge(Vertex *vertex) { _edges.erase(vertex); }
};

/**
 *  Comparison operators used for sorting, treeing, and queuing
 *  These will provide functions to call when passed vertices to compare
 */
int operator==(const Vertex &lhs, const Vertex &rhs)
{
	return lhs.getId() == rhs.getId();
}

bool operator<(const Vertex &lhs, const Vertex &rhs)
{
	return lhs.getId() < rhs.getId();
}

bool operator>(const Vertex &lhs, const Vertex &rhs)
{
	return lhs.getId() > rhs.getId();
}


/**
 *  Class used to compare path weights in priority queues
 */
class PathWeightComparer
	{
	public:
		bool operator()(const Vertex* lhs, const Vertex* rhs)
		{
			return (lhs->getPathWeight() > rhs->getPathWeight());
		}
	};


/**
 *  Hashing algorithm must exist in STD namespace
 *   Used by structures like unordered_map (it's a hash table)
 */
namespace std {

	template <>
	struct hash<Vertex>
	{
		// Provide a hash (convert item into integer)
		std::size_t operator()(const Vertex& item) const
		{
			size_t hash_val = 0;
			hash<int> int_hash{};              // To hash INTs using the STL
			hash_val = int_hash(item.getId()); // Define hashing algorithm.
			return hash_val;                   // Add other hash algs as necessary
		}
	};
}

#endif
