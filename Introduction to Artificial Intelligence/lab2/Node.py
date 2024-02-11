import numpy as np
from lab2_utils import TextbookStack, apply_sequence


class Node(object):

    # Constructor of Node taking stack, f(n), sequence so far, g(n).
    def __init__(self, Textbookstack, total_cost, sequence, g_val):
        self.stacky = (Textbookstack)
        self.cost = total_cost
        self.sequence = sequence
        self.gval = g_val

    # method to get stack of a node.
    def get_stack(self):

        return self.stacky

    # method to get f(n) of a node.
    def get_totalcost(self):

        return self.cost

    # method to get sequence so far of a node.
    def get_sequence(self):

        return self.sequence

    # method to get g(n) of a node.
    def get_gval(self):

        return self.gval

    # method used to compare two nodes based on overall cost.
    def __lt__(self, node):

        return self.cost < node.cost
