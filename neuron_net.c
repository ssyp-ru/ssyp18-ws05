//1234567890-=
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "neuron_net.h"
#include <math.h>
#define A 0.05

struct neuron* create_neuron(int length_prev)
{
	struct neuron* neuron = (struct neuron*)malloc(sizeof(struct neuron));
	neuron->length_prev = length_prev;
	double RAND_MAX_F = RAND_MAX;

	if (length_prev == 0)
	{
		neuron->weight = NULL;
	}
	else
	{
		neuron->weight = (double*)malloc(length_prev * sizeof(double));
	}

	for (int i = 0; i < length_prev; i++)
	{
		neuron->weight[i] = rand() / RAND_MAX_F*2-1;
	}

	neuron->b = rand() / RAND_MAX_F * 2 - 1;

	return neuron;
}

void delete_neuron(struct neuron* neuron)
{
	free(neuron->weight);
	free(neuron);
}

struct layer* create_layer(int length_prev, int length_now)
{

	struct layer* layer = (struct layer*)malloc(sizeof(struct layer));
	layer->neurons = (struct neuron**)malloc(length_now*sizeof(struct neuron*));
	layer->length = length_now;

	for (int i=0; i < layer->length; i++)
	{
		layer->neurons[i] = create_neuron(length_prev);
	}
	return layer;
}

void delete_layer(struct layer* layer)
{

	for (int i = 0; i < layer->length; i++)
	{
		delete_neuron(layer->neurons[i]);
	}

	free(layer->neurons);
	free(layer);
}

struct neural_network* create_n_network(int length_first, int length_last, int length_middle, int number)
{
	struct  neural_network* neural_network = (struct neural_network*)malloc(sizeof(struct neural_network));
	neural_network->layers = (struct layer**)malloc((number+2)*sizeof(struct layer*));

	neural_network->number_layers = number;
	neural_network->length_first = length_first;
	neural_network->length_last = length_last;
	neural_network->length_middle = length_middle;

	neural_network->layers[0] = create_layer(0, length_first);

	for (int i = 1; i < number+1; i++)
	{
		neural_network->layers[i] = create_layer(neural_network->layers[i-1]->length, length_middle);
	}

	neural_network->layers[number+1] = create_layer(neural_network->layers[number]->length, length_last);

	return neural_network;

}

void delete_neural_network(struct neural_network*  neural_n) {

	for (int i = 0; i <  neural_n->number_layers + 2; i++)
	{
		delete_layer(neural_n->layers[i]);
	}

	free(neural_n->layers);
	free(neural_n);

}

void calculate(struct neural_network* neural_network)
{
	for (int i = 1; i < neural_network->number_layers+2 ; i++)
	{
		for (int j = 0; j < neural_network->layers[i]->length; j++)
		{
			double summ=0;
			for (int k = 0; k < neural_network->layers[i]->neurons[j]->length_prev; k++)
			{
				summ += neural_network->layers[i]->neurons[j]->weight[k]* neural_network->layers[i-1]->neurons[k]->value;
			}
			neural_network->layers[i]->neurons[j]->sum = summ;

			neural_network->layers[i]->neurons[j]->value = activ_fun(neural_network, i, j)-0.5;
		}

	}
}

void file_print(struct neural_network* neural_network, const char* file_name)
{
    struct neural_network *abc = (struct neural_network*) neural_network;
	FILE*f = fopen(file_name, "w");

	fprintf(f, "%d\n", abc->length_first);
	fprintf(f, "%d\n", abc->length_last);
	fprintf(f, "%d\n", abc->length_middle);
	fprintf(f, "%d\n", abc->number_layers);

	for (int i = 1; i < abc->number_layers + 2; i++)
	{
		for (int j = 0; j < abc->layers[i]->length; j++)
		{
			for (int r = 0; r < abc->layers[i]->neurons[j]->length_prev; r++)
			{
				fprintf(f, "%2f ", abc->layers[i]->neurons[j]->weight[r]);
			}
			fprintf(f, "\n%2f\n", abc->layers[i]->neurons[j]->b);
		}
		if (i == abc->number_layers + 1)
		{
			fprintf(f, "-----------------\n");
			for (int r = 0; r < abc->layers[i]->length; r++)
			{
				fprintf(f, "%2f ", abc->layers[i]->neurons[r]->value);
			}
		}
	}
	fclose(f);
}

struct neural_network* file_read(const char* file_name)
{
	FILE*g = fopen(file_name, "r");

	int length_first, length_last, length_middle, number_layers;

	fscanf(g, "%d %d %d %d", &length_first, &length_last, &length_middle, &number_layers);

	struct neural_network* neural_network = create_n_network(length_first, length_last, length_middle, number_layers);

	for (int i = 1; i < neural_network->number_layers + 2; i++)
	{
		for (int j = 0; j < neural_network->layers[i]->length; j++)
		{
			for (int r = 0; r < neural_network->layers[i]->neurons[j]->length_prev; r++)
			{
				fscanf(g, "%lf", &neural_network->layers[i]->neurons[j]->weight[r]);
			}
			fscanf(g, "%lf", &neural_network->layers[i]->neurons[j]->b);
		}
	}
	fclose(g);

	return neural_network;
}

void n_last_delta(struct neural_network* nn,double* exp_value)
{
	for (int i = 0; i < nn->layers[nn->number_layers + 1]->length; i++)
	{
		nn->layers[nn->number_layers + 1]->neurons[i]->delta =
			(nn->layers[nn->number_layers + 1]->neurons[i]->value - exp_value[i]) *
			activ_pr_fun(nn, nn->number_layers + 1, i);
	}
}

void n_delta(struct neural_network* nn,double coef)
{
	double delta_weight_next=0;
	for (int i = nn->number_layers; i > 0; i--)
	{
		for (int j = 0; j < nn->layers[i]->length; j++)
		{
			delta_weight_next = 0;
			for (int r = 0; r < nn->layers[i+1]->length; r++)
			{
				delta_weight_next += nn->layers[i + 1]->neurons[r]->delta *
				nn->layers[i + 1]->neurons[r]->weight[j] *
				activ_pr_fun(nn,i,j);
			}
			nn->layers[i]->neurons[j]->delta = delta_weight_next;
		}
	}
	update_w(nn, coef);
}

void update_w(struct neural_network* nn,double coef)
{
    double max_update = 0;
	for (int i = 1; i < nn->number_layers+1; i++)
	{
		for (int j = 0; j < nn->layers[i]->length; j++)
		{
			for (int n = 0; n < nn->layers[i - 1]->length; n++)
			{
				double d = -coef *
					nn->layers[i]->neurons[j]->delta *
					nn->layers[i - 1]->neurons[n]->value;
                if(fabs(d) > max_update) max_update = fabs(d);
				nn->layers[i]->neurons[j]->weight[n] += d;
			}
			nn->layers[i]->neurons[j]->b += -coef *
				nn->layers[i]->neurons[j]->delta;
		}
	}
	printf("max update: %lf\n", max_update);
}

double activ_fun(struct neural_network* nn,int layer,int neuron)
{
	return 1 / (1 + exp(-1 * A*nn->layers[layer]->neurons[neuron]->sum));
}

double activ_pr_fun(struct neural_network* nn, int layer, int neuron)
{
	return A * activ_fun(nn, layer, neuron)*(1 - activ_fun(nn, layer, neuron));
}
