// Main Neural Network Source

// Blake Leonard
// 2012


#include <iostream>
using namespace::std;

#include <fstream>
using namespace::std;

#include <cmath>
using namespace::std;

#include <ctime>
using namespace::std;


// Global Variables

const int layers = 3;               // Including input layer, but not output           
const int layer_size = 300;
const int inp_size = 300;
const int max_data_pts = 1;

double learning_factor = 0.5;
double learning_factor_change = 0.9999995;
double sig_factor = 0.02;

const int global_training_steps = 2000;
int print_steps = 100;

double pre_neuron[layers][layer_size];
double neuron[layers][layer_size];
double output;
double delta[layers+1][layer_size]; 
double error[max_data_pts];
bool break_flag = 0;

double connections[layers][layers+1][layer_size][layer_size];

int hstep, istep, jstep, kstep, dstep, tstep, zstep, current_layer, receiving_layer;

double desired_output[max_data_pts+1];
double input_pts[max_data_pts][inp_size];
double training_input[inp_size];
double run_input[inp_size];


#include "train.h"
using namespace::std;

#include "randconnections.h"
using namespace::std;


void main()
{

    // Generate initial random connection array

    randconnections();


    // Enter Data

	for ( istep = 0; istep < max_data_pts; istep ++ )
	{

		for ( jstep = 0; jstep < inp_size; jstep ++)
		{

				input_pts[istep][jstep] = 1 + 0.5 * sin( jstep * ( 2 * 3.141592 / inp_size ) ) ; // + istep * 0.005;

		}


		desired_output[istep] = 1 + 0.5 * sin( inp_size * ( 2 * 3.141592 / inp_size ) );
		
	}


	desired_output[max_data_pts] = 1 + 0.5 * sin( ( inp_size + 1 ) * ( 2 * 3.141592 / inp_size ) );

	
	for ( istep = 0; istep < inp_size; istep ++ )
	{

		run_input[istep] = 1 + 0.5 * sin( ( istep + 1 ) * ( 2 * 3.141592 / inp_size ) );
	
	}

	
	// Train on data

	for ( tstep = 0; tstep < global_training_steps; tstep ++ )
	{

		learning_factor = learning_factor * learning_factor_change;

		for ( dstep = 0; dstep < max_data_pts; dstep ++ )
		{

			for ( zstep = 0; zstep < inp_size; zstep ++ )
			{

				training_input[zstep] = input_pts [dstep][zstep];

			}

			train( inp_size, training_input, desired_output[dstep], 1);

		}

		cout << delta[layers][0] << endl;

		if ( ( ( delta[layers][0] ) <= 0.0001 ) & ( ( delta[layers][0] ) >= ( - 0.0001)  ) )
		{
			break;

		}
		
	}

	train( inp_size, run_input, desired_output[max_data_pts], 1);

	cout << endl << "input: " << run_input[0] << "		" << "output: " << output << endl;
 


	return;

}