// Generate Array of random connections

// Blake Leonard
// 2012


void randconnections ( void )
{
	srand(time(0));

	current_layer = 0;
	
	while ( current_layer < layers )
	{

		receiving_layer = current_layer + 1;

		while ( receiving_layer <= layers )
		{
			
			for ( istep = 0; istep < layer_size; istep ++ )
			{	
					
				for ( jstep = 0; jstep < layer_size; jstep ++ )
				{
				
					// Generate random connection strengths between -1 and 1

					connections[current_layer][receiving_layer][istep][jstep] = 0.05 * ( 2 * ( (float)rand() / (float)RAND_MAX ) - 1 );
					
				}

			}

			receiving_layer ++;	

		}

		current_layer ++;
		
	}
			
}

