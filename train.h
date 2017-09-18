// Training Algorithm


void train (int input_size, double input[], double des_output, int training_steps)
{

	for ( hstep = 0; hstep < training_steps; hstep ++ )
	{
		
		output = 0;
		current_layer = 0;

		// read in input to first layer

		for ( jstep = 0; jstep < layer_size; jstep ++ )
		{

			neuron[0][jstep] = input[jstep];

		}


		// reset deltas and neurons

		for ( istep = 1; istep < layers; istep ++ )
		{

			for ( jstep = 0; jstep < layer_size; jstep ++ )
			{

				neuron[istep][jstep] = 0;

				delta[istep][jstep] = 0;

			}

		}

		for ( jstep = 0; jstep < layer_size; jstep ++ )
		{

			delta[layers][jstep] = 0;

		}


		//* Feed Forward input  *//
		
		while ( current_layer < ( layers - 1 ) )
		{

			for ( istep = 0; istep < layer_size; istep ++ )
			{

				receiving_layer = current_layer + 1;

				pre_neuron [current_layer][istep] = neuron [current_layer][istep];


				// Apply activation function

				if ( current_layer != 0 )
				{

					neuron [current_layer][istep] = 1 / ( 1 + exp ( - sig_factor * ( neuron [current_layer][istep] ) ) );      // Sigmoidal Activation Function
			
				}

				while ( receiving_layer < layers )
				{

					for ( jstep = 0; jstep < layer_size; jstep ++ )
					{

						// weight signal by connection strength and send to a higher layer to be added to neuron activation input

						neuron [receiving_layer][jstep] = neuron [receiving_layer][jstep] + connections [current_layer][receiving_layer][istep][jstep] * neuron [current_layer][istep];
						
						output = output +  connections [current_layer][layers][istep][0] * neuron [current_layer][istep];

					}
				
					receiving_layer ++;

				}

			}

			current_layer ++;	
			
		}


		for (jstep = 0; jstep < layer_size; jstep ++ )
		{
			pre_neuron[layers][jstep] = output;

		}


		// Apply Output Function and check 

		output = 1 / ( 1 + exp ( - sig_factor * output ) );      // Sigmoidal Function

		// cout << output << endl;

 
		delta[layers][0] = des_output - output;

		current_layer = layers;


		//* Back Propagation of Error *//

		// Back propagate delta

		while ( current_layer > 1 )
		{

			for ( istep = 0; istep < layer_size; istep ++ )
			{	
					
				receiving_layer = current_layer - 1;

				while ( receiving_layer >= 1 )
				{
				
						for ( jstep = 0; jstep < layer_size; jstep ++ )
						{

							// deltas back propagate in exactly the same way that the signal forward propagates

							delta[receiving_layer][jstep] = delta[receiving_layer][jstep] + connections[receiving_layer][current_layer][jstep][istep]*delta[current_layer][istep];
										
						}


					receiving_layer --;	

				}

			}

			current_layer --;			
		
		}


		//  Feedforward change in connection strengths

		current_layer = 0;

		while ( current_layer < ( layers - 1 ) )
		{

			for ( istep = 0; istep < layer_size; istep ++ )
			{

				receiving_layer = current_layer + 1;

				while ( receiving_layer < layers )
				{

					for ( jstep = 0; jstep < layer_size; jstep ++ )
					{

						// Alter connection strengths based on deltas

						connections[current_layer][receiving_layer][istep][jstep] = connections[current_layer][receiving_layer][istep][jstep] + learning_factor * delta[receiving_layer][jstep] * ( 1 / ( 1 + exp ( - sig_factor * pre_neuron[receiving_layer][jstep]) ) ) * ( 1 -( 1 / ( 1 + exp ( - sig_factor * pre_neuron[receiving_layer][jstep] ) ) ) ) * neuron[current_layer][istep];
						
					}
				
					receiving_layer ++;

				}

			}

			current_layer ++;	
			
		}

	}

}
	