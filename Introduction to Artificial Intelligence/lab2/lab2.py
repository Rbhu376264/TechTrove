# you can add imports but you should not rely on libraries that are not already provided in "requirements.txt #
from heapq import heappush, heappop, heapify
from lab2_utils import TextbookStack, apply_sequence
from collections import deque
from Node import Node
from copy import deepcopy
import itertools

# nodes traversed in a_star used for analysis of extra credit.
nodes_traversed_a_star = []

# nodes traversed in weighted_a_star used for analysis of extra credit.
nodes_traversed_weighted_a_star = []

# Used to calcuate h(n) for A star search.


def heurisitic_calc(stack):
    count = 0
    for i in range(len(stack.order)-1):  # Iterates over the given stack
        # Checks if a pair is adjacent or not
        if (abs(stack.order[i+1] - stack.order[i]) != 1):
            count += 1
            continue
        # Checks if a pair has different orientations i.e. pair has a book facing up and one facing down.
        if ((stack.orientations[i] != stack.orientations[i+1])):
            count += 1
            continue
        # Checks if a pair is wrongly ordered, but with correct orientations (both facing up).
        if (((stack.order[i+1] + 1 == stack.order[i])) and (stack.orientations[i] and stack.orientations[i+1])):
            count += 1
            continue
        # Checks if a pair is correctly ordered, but with wrong orientations (both facing down).
        if (((stack.order[i+1] - stack.order[i]) == 1) and (stack.orientations[i] == stack.orientations[i+1] == 0)):
            count += 1
            continue

    return count


def a_star_search(stack):

    # final sequence of flips done to arrived at the goal state.
    flip_sequence = []

    # Nodes which will be used to find the the goal state.
    nodes_to_expand = []

    nodes_traversed = []  # Nodes which are traversed.

    g_n = 0  # Starting g(n) value.

    # Calculates the f(n) value of the starting node.
    cost = heurisitic_calc(stack) + g_n

    # Makes a node object which takes stack, f(n), sequence of flips so far, g(n) as input.
    nody = Node(stack, cost, [], g_n)

    nodes_to_expand.append(nody)  # Appends node in node_to_expand.

    # --- v ADD YOUR CODE HERE v --- #
    while nodes_to_expand:

        # Pops off the node from the nodes_to_expand which is a heap.
        curr_node = heappop(nodes_to_expand)

        # Appending nodes in nodes_traversed and node_traversed_a_star.
        nodes_traversed.append(curr_node)
        nodes_traversed_a_star.append(curr_node)

        # Checks if current sequence is ordered, then return flip sequence as current node sequence.
        if curr_node.get_stack().check_ordered():
            flip_sequence = curr_node.get_sequence()
            return flip_sequence

        curr_g_n = curr_node.get_gval() + 1  # g(n) for a new level in a tree.

        # old sequence stores current node's sequence.
        old_sequence = curr_node.get_sequence()

        # Iterating from  1 to length of stack + 1.
        for i in range(1, curr_node.get_stack().num_books+1):

            # makes copy of current node's stack.
            flippy = curr_node.get_stack().copy()

            flippy.flip_stack(i)  # flips the stack from given index.

            # Checks if the stack is ordered then merge old sequence with current index i and return it as flip sequence.
            if flippy.check_ordered():
                flip_sequence = old_sequence + [i]
                return flip_sequence

            # Calculates the f(n) for the flipped stack.
            costy = heurisitic_calc(flippy) + curr_g_n

            # Makes equence of the flipped stack.
            new_sequence = old_sequence + [i]

            # Makes a node of the newly evaluaated stack, f(n), sequence so far, g(n).
            node_in = Node(flippy, costy, new_sequence, curr_g_n)

            # Checks if given node is visited or not, then psuh into the nodes_to_expand heap.
            if (node_in not in nodes_traversed):

                heappush(nodes_to_expand, node_in)

    return flip_sequence

    # ---------------------------- #


# Used to calculate f(n) for weighted_a_star.
def f_calc(stack, gval, epsilon, N, d):

    h_n = heurisitic_calc(stack)  # used to calculate h(n)

    w_n = 1 + epsilon - ((epsilon*d)/N)  # used to calculate w(n).

    return gval + (w_n*h_n)  # finally returns f(n)


def weighted_a_star_search(stack, epsilon=None, N=1):
    # Weighted A* is extra credit

    flip_sequence = []  # final sequence of flips done to arrived at the goal state

    # Nodes which will be used to find the the goal state.
    nodes_to_expand = []

    nodes_traversed = []  # Nodes which are traversed.

    g_n = 0  # Starting g(n) value.

    # Calculates f(n) on given parameters as stack, g(n), epsilon, N , and depth so far.
    cost = f_calc(stack, g_n, epsilon, N, 0)

    # Makes a node object which takes stack, f(n), sequence of flips so far, g(n) as input.
    nody = Node(stack, cost, [], g_n)

    nodes_to_expand.append(nody)  # Appends node in node_to_expand.

    # --- v ADD YOUR CODE HERE v --- #
    while nodes_to_expand:

        # Pops off the node from the nodes_to_expand which is a heap.
        curr_node = heappop(nodes_to_expand)

        # Appending nodes in nodes_traversed and node_traversed_weighted_a_star.
        nodes_traversed.append(curr_node)

        nodes_traversed_weighted_a_star.append(curr_node)

        # Checks if current sequence is ordered, then return flip sequence as current node sequence.
        if curr_node.get_stack().check_ordered():
            flip_sequence = curr_node.get_sequence()
            return flip_sequence

        curr_g_n = curr_node.get_gval() + 1  # g(n) for a new level in a tree.

        # old sequence stores current node's sequence.
        old_sequence = curr_node.get_sequence()

        # Iterating from  1 to length of stack + 1.
        for i in range(1, curr_node.get_stack().num_books+1):

            # makes copy of current node's stack.
            flippy = curr_node.get_stack().copy()

            flippy.flip_stack(i)  # flips the stack from given index.

            # Checks if the stack is ordered then merge old sequence with current index i and return it as flip sequence.
            if flippy.check_ordered():
                flip_sequence = old_sequence + [i]
                return flip_sequence

            # Makes equence of the flipped stack.
            new_sequence = old_sequence + [i]

            # Calculates the f(n) for the flipped stack.
            costy = f_calc(flippy, curr_g_n, epsilon, N, len(new_sequence))

            # Makes a node of the newly evaluaated stack, f(n), sequence so far, g(n).
            node_in = Node(flippy, costy, new_sequence, curr_g_n)

            # Checks if given node is visited or not, then psuh into the nodes_to_expand heap.
            if (node_in not in nodes_traversed):

                heappush(nodes_to_expand, node_in)

    # --- v ADD YOUR CODE HERE v --- #

    return flip_sequence

    # ---------------------------- #


# Used calculate nodes_traversed for A star search on a given stack.
def nodes_traversed_from_a_star(stack):

    nodes_traversed_a_star.clear()

    sequence = a_star_search(stack)

    return nodes_traversed_a_star


# Used calculate nodes_traversed for weighted A star search on a given stack, epsilon, N.
def nodes_traversed_from_weighted(stack, epsilon, N):

    nodes_traversed_weighted_a_star.clear()

    sequence = weighted_a_star_search(stack, epsilon, N)

    return nodes_traversed_weighted_a_star
