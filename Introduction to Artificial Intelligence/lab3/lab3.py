import numpy as np
from lab3_utils import edit_distance, feature_names

# please note the analysis is mentoned in result_analysis


# its a debugging function used to print any dimesional array's contents.
def print_any(arr):
    for i in range(len(arr)):
        print(arr[i])


# it is used to get max of the given feature in the given input.
def get_max_of_all_features(arr):

    max_of_all_features = []

    # iterates over how many features we have.
    for j in range(len(feature_names)):
        res = []
        # iterates over the array of the input of given column and it will help us to find mode of that feature.
        for i in range(len(arr)):
            res.append(arr[i][j])
        actual = np.array(res)
        values, counts = np.unique(actual.astype(str), return_counts=True)
        max_of_all_features.append(values[np.argmax(counts)])

    return max_of_all_features


# it is used to remove the values with ? with mode of the feature as mentioned in pre-processing step.
def removing_blank_values(arr, max_of_all):

    # it is iterating the length of array and finding missing values and replacing them from
    for i in range(len(arr)):
        curr = arr[i]
        for i in range(len(curr)):
            if (curr[i] == '?'):
                curr[i] = max_of_all[i]


# it is used to replacing the ordinal features with integral values.
def dealing_features(arr):

    # iterating over each input element and changing the values with necessary values.
    for i in range(len(arr)):
        curr = arr[i]
        curr[curr == '0-2'] = 1
        curr[curr == '3-5'] = 2
        curr[curr == '6-8'] = 3
        curr[curr == '9-11'] = 4
        curr[curr == '12-14'] = 5
        curr[curr == '15-17'] = 6
        curr[curr == '18-20'] = 7
        curr[curr == '21-23'] = 8
        curr[curr == '24-26'] = 9
        curr[curr == '27-29'] = 10
        curr[curr == '30-32'] = 11
        curr[curr == '33-35'] = 12
        curr[curr == '36-39'] = 13
        curr[curr == '0-4'] = 1
        curr[curr == '5-9'] = 2
        curr[curr == '10-14'] = 3
        curr[curr == '15-19'] = 4
        curr[curr == '20-24'] = 5
        curr[curr == '25-29'] = 6
        curr[curr == '30-34'] = 7
        curr[curr == '35-39'] = 8
        curr[curr == '40-44'] = 9
        curr[curr == '45-49'] = 10
        curr[curr == '50-54'] = 11
        curr[curr == '55-59'] = 12
        curr[curr == '10-19'] = 1
        curr[curr == '20-29'] = 2
        curr[curr == '30-39'] = 3
        curr[curr == '40-49'] = 4
        curr[curr == '50-59'] = 5
        curr[curr == '60-69'] = 6
        curr[curr == '70-79'] = 7
        curr[curr == '80-89'] = 8
        curr[curr == '90-99'] = 9
        curr[curr == 'yes'] = 1
        curr[curr == 'no'] = 0
        curr[curr == 'left'] = 0
        curr[curr == 'right'] = 1


# it replaces the menopuse feature with one-hot encoding.
def replacing_meno(arr):

    res = []
    for i in range(len(arr)):
        curr_res = [arr[i][0]]
        curr = arr[i][1]
        if (curr == 'lt40'):
            curr_res.append(1)
            curr_res.append(0)
            curr_res.append(0)
        elif (curr == 'ge40'):
            curr_res.append(0)
            curr_res.append(1)
            curr_res.append(0)
        elif (curr == 'premeno'):
            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(1)

        for j in range(2, len(arr[i])):
            curr_res.append(arr[i][j])

        curr_res = np.array(curr_res, dtype=object)

        res.append(curr_res)

    res = np.array(res, dtype=object)

    return res


# it is used to replace the input array with breast_quad feature to one-hot encoding as mentioned in instructions.
def replacing_breast_quad(arr):
    res = []
    for i in range(len(arr)):
        curr_res = [arr[i][j] for j in range(0, 9)]
        curr = arr[i][9]
        if (curr == 'left_up'):

            curr_res.append(1)
            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(0)

        elif (curr == 'left_low'):

            curr_res.append(0)
            curr_res.append(1)
            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(0)

        elif (curr == 'right_up'):

            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(1)
            curr_res.append(0)
            curr_res.append(0)

        elif (curr == 'right_low'):

            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(1)
            curr_res.append(0)

        elif (curr == 'central'):

            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(0)
            curr_res.append(1)

        curr_res.append(arr[i][10])

        curr_res = np.array(curr_res, dtype=object)

        res.append(curr_res)

    res = np.array(res, dtype=object)

    return res


# Hint: Consider how to utilize np.unique()
# provided function which processes the testing and training data.
def preprocess_data(training_inputs, testing_inputs, training_labels, testing_labels):
    processed_training_inputs, processed_testing_inputs = ([], [])
    processed_training_labels, processed_testing_labels = ([], [])
    # VVVVV YOUR CODE GOES HERE VVVVV $
    # These lines of code are mere implementation of functions mentioned above.
    mode_of_all = get_max_of_all_features(training_inputs)
    removing_blank_values(training_inputs, mode_of_all)

    mode_of_all_test = get_max_of_all_features(testing_inputs)
    removing_blank_values(testing_inputs, mode_of_all_test)

    dealing_features(training_inputs)
    act_res = replacing_meno(training_inputs)
    processed_training_inputs = replacing_breast_quad(act_res)

    dealing_features(testing_inputs)
    test_res = replacing_meno(testing_inputs)
    processed_testing_inputs = replacing_breast_quad(test_res)

    processed_training_labels = training_labels

    processed_testing_labels = testing_labels

    # ^^^^^ YOUR CODE GOES HERE ^^^^^ $
    return processed_training_inputs, processed_testing_inputs, processed_training_labels, processed_testing_labels


# Hint: consider how to utilize np.argsort()
def k_nearest_neighbors(predict_on, reference_points, reference_labels, k, l, weighted):
    assert len(
        predict_on) > 0, f"parameter predict_on needs to be of length 0 or greater"
    assert len(
        reference_points) > 0, f"parameter reference_points needs to be of length 0 or greater"
    assert len(
        reference_labels) > 0, f"parameter reference_labels needs to be of length 0 or greater"
    assert len(reference_labels) == len(reference_points), f"reference_points and reference_labels need to be the" \
                                                           f" same length"
    predictions = []
    # VVVVV YOUR CODE GOES HERE VVVVV $

    for i in range(len(predict_on)):
        distance_calc = []
        # calculates distance of each testing instance with all training instances.
        for j in range(len(reference_points)):

            res = edit_distance(predict_on[i], reference_points[j], l)

            distance_calc.append(res)

        distance_calc = np.array(distance_calc)
        arr = np.argsort(distance_calc)

        no_recursion_events, recursion_events = 0, 0

        for d in range(k):  # finds k nearest neighbors.
            if (reference_labels[arr[d]] == 'no-recurrence-events'):
                no_recursion_events += 1
            elif (reference_labels[arr[d]] == 'recurrence-events'):
                recursion_events += 1

        # used to break ties of recurrence or no-recurrence events.
        if (recursion_events >= no_recursion_events):
            predictions.append('recurrence-events')
        else:
            predictions.append('no-recurrence-events')

    # ^^^^^ YOUR CODE GOES HERE ^^^^^ $
    return predictions
