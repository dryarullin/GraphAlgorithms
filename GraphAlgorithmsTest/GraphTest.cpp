#include "Graph.h"
#include "GraphTest.h"

#include <gtest/gtest.h>
#include <memory>

using ::testing::TestWithParam;
using ::testing::Values;

typedef GraphRepresentation<int>* CreateRepresentationFunc();

GraphRepresentation<int>* CreateAdjacencyMatrixRepresentation()
{
	return new AdjacencyMatrixRepresentation<int>();
}


GraphRepresentation<int>* CreateAdjacencyListRepresentation()
{
	return new AdjacencyListRepresentation<int>();
}


class GraphTest : public ::TestWithParam<CreateRepresentationFunc*>
{
protected:

	virtual void SetUp()
	{
		representation = (*GetParam())();
	}

	virtual void TearDown()
	{
		if (representation)
		{
			delete representation;
			representation = nullptr;
		}
	}

	GraphRepresentation<int>* representation;
	std::unique_ptr<Graph<int>> graph;
};



TEST_P(GraphTest, AddVertexDirectedTest)
{
	representation->Resize(10);
	graph = std::make_unique<DirectedGraph<int>>(representation);
	graph->AddVertex();

	EXPECT_EQ(11, graph->NumberOfVertices());
	representation->AddVertex();
	EXPECT_EQ(12, graph->NumberOfVertices());
}


TEST_P(GraphTest, AddVertexUndirectedTest)
{
	representation->Resize(10);
	graph = std::make_unique<UndirectedGraph<int>>(representation);
	graph->AddVertex();

	EXPECT_EQ(11, graph->NumberOfVertices());
	representation->AddVertex();
	EXPECT_EQ(12, graph->NumberOfVertices());

}


TEST_P(GraphTest, AddEdgeDirectedTest)
{
	representation->Resize(2);
	graph = std::make_unique<DirectedGraph<int>>(representation);
	graph->AddEdge(0, 1, 1);

	EXPECT_EQ(2, graph->NumberOfVertices());
}


TEST_P(GraphTest, AddEdgeUndirectedTest)
{
	representation->Resize(2);
	graph = std::make_unique<UndirectedGraph<int>>(representation);
	graph->AddEdge(0, 1, 1);
}



INSTANTIATE_TEST_CASE_P(GraphRepresenattions, GraphTest, Values(&CreateAdjacencyMatrixRepresentation, &CreateAdjacencyListRepresentation));