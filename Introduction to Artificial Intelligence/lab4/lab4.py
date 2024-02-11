import numpy as np
from lab4_utils import feature_names, accuracy_score

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

# it replaces the menopuse feature with numeric values as mentioned in instructions.
def replacing_meno(arr):

    for i in range(len(arr)):
        # curr_res = [arr[i][0]]
        curr = arr[i][1]
        if (curr == 'lt40'):
            arr[i][1] = 1
           
        elif (curr == 'ge40'):
            arr[i][1] = 2
            
        elif (curr == 'premeno'):
            arr[i][1] = 3

# it is used to replace the input array with breast_quad feature to numeric values as mentioned in instructions.
def replacing_breast_quad(arr):
    
    for i in range(len(arr)):
        
        curr = arr[i][7]
        if (curr == 'left_up'):
            arr[i][7] = 1
            

        elif (curr == 'left_low'):
            arr[i][7] = 2
           

        elif (curr == 'right_up'):
            arr[i][7] = 3
           

        elif (curr == 'right_low'):
            arr[i][7] = 4
            

        elif (curr == 'central'):
            arr[i][7] = 5
           
def processesor_labels(arr): #This functions is used to process the testing or training labels as numeric values.

    for i in range(len(arr)):

        if arr[i] == 'recurrence-events':
           arr[i] = 1
        elif  arr[i] == 'no-recurrence-events': 
            arr[i] = 0

# Hint: Consider how to utilize np.unique()
# provided function which processes the testing and training data.
def preprocess_data(training_inputs, testing_inputs, training_labels, testing_labels):
    processed_training_inputs, processed_testing_inputs = ([], [])
    processed_training_labels, processed_testing_labels = ([], [])
    # VVVVV YOUR CODE GOES HERE VVVVV $

    # These lines of code are mere implementation of functions mentioned above.
    mode_of_all = get_max_of_all_features(training_inputs)
    removing_blank_values(training_inputs, mode_of_all)
    dealing_features(training_inputs)
    replacing_meno(training_inputs)
    replacing_breast_quad(training_inputs)
    processesor_labels(training_labels)
    # print(training_labels)
    mode_of_all_test = get_max_of_all_features(testing_inputs)
    removing_blank_values(testing_inputs, mode_of_all_test)
    dealing_features(testing_inputs)
    replacing_meno(testing_inputs)
    replacing_breast_quad(testing_inputs)
    processesor_labels(testing_labels)

    processed_training_inputs = training_inputs
    processed_training_labels = training_labels
    processed_testing_inputs = testing_inputs
    processed_testing_labels = testing_labels

    # ^^^^^ YOUR CODE GOES HERE ^^^^^ $
    return processed_training_inputs, processed_testing_inputs, processed_training_labels, processed_testing_labels

def getting_index_of_recur(arr): #This function helps in getting indx of recurring values from training labels.

    res = []

    for i in range(len(arr)):
        if arr[i] != 0:
            res.append(i)
    
    return res

def getting_index_of_no_recur(arr): #This function helps in getting indx of no-recurring values from training labels.

    res = []

    for i in range(len(arr)):
        if arr[i] == 0:
            res.append(i)
    
    return res


# Hint: consider how to utilize np.count_nonzero()
def naive_bayes(training_inputs, testing_inputs, training_labels, testing_labels):
    assert len(training_inputs) > 0, f"parameter training_inputs needs to be of length 0 or greater"
    assert len(testing_inputs) > 0, f"parameter testing_inputs needs to be of length 0 or greater"
    assert len(training_labels) > 0, f"parameter training_labels needs to be of length 0 or greater"
    assert len(testing_labels) > 0, f"parameter testing_labels needs to be of length 0 or greater"
    assert len(training_inputs) == len(training_labels), f"training_inputs and training_labels need to be the same length"
    assert len(testing_inputs) == len(testing_labels), f"testing_inputs and testing_labels need to be the same length"
    misclassify_rate = 0
    # VVVVV YOUR CODE GOES HERE VVVVV $
    P_recur = (sum(training_labels)+1)/(len(training_labels)+2) #Probability of recuring.
    P_non_recur = 1 - P_recur #Probability of no-recuring
    n_recur = sum(training_labels) #total number of recuring training instances.
    n_non_recur = len(training_labels) - n_recur #total number of no-recuring training instances.
    v = [9,3,12,13,2,3,2,5,2] #Number of levels of each feature.
    idx_recur = getting_index_of_recur(training_labels) #index of recuring values in training labels.
    idx_no_recur = getting_index_of_no_recur(training_labels)#index of recuring values in training labels.
    Predictions = [] #Array of predictions of labels.
    for i in range(len(testing_inputs)):
        curr = testing_inputs[i] #Testing instance
        P_recur_testing = [] #Probaility to store if given feature is recuring of testing instance
        P_non_recur_testing = [] #Probaility to store if given feature is no-recuring of testing instance
        for m in range(len(curr)): #This loop basically conducts Laplace smoothing to calculate probabilities of recuring instances.
            n_c = 0
            for j in range(len(idx_recur)):
                if training_inputs[idx_recur[j]][m] == curr[m]:
                    n_c +=1
        
            P_inst = (n_c + 1)/(n_recur + v[m])

            P_recur_testing.append(P_inst)
      

        for n in range(len(curr)): #This loop basically conducts Laplace smoothing to calculate probabilities of recuring instances.
            n_c = 0
            for d in range(len(idx_no_recur)):
                if training_inputs[idx_no_recur[d]][n] == curr[n]:
                    n_c +=1
            
            P_inst = (n_c + 1)/(n_non_recur + v[n])

            P_non_recur_testing.append(P_inst)
        
        #The calculations below happen in regards with naive bayes theorem.
        P_denom = np.add(P_recur_testing,P_non_recur_testing) #Takes sum of recurring and no-recuring probabilities of testing instance.

        P_denom = np.product(P_denom) #conducts product of all the probabilities values of the features occuring in the testing instance.

        P_recur_testpoint = np.product(P_recur_testing)*P_recur/P_denom #Finds probability of recurence given that the testing instance.

        P_non_recur_testpoint = np.product(P_non_recur_testing)*P_non_recur/P_denom #Finds probability of no-recurence given that the testing instance.


        if P_recur_testpoint >= P_non_recur_testpoint: #Breaking ties of be it recurence or no-recure event.
            Predictions.append(1)
        else:
                Predictions.append(0)

    accuracy = accuracy_score(testing_labels, Predictions) #calculates accuaracy of predictiions with given testing labels.
    # print(f"accuracy = {accuracy:.5f}")

    misclassify_rate = 1-accuracy #evaluates misclassify rate.

       








    # ^^^^^ YOUR CODE GOES HERE ^^^^^ $
    return misclassify_rate


# Hint: reuse naive_bayes to compute the misclassification rate for each fold.
def cross_validation(training_inputs, testing_inputs, training_labels, testing_labels):
    data = np.concatenate((training_inputs, testing_inputs))
    label = np.concatenate((training_labels, testing_labels))
    average_rate = 0
    # VVVVV YOUR CODE GOES HERE VVVVV $

    # VVVVV YOUR CODE GOES HERE VVVVV $
    return average_rate
