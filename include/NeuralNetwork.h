#pragma once
#include <vector>
#include <utility>
#include <string>

//input and output vectors
using input_and_output = std::pair <std::vector <double>, std::vector <double>>;

//list of input and output vectors
using list_of_inputs_and_outputs = std::vector <input_and_output>;

//pair containing list of matrices with ∂C/∂W for each weight and list of vectors with ∂C/∂B for each bias
using nabla_w_nabla_b = std::pair <std::vector <std::vector <std::vector <double>>>, std::vector <std::vector <double>>>;

//Neural network with sigmoid activation
class NeuralNetwork{
    private:
        std::vector <int> neurons_in_each_layer;                    //vector containing number of neurons in each layer
        std::vector <std::vector <std::vector <double>>> weights;   //vector containing weight matrices for all layers
        std::vector <std::vector <double>> biases;                  //vector containing bias vectors for all layers
        std::vector <std::vector <double>> activation_inputs;       //vector containing vectors of values, z, fed into the activation function, σ, for all layers
        std::vector <std::vector <double>> activations;             //vector containing activation vectors for all layers
        std::vector <double> costs;                                 //vector containing the costs for all training inputs
        std::vector <std::vector <double>> cost_derivatives;        //vector containing a list of the derivative of the cost function w.r.t. every output neuron for all training inputs
        int no_of_layers;                                           //number of layers
        
        //adjusts weights and biases for each mini batch then returns the average cost
        double stochastic_gradient_descent(list_of_inputs_and_outputs& mini_batch, double eta);

        //computes ∂C/∂W and ∂C/∂B for each training input/output
        nabla_w_nabla_b back_propagation(input_and_output& i_o);
        
        //reads weights and biases from a file previously generated by this program
        void read_from_file(std::string filename);

        //writes weights and biases to a file
        void write_to_file(std::string filename, double success_rate = -1);

        //returns random number
        static inline double random(double min, double max);

        //activation function, σ(Z)=1/(1+e^-Z)
        static inline double sigmoid(double z);

        //activation function derivative, σ'(Z)=(e^Z)/(e^Z + 1)²
        static inline double sigmoid_prime(double z);
    public:
        //Constructor
        //
        //Takes vector whose elements represent the number of neurons in the input and each layer after the input, then fills weights with random values and biases with zeros
        NeuralNetwork(std::vector<int> sizes, double min_random_weight = -0.5, double max_random_weight = 0.5);

        //Constructor
        //
        //Initializes weights, biases, number of layers, and size of each layer with data from a file
        NeuralNetwork(const char* file_to_read);

        //attempts to predict the output
        int feed_forward(std::vector <double>& inputs);
        
        //trains the network
        void train(list_of_inputs_and_outputs& training_set, int epochs, int mini_batch_size, double eta, std::string file_to_write = "");

        //trains the network, and tests it after each epoch
        void train(list_of_inputs_and_outputs& training_set, int epochs, int mini_batch_size, double eta, list_of_inputs_and_outputs& test_set, std::string file_to_write = "");
};