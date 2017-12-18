# include <cstdlib>
# include <iostream>
# include "tsp-ga.h"
# include <ctime>



void usage(const char* progname){
	std::cout << "usage: " << progname << " n f"<< std::endl;
}

void printArray(const std::vector<int> &points){
	std::cout << "[";
	for(auto i: points){
		std::cout << std::to_string(i) << ',';
	}
	std::cout << "]" << std::endl;
}

int main(int argc, char **argv){
	if (argc != 4){
		usage(argv[0]);
	}
	srand( time( NULL ) );
	// formate = ./tsp-ga population generations keep mutate
	int population = atoi(argv[1]);
	int generations = atoi(argv[2]);
	int keep = (int) (atof(argv[3]) * (double)population + 0.5);
	int mutate = (int) (population * atof(argv[4]));


	int n;
	std::cout << "how many points?" << std::endl;
	std::cin >> n;
	std::vector<Point> points;
	int i = 0;
	while (i < n){
		double a,b,c;
		std::cout<< "point " + std::to_string(i);
		std::cin >> a >> b >> c;
		points.push_back(*(new Point(a,b,c)));
		i++;
	}
	
	TSPGenome bestorder = findAShortPath(points, population, generations, keep, mutate);
	printArray(bestorder.getOrder());
	std::cout << std::endl;
	
	std::cout << "Shortest distance: " << bestorder.getCircuitLength()<< std::endl;
	return 0;
}