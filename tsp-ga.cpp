# include "tsp-ga.h"


TSPGenome::TSPGenome(int numPoints){
  for(int i = 0; i < numPoints; i++){
    this->order.push_back(i);
  }
  std::random_shuffle(this->order.begin(),this->order.end());
}

TSPGenome::TSPGenome(const std::vector<int> &_order){
  this->order = _order;
}

TSPGenome::~TSPGenome(){

}

std::vector<int> TSPGenome::getOrder() const{
  return this->order;
}

void TSPGenome::computeCircuitLength(const std::vector<Point> &points){
  this->circuit_length = 0;
  std::vector<int>::const_iterator oit = this->order.begin();
  std::vector<Point>::const_iterator pit = points.begin();
  while(oit != this->order.end() - 1){
    //std::cout << "this->is circuitLength while"<<std::endl;
    this->circuit_length += (pit + *(oit))->distanceTo( *(pit + *(oit + 1)) );
    //std::cout << std::to_string(this->circuit_length) << std::endl;
    //std::cin.get();
    oit++;
  }
  this->circuit_length += (pit + *(this->order.begin()))->distanceTo( *(pit + *(this->order.end() - 1)) );
//std::cout << "final: "<<std::to_string(this->circuit_length) << std::endl;
}
double TSPGenome::getCircuitLength() const{
  return this->circuit_length;
}

void TSPGenome::mutate(){
  int i = rand() % (order.size() - 1) + 1;
  int j = rand() % (order.size() - 1) + 1;
  while(j == i){
    j = rand() % (order.size() - 1) + 1;
  }
  int temp = this->order[i];
  this->order[i] = this->order[j];
  this->order[j] = temp;
}

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2){
  std::vector<int> offspring;
  std::vector<int> p1 = g1.getOrder();
  std::vector<int> p2 = g2.getOrder();
  for (std::size_t i = 0, j = rand() % (p1.size() - 2) + 1; i < j; i++){
    offspring.push_back(p1.at(i));
  }
  std::set<int> finishedset; 
  for (auto i: offspring){
    finishedset.insert(i);
  }
  for (auto i: p2){
    auto location = finishedset.find(i);
    if(location == finishedset.end()){
      offspring.push_back(i);
        finishedset.insert(i);
    }

  }
  return TSPGenome(offspring);
}

bool operator<(const TSPGenome &g1, const TSPGenome &g2){
  return g1.getCircuitLength() < g2.getCircuitLength();

}

TSPGenome findAShortPath(const std::vector<Point> &points,
    int populationSize, int numGenerations,int keepPopulation, int numMutations){
  
  std::vector<TSPGenome> population;

  for(int i = 0; i < populationSize; i++){
    population.push_back( TSPGenome(points.size()));
  }

  for(int gen = 0; gen < numGenerations; ++gen){
    for(std::vector<TSPGenome>::iterator tit = population.begin(), end = population.end(); tit != end; tit++){
      tit->computeCircuitLength(points);
      //std::cout << + "point: "<<i.getCircuitLength() << std::endl;
    }
    /*std::cout << std::to_string(gen) +"before sort"<< std::endl;
    for( TSPGenome i: population){
      std::cout<< i.getCircuitLength()<< std::endl;
    }*/

    std::sort(population.begin(), population.end()); 

    if (gen % 10 == 0) {
      std::cout << "Generation " << gen << ":  shortest path is "
        << population[0].getCircuitLength() << std::endl;
    }
    if (gen == numGenerations - 1){
      return population[0];
    }

    for (int i = keepPopulation; i < population.size(); i++){
      std::size_t p1 = rand() % keepPopulation;
      std::size_t p2 = rand() % keepPopulation;
      while(p1 == p2){
        p2 = rand() % keepPopulation;
      }
      population[i] = crosslink(population[p1], population[p2]);

    }

      for(int j = 0; j < numMutations; j++){
      population[1+rand()% (populationSize - 1)].mutate();
    
    }

  }

  std::sort(population.begin(), population.end());
  return  population[0];

}
