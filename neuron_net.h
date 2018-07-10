#pragma once

struct neuron {
	double* weight;
	int length_prev;
	double value;
	double b,delta,sum;
};

struct neuron* create_neuron(int length_prev);

void delete_neuron(struct neuron* neuron);

struct layer {
	struct neuron** neurons;
	int length;
};

struct layer* create_layer(int length_prev, int length_now);

void delete_layer(struct layer* layer);

struct neural_network {
	struct layer** layers;
	int number_layers;
	int length_first;
	int length_last;
	int length_middle;
};

struct neural_network* create_n_network(int length_first, int length_last, int length_middle, int number);
;
void delete_neural_network(struct neural_network*  neural_n);

void calculate(struct neural_network* neural_network);

void file_print(struct neural_network* neural_network,const char* file_name);

struct neural_network* file_read(const char* file_name);
//new
void update_w(struct neural_network* nn, double coef);

double activ_fun(struct neural_network* nn, int layer, int neuron);

double activ_pr_fun(struct neural_network* nn, int layer, int neuron);

void n_delta(struct neural_network* nn, double numneuron);

void n_last_delta(struct neural_network* nn, double *exp_value);