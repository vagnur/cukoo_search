# Cukoo Search Algorithm

C++ implementation of the cuckoo search metaheuristic for optmization problems.

## Installation

In order to use the cuckoo search, you need to use the makefile of the repository:

```
~@ make 
```

## Usage

First, you need to declare the fitness function. In the code we have an example of a fitness function. The algorithm searchs in a [0,1] space, so you need to adjust the value of the parameters in the fitness function, see the example in [cuckoosearch.cc](../master/src/cuckoosearch.cc) file for details.

Then, you need a file that contains the minimun and maximun value of each parameter _i_, like this:

```
0 1 2 3 4
4 5 6 7 8
```
In this case the parameters min and max, when _i=3_ for example, are 2 and 6 respectively.

To execute the program:

```
~@ ./cs -p -n -g -b -f -s
```

Where:

* p -> Number of parameters in the problem
* n -> Number of nests
* g -> Maximum number of generations
* b -> Betta parameter for the levy flight
* f -> % of nest to destroy 
* s -> Stop criterion

## Algorithm

For more information see: _Yang, X. S., & Deb, S. (2009, December). Cuckoo search via Lévy flights. In Nature & Biologically Inspired Computing, 2009. NaBIC 2009. World Congress on (pp. 210-214). IEEE._


For more information about Levy Flights, see chapter 2 of _Yang, X. S. (2010). Nature-inspired metaheuristic algorithms. Luniver press._

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](../master/LICENSE) file for details.
