#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <functional>

class egg {

private:	
	//Number of parameters of the problem.
	int number_of_parameters;
	//Fitnes of the egg (quality of the solution)
	double fitness;
	//Vector that represent a solution.
	std::vector<double> solution;
	//Random number generators for each parameter of the problem.
	std::vector<std::uniform_real_distribution<double> > parameters_distributions;

public:		
	//Empy constructor
	egg(void);
	//Constructor of the class
	//	int number_of_parameters : number of parameters in the problem
	//	vector upper_bounds : Each position of the vector contains the upper bound of the i parameter.
	//	vector lower_bounds : Each position of the vector contains the lower bound of the i parameter.
	egg(const int &number_of_parameters, const std::vector<double> lower_bounds, const std::vector<double> upper_bounds);
	//Method that generate a new solution
	void generate_solution(const std::function<double(std::vector<double>,int)> fitness);
	//Method that change the actual solution with a new one.
	//	vector new_egg : New egg (solution) to replace the actual one.
	void change_egg(std::vector<double> new_egg);
	//Method that return the fitness (quality) of the solution
	double get_fitness(void) const;
	//Method that return the solution vector.
	std::vector<double> get_solution(void) const;
	//TODO : Eventualy remove
	void print_solution(void);
	//Destructor of the class
	~egg(void);
};