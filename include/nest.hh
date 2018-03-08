#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <egg.hh>
#include <functional>

class nest {

private:
	//The number of eggs. Each egg represent a solution.
	int number_of_eggs;
	//The number of parameters of the problem.
	int number_of_parameters;
	//A vector that contain objects of the class 'egg'.
	std::vector<egg> eggs;
	//Fraction of worse nests that are going to be destroyed.
	double pa;

public:	
	//Empy constructor	
	nest(void);
	//Constructor of the class nest.
	//	int number_of_eggs : number of eggs to use
	//	int number_of_parameters : number of parameters to find
	//	double pa : fraction of nests to be destroyed. Must be a value bewteen 0 and 1.
	//	vector upper_bounds : Each position of the vector contains the upper bound of the i parameter.
	//	vector lower_bounds : Each position of the vector contains the lower bound of the i parameter.
	nest(const int &number_of_eggs, const int &number_of_parameters, const double &pa, const std::vector<double> lower_bounds, const std::vector<double> upper_bounds);
	//Metod that generate the initial population of eggs (initial solution of each egg).
	void initial_population(const std::function<double(std::vector<double>,int)> fitness);
	//Metod that compare the nest egg and the cuckoo egg. If the cuckoo egg has a better fitness, it replace the nest egg.
	//	double cuckoo_egg_fitness : fitnes of the cuckoo egg.
	//	vector cuckoo_solution : vector that represent the cuckoo egg. Each position is a solution for the i parameter.
	void compare_eggs(const double cuckoo_egg_fitness, const std::vector<double> cuckoo_solution);
	//Metod that destroy and generate new solutions fot the worst nests.
	void discover_eggs(const std::function<double(std::vector<double>,int)> fitness);
	//Metod that rank the eggs leaving the better ones (better fitness) at first place.
	void rank_eggs(void);
	//Metod that show information of the solutions.
	void postprocess(void);
	//Metod that return the egg solution.
	//	int i : Position of the egg in the vector.
	std::vector<double> get_egg_solution(const int &i) const;
	//Desctuctor of the class.
	~nest(void);
};