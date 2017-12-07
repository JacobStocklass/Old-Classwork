#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <string.h>
#include "Graph.h"
#include "Vertex.h"
#include <list>

using namespace std;

/**
 *  Test the graph algorithm with the topo graph from the class textbook
 *  Graph may be found on page ??? and in topoGraph.png
 */
void run_TopoGraphTest()
{
	cout << " [d] Testing Topological sort graph (small graph) tests." << endl;

	Graph graph{};
	graph.loadDotFile( "topoGraph.dot" );
    graph.setallindegrees();

	cout << "  [d] Current graph structure from topo's graph: " << endl;
	cout << graph.to_string( true ) << endl;

	cout << "  [d] ** Starting Topological Here **" << endl;
	list<Vertex*> topoResults = graph.getTopoSort();

//loop through the list to print the topo sort
    std::list<Vertex*>::iterator it;
    for(list<Vertex*>::iterator it = topoResults.begin(); it != topoResults.end(); it++)
    {
        cout<< (*it)->getId() << endl;
    }
	cout << " [!!!!] Valid output would look something like:" << endl;
	cout << "  {1, 0, 8, 9, 10, 16, 2, 3, 6, 5, 15, 4, 12, 14, 7, 13, 11}" << endl;
	cout << "  -- No, I don't know your final output because there's actually several places you could do it in different ways." << endl;



	cout << "  [d] Current graph structure AFTER topographical sort run (should be empty): " << endl;
	cout << graph.to_string( true ) << endl;

	cout << " [d] Topo sort graph tests complete. " << endl;
}


/**
 *  Test mode operations
 */
void run_test_mode( bool bigtest = false ) {
	cout << " [t] Running in test mode. " << endl;
	run_TopoGraphTest();

	if( bigtest )
		cout << " [!] No Bigtest option yet" << endl;
	cout << " [t] All tests complete. " << endl;
}


/**
 *  Normal mode execution for general user control
 */
void run_normal_mode() {
	cout << "  [!] Nothing to do in normal mode so here's a hat: " << endl;

cout <<""
"       _.-'`'-._\n"
"    .-'    _    '-.\n"
"     `-.__  `\\_.-'\n"
"       |  `-``\\|\n"
" jgs   `-.....-A\n"
"               #\n"
"               #\n";
	cout << endl;
	cout << " Oh, and you should probably run 'make test' to test your program. \n"
" To run the mouse brain graph, use 'make bigtest', which takes about 15 sec for me. \n"
" You'll find images of the graphs we're using in:\n"
"     bookGraph.png\n"
"     MouseBrainGraph.png (currently being built - fingers crossed)\n"
"\n"
" Both built using: neato -Tpng bookGraph.dot -o bookGraph.png\n"
" Both built using: neato -Tpng MouseBrainGraph.dot -o MouseBrainGraph.png\n";
}




/**
 *  Main function for test or use
 */
int main( int argc, char* argv[] )
{
	int retState = 0;

	// Note: If you call this program like this: ./Dijkstra --test
	//  it will call the test function
	if( argc > 1 && !strcmp(argv[1], "--bigtest" )  )
	{
		run_test_mode( true );
		cout << " [x] BIGTEST testing program complete. " << endl;
	}
	else if( argc > 1 && !strcmp(argv[1], "--test" ) )
	{
		run_test_mode( );
		cout << " [x] Testing program complete. " << endl;
	}
	else
	{
		cout << " [x] Running in normal mode. " << endl;

		run_normal_mode();
	}
}

