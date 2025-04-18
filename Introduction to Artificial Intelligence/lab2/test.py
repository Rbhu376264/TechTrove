# Any changes to this file will not be reflected during testing and grading
# While these are some test cases these are not the only cases used in grading
from lab2_utils import TextbookStack, apply_sequence
from lab2 import a_star_search, weighted_a_star_search, nodes_traversed_from_a_star, nodes_traversed_from_weighted
import itertools
import time
from tabulate import tabulate


def test_sorter(func, stack, solution=None, verbose=False, EX=False):
    # Tests a function against a stack and a solution if it exists, else returns a solution
    if verbose:
        print(f"Testing {func.__name__} on:\n {stack}")
    if EX:
        return func(stack, EX=True)
    else:
        sequence = func(stack)
    new_stack = apply_sequence(stack, sequence)
    pass_test = int(new_stack.check_ordered())
    if solution:
        correct_sequence = int(sequence == solution)
    else:
        correct_sequence = sequence

    if verbose:
        print(f"Stack is {'' if new_stack.check_ordered() else 'not '}ordered")
        if solution:
            print(
                f"Comparing output to expected traces  - "
                f"\t{'PASSED' if correct_sequence else 'FAILED'}"
            )
    return pass_test, correct_sequence


def test_permutations(func, max_n):
    passes = []
    for i in range(1, max_n + 1):
        order = list(range(i))
        orient = [0 for k in range(i)]
        orders = list(itertools.permutations(order))
        orders = [list(p) for p in orders]
        orients = list(itertools.product([0, 1], repeat=i))
        orients = [list(p) for p in orients]
        for order in orders:
            for orient in orients:
                stack = TextbookStack(
                    initial_order=order, initial_orientations=orient)
                pass_test, _ = test_sorter(func, stack, EX=False)
                passes.append(pass_test)
    pass_perc = sum(passes) / len(passes)
    return pass_perc


if __name__ == "__main__":

    #######################
    # Generate Examples
    #######################
    stacks = [
        TextbookStack(initial_order=[3, 2, 1, 0],
                      initial_orientations=[0, 0, 0, 0]),
        TextbookStack(initial_order=[3, 2, 0, 1],
                      initial_orientations=[0, 1, 1, 1]),
        TextbookStack(
            initial_order=[0, 2, 3, 5, 1, 4], initial_orientations=[0, 1, 0, 1, 0, 1]
        ),
    ]
    print("Generating A* solutions")
    for s in stacks:
        correct_stack = a_star_search(s)
        print(correct_stack)

    examples = [
        (
            TextbookStack(
                initial_order=[3, 2, 1, 0], initial_orientations=[0, 0, 0, 0]
            ),
            {"a_star_search": [4]},
        ),
        (
            TextbookStack(
                initial_order=[3, 2, 0, 1], initial_orientations=[0, 1, 1, 1]
            ),
            {"a_star_search": [2, 1, 2, 4, 2]},
        ),
        (
            TextbookStack(
                initial_order=[0, 2, 3, 5, 1, 4],
                initial_orientations=[0, 1, 0, 1, 0, 1],
            ),
            {"a_star_search": [4, 6, 5, 1, 4, 1, 2]},
        ),
    ]

    #######################
    # Verify Methods
    #######################

    correct_stacks = 0
    correct_sequences = 0
    n_tests = 0

    for example in examples:
        test = example[0]
        correct_stack, correct_sequence = test_sorter(
            a_star_search, test, example[1]["a_star_search"], verbose=False,
        )

        correct_stacks += correct_stack
        correct_sequences += correct_sequence
        n_tests += 1

    print(
        f"Tests:{n_tests} - Passed: {correct_stacks} - Confirmed Sequ: {correct_sequences}\n"
    )

    # TA Note - we will probably grade up to at least max_n=4
    max_n = 5
    print("Evaluating A* on all permutations")
    time0 = time.time()
    score = test_permutations(a_star_search, max_n)
    print(f"Passing {score*100} %")
    print(f"Time lapse for max_n={max_n}: {time.time()-time0:.3f} seconds.")

# My test for weighted_A_star_search and A_star

    # Stacks of different sizes such that 'm' ranges from 1 to 8.
    stack_list = [TextbookStack(initial_order=[0], initial_orientations=[0]), TextbookStack(initial_order=[0, 1], initial_orientations=[1, 0]), TextbookStack(initial_order=[2, 0, 1], initial_orientations=[0, 1, 1]), TextbookStack(initial_order=[3, 2, 0, 1], initial_orientations=[0, 1, 1, 1]), TextbookStack(initial_order=[
        3, 2, 4, 0, 1], initial_orientations=[0, 1, 0, 1, 1]), TextbookStack(initial_order=[3, 2, 4, 0, 1, 5], initial_orientations=[0, 1, 0, 1, 1, 0]), TextbookStack(initial_order=[3, 2, 4, 0, 1, 6, 5], initial_orientations=[0, 1, 0, 1, 1, 0, 1]), TextbookStack(initial_order=[3, 2, 4, 0, 1, 6, 5, 7], initial_orientations=[0, 1, 0, 1, 1, 0, 0, 1])]

    table = []  # table which will be used to print out the results with help of tabulate library

    for stackum in stack_list:

        # get a sequence by running A* search.
        sequence = a_star_search(stackum)

        # Get a sequence by running weighted A* search.
        sequence_1 = weighted_a_star_search(stackum, 1, 2*stackum.num_books)

        # Finds the average number of nodes visited on a particular size m.
        avg = (len(nodes_traversed_from_a_star(stackum)) +
               len(nodes_traversed_from_weighted(stackum, 1, 2*stackum.num_books)))//2

        # Appends a row on a particular iteration into table reprsenting size, number of flips from A* and weighed A* and avg nodoes visited.
        table.append([stackum.num_books, len(sequence), len(sequence_1), avg])

    # Prints the table in a great format with appropriate headers.
    print("\nTable for Extra Credit:- \n")
    print(tabulate(table, headers=['m', 'A*',
          'Weighted A*', 'Avg Nodes Visited']))
