# include <vector>
# include <algorithm>
# include "Point.h"
# include <set>
# include <iostream>

class TSPGenome{
private:
	std::vector<int> order;
	double circuit_length;
public:
	TSPGenome(int numPoints);
	TSPGenome(const std::vector<int> &order);

	~TSPGenome();

	std::vector<int> getOrder() const;

	double getCircuitLength() const;
	void computeCircuitLength(const std::vector<Point> &points);

	void mutate();
};

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);
bool operator<(const TSPGenome &g1, const TSPGenome &g2);

TSPGenome findAShortPath(const std::vector<Point> &points,
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations);


