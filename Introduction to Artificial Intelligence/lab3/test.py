from lab3_utils import (
    accuracy_score,
    load_data
)
from lab3 import k_nearest_neighbors, preprocess_data
import numpy as np
import time
# from tabulate import tabulate #uncomment this line as it will be needed if you want to see the result that I put in pdf file.


if __name__ == "__main__":
    print(f"Loading data from file...")
    start_time = time.time()
    raw_data = load_data()
    load_time = time.time() - start_time
    print(f"Data loaded - time elapsed from start: {load_time:0.9f}")
    print(f"Beginning data preprocessing and cleaning...")
    processed_training_inputs, processed_testing_inputs, processed_training_labels, processed_testing_labels =\
        preprocess_data(*raw_data)
    load_time = time.time() - start_time
    print(f"Data preprocessed - time elapsed from start: {load_time:0.9f}")
    print(
        f"Example training input: {processed_training_inputs[0]} - label: {processed_training_labels[0]}")
    l_norms = [-1, 1, 2, 3, 4, 5, 6, np.inf]
    k_max = 30
    # relationship = []  # used to calculate analysis. uncomment this if you want to see table in the pdf.
    weighting_options = [True, False]
    accuracies = np.zeros((k_max, len(l_norms), len(weighting_options)))
    for k in range(1, k_max+1):
        for l_i, l_norm in enumerate(l_norms):
            for w, weighting in enumerate(weighting_options):
                print(
                    f"Running kNN with k= {k}, l= {l_norm}, weighting={weighting}")
                predicted_labels = k_nearest_neighbors(
                    predict_on=processed_testing_inputs,
                    reference_points=processed_training_inputs,
                    reference_labels=processed_training_labels,
                    k=k,
                    l=l_norm,
                    weighted=weighting
                )
                load_time = time.time() - start_time
                print(
                    f"kNN completer - time elapsed from start: {load_time:0.9f}")
                # it will be used for analysis consiting of k, l, weighting and accuracy.
                #uncomment line 46 to 53 to see table in pdf.
                # entry = []
                # entry.append(k)
                # entry.append(l_norm)
                # entry.append(weighting)
                # entry.append(accuracy_score(
                #     processed_testing_labels, predicted_labels))
                # relationship.append(entry)
                accuracies[k-1, l_i, w] = accuracy_score(
                    processed_testing_labels, predicted_labels)

    best_accuracy = np.max(accuracies)
    best_k, best_metric, best_weighting = np.where(accuracies == best_accuracy)
    print(f"Highest accuracy achieved: {best_accuracy:0.4f}")
    for k, l, w in zip(best_k, best_metric, best_weighting):
        print(
            f"\t k= {k+1} - l= {l_norms[l]} - weighting= {weighting_options[w]}]")

    #uncomment lines to print the table of results followed by neccesary uncomments from line 65 to 66
    # print('\n')
    # print(tabulate(relationship, headers=['k', 'L',
    #       'Weighted', 'Accuracy Score'], tablefmt='grid'))  # prints table of the analysis of each l for a given k alogn with weighted or not weighted
