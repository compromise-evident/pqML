# Create a new model and save it as one file.                                   Run it: "apt install geany python3-torch". Open the .py in Geany.
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

# Saves model to file.
torch.save(model.state_dict(), 'Model/Model.pth')
print("\nModel.pth saved with hidden layers:  ", number_of_layers, "deep,", neurons_per_layer, "wide.")
