# See just the testing on ezMNIST without training.                             Run it: "apt install geany python3-torch". Open the .py in Geany.
#                                                                               Replace "python" with "python3" in Geany's execute command. F5 to run.

import torch
import torch.nn as nn
import torch.optim as optim

# Grabs 2 numbers from a text file created by C++, in order to set number_of_layers and neurons_per_layer.
with open('Model/Python/depth_width.txt', 'r') as f: number_of_layers, neurons_per_layer = (int(line.strip()) for line in f)

# This is needed to create/save/load model.
model = nn.Sequential(); model.add_module         ('input',       nn.Linear(              784, neurons_per_layer)); model.add_module('relu1',     nn.ReLU());
for a in range(number_of_layers): model.add_module(f'hidden_{a}', nn.Linear(neurons_per_layer, neurons_per_layer)); model.add_module(f'relu_{a}', nn.ReLU());
model.add_module                                  ('output',      nn.Linear(neurons_per_layer,                10))

# Loads model from file.
model.load_state_dict(torch.load('Model/Model.pth', map_location='cpu'))

# Gets number of items to test on.
with open('ezMNIST/test-ezMNIST.txt', 'rb') as f: total_testing_data_items = f.read().count(10)

# Tests model.
print("\n", end='')
with open('results.txt', 'w') as f: pass # Empty file.
model.eval()
in_stream = open('ezMNIST/test-ezMNIST.txt', 'rb')
misclassified = 0
for a in range(total_testing_data_items):
	print("Testing on test-ezMNIST.txt line", (a + 1), "of", total_testing_data_items)
	
	# Expected classification.
	file_byte = in_stream.read(1); expected_classification = (file_byte[0] - 48);
	
	# Data to be classified.
	normalized = [0.0] * 784; normalized_write_bookmark = 0;
	file_byte = in_stream.read(1); file_byte = in_stream.read(1); integer = file_byte[0];
	while integer != 10:
		if integer == 64: normalized[normalized_write_bookmark] = 1.0
		normalized_write_bookmark += 1;
		file_byte = in_stream.read(1);
		integer = file_byte[0]
	input_data = torch.tensor(normalized).view(1, 784)
	
	# Uses model.
	with torch.no_grad():
		outputs = model(input_data) # Forward pass.
		_, predictions = torch.max(outputs, 1)
	
	# Appends classification to file results.txt.
	classification = predictions[0].item()
	with open('results.txt', 'a') as f: f.write(f"{classification}\n")
	
	# Checks if misclassified.
	if classification != expected_classification: misclassified += 1
in_stream.close()

print("\nMisclassifies", misclassified, "out of", total_testing_data_items, "(see results.txt)\n")
percent_correct = format((((total_testing_data_items - misclassified) / total_testing_data_items) * 100), ".15f")
print(percent_correct, end='% correct.')
