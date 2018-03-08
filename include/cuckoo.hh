#include <random>
#include <vector>
#include <math.h>
#include <iostream>

class cuckoo {

private:
	//Parameter for the levy flight.
	double beta;
	//Parameter for the levy flight.
	double sigma_u;
	//Parameter for the levy flight.
	double sigma_v;
	//Random number generator for the distribution u in the levy fligh.
	std::uniform_real_distribution<double> distribution_u;
	//Random number generator for the distribution v in the levy fligh.
	std::uniform_real_distribution<double> distribution_v;
	//Random number generator for the direction in the levy fligh.
	std::uniform_real_distribution<double> direction;
	//Vector that represent the egg (solution) of the cuckoo.
	std::vector<double> solution;

public:		
	//Empy constructor.
	cuckoo(void);
	//Constructor of the class.
	//	double beta : Parameter of the levy flight.
	//	int number_of_parameters : Number of the parameters in the problem.
	cuckoo(const double &beta, const int &number_of_parameters);
	//Method that return the number value of the levy flight.
	//	double step_size : The actual size ot the levy flight.
	double levy_flight(const double &step_size);
	//Method that return a cuckoo egg (new solution)
	//	vector nest_egg : egg from the nest (its used to generate the new solution).
	//	double step_size : The actual size ot the levy flight.
	//	vector upper_bounds : Each position of the vector contains the upper bound of the i parameter.
	//	vector lower_bounds : Each position of the vector contains the lower bound of the i parameter.
	std::vector<double> get_cuckoo(const std::vector<double> &nest_egg,const double &step_size, const std::vector<double> &lower_bound, const std::vector<double> &upper_bound);
	//Destructor of the class
	~cuckoo(void);
};