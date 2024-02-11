[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/paQtCn_S)
# Lab 5: Implement Machine Learning Algorithm with Sklearn

**CSCI 360: Introduction to Artificial Intelligence**
# Note for the grader:
In this assignment I did only p1 and p2 and they have file names as p1.ipynb and p2.ipynb respectively.
## Introduction
In this lab you will be implementing three basic machine learning algorithms in Python using famous package [sklearn](https://scikit-learn.org/stable/). In this lab, we do not provide skeleton code while you are provided with abundant examples online. Please list all packages including `numpy` and `sklearn` in `requirements.txt` along with version number you are using. Save your implementation and necessary files (dataset and plots) in the respective folder of three problems.

## Logistics
### Naming scripts
In folder of each problem, make sure you name the first/main script to run your implementation as `main.py` or `main.ipynb` (for Jupyter Notebook). Also, make sure your implementation can run with only scripts in that folder besides python libraries installed in environment. For example, in `main.py` of `p1`, do not cross reference/import scripts from `p2` or `p3`. You can copy all helper scripts/functions into the other folders.

### Jupyter Notebook or Regular .PY
As in instruction, you are encouraged to use Jupyter Notebook because it allows you to save and visualize intermediate results. However, we also accept regular .py scripts in implementation. Please make sure you list all extensive packages and their versions in `requirements.txt`.

### Is there an extra credit?
Different from labs before, Lab 5 does not have an extra credit problem while the three problems worth 150 points. This means, we will cap your raw score (out of 150) to 100 points as final score. We hope you work on all three problems as a good practice. (*You know, machine learning is inevitable today ...*)

## How we will grade
__IMPORTANT:__ You need to show intermediate results of each step besides final result. You need to determine the way to present unless already specified in instruction. For example, you can report train error using simple printout, or drawing a figure to present decision tree. Make sure you clearly label what to print ("train error: XXX") or plot (as figure title). We will give partial credits for intermediate steps.

### Problem 1: Perceptron Learning for the Iris Dataset (50 pts)
- (10 pts) Load iris dataset in sklearn.
- (5 pts) Merge virginica and versicolor classes. You can show number of data points and categories (using `np.unique`) before and after merge.
- (5 pts) Segment data into training set and test set.
- (15 pts) Train a Perceptron on training data.
- (10 pts) Test on test data.
- (5 pts) Report training and test error.

### Problem 2: Decision Trees as Interpretable Models (50 pts)
- (5 pts) Reuse loaded dataset from Problem 1.
- (15 pts) Build a decision tree on the training set.
- (5 pts) Plot the decision tree.
- (15 pts) Convert the decision rules into a set of IF-THEN rules.
- (10 pts) Test the decision tree on test set and report the test error.

### Problem 3: Feedforward Neural Networks for Regression (50 pts)
- (5 pts) Download [dataset](http://archive.ics.uci.edu/ml/datasets/Concrete+Compressive+Strength) and select the first 730 data points as the training set and the last 300 points as the test set.
- (10 pts) Implement a neural network using a single layer with `early-stopping=False`.
- (15 pts) Find the optimal configurations to the neural network through trail and error methodology. You need to provide reasoning for your choice by reporting observation (test error) of different configurations.
- (10 pts) Train the network with `early-stopping=True` while all other configurations remain unchanged from last step.
- (5 pts) Write down your understanding of `early-stopping`. Note that your understanding should be analyzed from observations of previous steps. We will __not__ give points if you just search and copy interpretation online.
- (5 pts) Compare and report difference of performance between `early-stopping=True` and `early-stopping=False`.
