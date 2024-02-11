# you can add imports but you should not rely on libraries that are not already provided in "requirements.txt #
from collections import deque
from lab1_utils import TextbookStack
from copy import copy
from lab1_utils import apply_sequence


def breadth_first_search(stack):
    flip_sequence = []

    # --- v ADD YOUR CODE HERE v --- #

    
    mystack = stack.copy()


    explored_nodes = []
    path = []
    queue = []

    queue.append(mystack)
    explored_nodes.append(mystack)
    path.append([])
    found_solution = False

    
    while queue :

        mystack_1 = queue.pop(0)

        curr_path = path.pop(0)
        

        for i in range(1,len(mystack_1.order)+1):
            
            mystcpy = mystack_1.copy()
           
            mystcpy.flip_stack(i)
            
          
            if mystcpy.check_ordered():
                found_solution = True
            
                curr_path.append(i)
                
                flip_sequence = curr_path
             

                break
                
            
            if(mystcpy not in explored_nodes):
               
                queue.append(mystcpy)
                explored_nodes.append(mystcpy)
                new_path = curr_path.copy()

                new_path.append(i)

                path.append(new_path)


        if(found_solution):
           
            break
        
       
        

    return flip_sequence
    # ---------------------------- #


def depth_first_search(stack):
    flip_sequence = []

    # --- v ADD YOUR CODE HERE v --- #
    mystack = stack.copy()


    explored_nodes = []
    path = []
    queue = []

    queue.append(mystack)
    path.append([])
    found_solution = False

    
    while queue :

        mystack_1 = queue.pop()

        curr_path = path.pop()

        explored_nodes.append(mystack_1)
        
        if mystack_1.check_ordered():
                found_solution = True
                
                flip_sequence = curr_path
             
                break

        for i in range(1,len(mystack_1.order)+1):
            
            mystcpy = mystack_1.copy()
           
            mystcpy.flip_stack(i)
                
            
            if(mystcpy not in explored_nodes):
               
                queue.append(mystcpy)
                new_path = curr_path.copy()

                new_path.append(i)

                path.append(new_path)


        if(found_solution):
           
            break
        
       
    return flip_sequence
    # ---------------------------- #
