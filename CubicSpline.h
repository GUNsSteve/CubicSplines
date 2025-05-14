#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Eigen/Dense"
using std::string;

class cubicSpline {
public:
	double divDiff(int i) {
		return(y[i+1]-y[i])/(x[i+1]-x[i]);
	}
	void initialize(std::vector<double> x, std::vector<double> y) {
		this->x = x;
		this->y = y;
		n = x.size();
		a.resize(n);
		b.resize(n);
		c.resize(n);
		d.resize(n);
		Mat1 = Eigen::MatrixXd::Zero(n,n);
		Diff.resize(n);



		//populate matrix and vector

		for (int i = 0; i < n ; i++) {
			
			if (i == 0) {
				Diff(i) = 0;
			}
			else if (i == (n - 1)) {
				Diff(i) = 0;
			}
			else {
					Diff(i) = 3 * (divDiff(i) - divDiff(i - 1));
				}
				for (int j = 0; j < n; j++) {
					//first data
					if (i == 0 && j == 0) {
						Mat1(i, i) = 1;
					}
					//last data
					else if (i == n-1 && j == n-1) {
						Mat1(i, i) = 1;
					}
					//populate 3 diagonals
					else if (j == i && i != 0 && i!= n-1) {
						Mat1(j, i) = 2 * (x[j] - x[j - 1] + x[j + 1] - x[j]);
						std::cout << "middle diagonal " << i << " =" << Mat1(j,i)<<"\n";
						Mat1(j , i-1) = x[j] - x[j - 1];
						std::cout << "left diagonal " << i << " =" << Mat1(j-1, i) << "\n";
						Mat1(j , i+1) = x[j + 1] - x[j];
						std::cout << "right diagonal " << i << " =" << Mat1(j + 1, i) << "\n";
					}

					
			}
				std::cout << Diff(i)<< "\n";

		}
		//solve matrix
		std::cout << "Completed population:\n";
		std::cout <<Mat1<<"\n";
		std::cout << Diff<<"\n";
		coeffans = Mat1.colPivHouseholderQr().solve(Diff);
		std::cout << "Completed solution\n";





		for (int i = 0; i < n-1 ; i++) {
			





			a[i] = y[i];
			b[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (x[i + 1] - x[i]) * (2 * coeffans(i) + coeffans(i + 1)) / 3;
			d[i] = (coeffans(i+1)-coeffans(i)) / 3*(x[i + 1] - x[i]);
		}


	}
	double interpolate(double val) {
		for (int i = 0; i < n-1; i++) {
			if (val >= this->x[i] && val <= this->x[i + 1]) {
				return(		  a[i] + b[i] * (val - x[i])
							+ coeffans(i) * (val - x[i]) * (val - x[i])
							+ d[i] * (val - x[i]) * (val - x[i]) * (val - x[i])		
					  );

			}
		}
	}
	string getEquation() {
		std::string equation = "\0";
		for (int i = 0; i < n - 1; i++) {
			equation += std::to_string(a[i]) + " + " + 
				(std::to_string(b[i])) +" * (x - "+(std::to_string(x[i])) + ") + " + 
				(std::to_string(coeffans(i))) + "(x - " + (std::to_string(x[i])) + ")^2 +" + 
				(std::to_string(d[i])) + "(x - " + (std::to_string(x[i])) + ")^3 +" + 
				" When x is between: " + (std::to_string(x[i])) + " and " + (std::to_string(x[i + 1])) + "\n";
		}
		return equation;
	}
private:
	size_t n;						//size of array
	std::vector<double> x;			//input data x
	std::vector<double> y;			//input data y
	std::vector<double> a;			//constant
	std::vector<double> b;			//1st degree
	std::vector<double> c;			//2nd degree
	std::vector<double> d;			//3rd degree
	Eigen::MatrixX<double> Mat1; //Matrix to solve 
	Eigen::VectorX<double> Diff; //Other part of matrix equation
	Eigen::VectorX<double> coeffans; //Coefficient answers
};
