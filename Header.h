#pragma once
#include <cmath>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <random>
double Function(double x) {
	return cos(x) + log10(x);
}

double ModifiedFun(double x) {
	return sin(5 * x) * Function(x);
}

double CoolingTemperature(double Current) {
	return Current * 0.95;
}

double CalcDifference(double function(double x),double x1, double x2) {
	return function(x1) - function(x2);
}

double P(double diff, double temperature) {
	return exp(-diff / temperature);
}

int GetRandomFromRange(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	srand(std::chrono::steady_clock::now().time_since_epoch().count());
	return static_cast<int>(rand() * fraction * (max - min) + min);
}

double average_distance(const std::vector<int>& permutation) {
	double distance_sum = 0;

	for (int i = 0; i < 1000; i++)
		distance_sum += abs(permutation[i] - i);

	return distance_sum / 1000;
}

double NumberConstructor(int a, int b, int number) {
	double result = number;
	while (result >= 1) {
		result /= 10;
	}
	int temp = GetRandomFromRange(a, b);
	if (temp == b) {
		temp -= 1;
	}
	return temp + result;
}

double RandomNumberGenerator(int a, int b) {
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::vector<int> permutation(1000);

	for (int i = 0; i < 1000; i++)
		permutation[i] = i;
	shuffle(permutation.begin(), permutation.end(), rng);
	double part1 = average_distance(permutation);
	shuffle(permutation.begin(), permutation.end(), rng);
	double part2 = average_distance(permutation);
	int index = permutation[(abs(a) + abs(b) + 1) % 1000] + 1;
	double a_ = part1 * part2;
	int b_ = ceil(a_);
	int result = b_ % index;
	return NumberConstructor(a, b, result);
}

bool ChanceToChange(double diff, double temperature) {
	double Probability = P(diff, temperature);
	double RandomNumber = RandomNumberGenerator(0, 1);
	if (RandomNumber > Probability) {
		return false;
	}
	else {
		return true;
	}
}

bool RateDifference(double diff) {
	if (diff <= 0) {
		return true;
	}
	else {
		return false;
	}
}


void SA(double function(double x), int a, int b , double Tmax , double Tmin) {
	//double xmin = 0;
	int attempt = 1;
	double xmin = RandomNumberGenerator(a, b);
	double Tcurrent = Tmax;
	std::cout<<std::left << 'N' << ' ' << std::setw(7) << "Temper" << ' ' << std::setw(7) << 'x' << ' '
		<< std::setw(7) << "f(x)" << std::endl;
	while (Tcurrent > Tmin) {
		double x2 = RandomNumberGenerator(a, b);
		double difference = function(x2) - function(xmin);
		if (RateDifference(difference)) {
			xmin = x2;
		}
		else {
			if (ChanceToChange(difference, Tcurrent)) {
				xmin = x2;
			}
		}
		Tcurrent = CoolingTemperature(Tcurrent);
		std::cout<<std::left << attempt++ << ' '<< std::setw(7) << Tcurrent << ' ' << std::setw(7)<<xmin << ' ' << std::setw(7) <<function(xmin) << std::endl;
	}
}