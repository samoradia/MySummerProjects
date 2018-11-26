#include "MatchmakerTests.h"
#include "Matchmaker.h"
using namespace std;

ENABLE_TESTS();

ADD_TEST("If everyone is already uniquely paired off, all pairs should be found.") {
    BipartiteGraph graph;

    graph.lhs = { "A", "B", "C" };
    graph.rhs = { "1", "2", "3" };
    graph.edges = {
        { "A", "1" },
        { "B", "2" },
        { "C", "3" }
    };

    /* We should get back all possible pairs. */
    auto match = matchmake(graph);

    expect(match == graph.edges);
}

ADD_TEST("If all possible pairs exist, everyone should end up paired off.") {
    BipartiteGraph graph;

    graph.lhs = { "A", "B" };
    graph.rhs = { "1", "2" };
    graph.edges = {
        { "A", "1" },
        { "A", "2" },
        { "B", "1" },
        { "B", "2" }
    };

    auto match = matchmake(graph);
    expect(match.size() == 2);

    for (auto person: graph.lhs + graph.rhs) {
        bool found = false;
        for (auto edge: match) {
            if (edge.first == person || edge.second == person) {
                found = true;
                break;
            }
        }
        expect(found);
    }
}
ADD_TEST("Matching will only be found if the function can break connections are reconnect"){
    BipartiteGraph graph;

    graph.lhs = { "A", "B", "C" };
    graph.rhs = { "1", "2", "3" };
    graph.edges = {
        { "A", "1" },
        { "A", "2" },
        { "B", "3" },
        { "C", "1" }
    };
    /*
     * Here, the program will likely choose A to connect to 1 first, then B to 3. C must connect to 1, so A should be shifted to
     * 2 and all nodes should be paired.
     */
    auto match = matchmake(graph);
    expect(match.size() == 3);

}
ADD_TEST("If there are less lhs than rhs, but all lhs have connections, not all are matched"){
    BipartiteGraph graph;

    graph.lhs = { "A", "B","C" };
    graph.rhs = { "1", "2" };
    graph.edges = {
        { "A", "1" },
        { "B", "2" },
        { "C", "2" }
    };
    /*
     * Here, there are only 2 rhs nodes to be paired to, and all of the lhs nodes should be able to connect to them.
     * So, only two of the nodes should be paired
     */
    auto match = matchmake(graph);
    expect(match.size() == 2);
}
