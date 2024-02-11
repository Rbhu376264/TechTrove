#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include "spmat.h"
using namespace std;

#ifdef SPARSE_DEBUG
#include "spmat-debug.h"    
// global instance of the debug helper
SparseMatrixDebugHelper debug;
#endif


// Define and initialize the constant static member npos here

const size_t SparseMatrix::npos = (size_t)-1;


// ----------------------------------------------------------------------------
// ------------------ Coord struct Implementation -----------------------------
// ----------------------------------------------------------------------------

// Constructor
// COMPLETE 
SparseMatrix::Coord::Coord(size_t row, size_t col) :
    r(row), c(col)
{
}

// operator[] accessors
// To be completed - Must adhere it requirements in the .h
size_t& SparseMatrix::Coord::operator[](size_t index) {

    // Coord* temp = new Coord(this->r,this->c);

    // if(index == ROW)
    // {
    //     return temp->r;

    // }
    // else if(index == COL)
    // {
    //     return temp->c;
    // }
    // else
    // {
        
    //     throw std::out_of_range ("Index is 2 or more");
        
    // }

    if(index == ROW)
    {
        return this->r;

    }
    else if(index == COL)
    {
        return this->c;
    }
    else
    {
        
        throw std::out_of_range ("Index is 2 or more");
        
    }


}

size_t const& SparseMatrix::Coord::operator[](size_t index) const {


    if(index == ROW)
    {
        return this->r;

    }
    else if(index == COL)
    {
        return this->c;
    }
    else
    {
        
        throw std::out_of_range ("Index is 2 or more");
        
    }


}

// operator== comparison function
// To be completed - Must adhere it requirements in the .h
bool SparseMatrix::Coord::operator==(const Coord& rhs) const
{
    const Coord* temp_1 = &rhs;

    if((this->r == temp_1->r) && (this->c == temp_1->c))
    {
        return true;
    }
    else
    {
        return false;
    }

}


// operator != comparison function
// COMPLETE
bool SparseMatrix::Coord::operator!=(const Coord& rhs) const
{
    return !operator==(rhs);
}

// ----------------------------------------------------------------------------
// ------------------ SparseItem struct Implementation ------------------------
// ----------------------------------------------------------------------------

// Constructor
// COMPLETE 
SparseMatrix::SparseItem::SparseItem(Coord coord, double v)
{
    this->val = v;
    this->coord = coord;
    this->prev[ROW] = this->prev[COL] = nullptr;
    this->next[ROW] = this->next[COL] = nullptr;
}

// ----------------------------------------------------------------------------
// ----------------- SparseMatrix class Implementation ------------------------
// ----------------------------------------------------------------------------

// Constructor
// To be completed - Must adhere to requirements in the .h
SparseMatrix::SparseMatrix(size_t n) : 
    /* Add code as needed */ n_(n)
{
    if(0U == n_) {
        throw std::invalid_argument("n must be greater than 0");
    }
    /* Add code as needed */

   
    for(size_t i = 0; i<2; i++)
    {
        this->lists_[ i ] = new SparseItem*[n];
        for(size_t j = 0; j<n_; j++)
        {
            
            this->lists_[i][j] = nullptr;
        }
    }


}

// Destructor
// To be completed 
SparseMatrix::~SparseMatrix() 
{
    
    for(size_t j = 0; j<n_; j++)
    {
        SparseItem* x = this->lists_[ROW][j];
        while(x != nullptr && x->next[ROW] != nullptr) 
        {
            x = x->next[ROW];
            delete x->prev[ROW];
        }
        if(x!= nullptr)
        {
            delete x;
        }

    }
    delete [] lists_[ROW];
    delete [] lists_[COL];
    



}

// COMPLETE
SparseMatrix::SparseItem* SparseMatrix::createSparseItem(const SparseMatrix::Coord& coord, double val)
{
    SparseItem* ptr = new SparseItem(coord, val);
#ifdef SPARSE_DEBUG    
    debug.addItem(ptr);
#endif
    return ptr;
}

// COMPLETE
SparseMatrix::SparseItem* SparseMatrix::lowerBound(size_t list, Coord target_coord ) const
{
    SparseItem* head = this->lists_[list][target_coord[list]];
    size_t target_index = target_coord[1-list];

    if(head == nullptr) {
        return nullptr;
    }
    else if( head->coord[1-list] > target_index ) {
        return nullptr;
    }
    else {
        while(  head->next[list] != nullptr && 
                head->next[list]->coord[1-list] <= target_index  ) 
        {
            head = head->next[list];
        }
        return head;        
    }
}


// COMPLETED
double SparseMatrix::get(const Coord& coord) const
{
    if( coord[ROW] >= n_ || coord[COL] >= n_ ) {
        throw std::invalid_argument("Bad coordinates");
    }
    SparseItem* head = lowerBound(ROW, coord );
    if(nullptr == head || head->coord[COL] != coord[COL]){
        return 0;
    }
    return head->val;
}

// COMPLETED
void SparseMatrix::print(std::ostream &os) const
{
    os << setprecision(7);
    for(size_t r = 0; r < this->n_; r++) {
        SparseItem* ptr = this->lists_[ROW][r];
        size_t col = 0;
        while(ptr != NULL) {
            while(col < ptr->coord[COL]) {
                os << setw(8) << 0;
                col++;
            }
            os << setw(8) << ptr->val;
            col++;
            ptr = ptr->next[ROW];
        }
        while(col < this->n_) {
            os << setw(8) << 0;
            col++;
        }
        os << endl;
    }
}


// To be completed - Must adhere it requirements in the .h
void SparseMatrix::deleteNode(SparseItem* node)
{
    if(nullptr == node){
        throw std::invalid_argument("argument must not be null");
    }
    /* Add necessary code to update all other pointers */
    /* Note: calling delete is provided for you below  */

    if(node->prev[ROW] != nullptr && node->next[ROW] != nullptr)
    {
        node->prev[ROW]->next[ROW] = node->next[ROW];

        node->next[ROW]->prev[ROW] = node->prev[ROW];
    }
    
    if(node->prev[ROW] == nullptr && node->next[ROW] == nullptr)
    {
        this->lists_[ROW][node->coord.r] = nullptr;

        
    }
    if(node->prev[ROW] == nullptr && node->next[ROW] != nullptr)
    {
        
        this->lists_[ROW][node->coord.r] = node->next[ROW];
        // cout << this->lists_[ROW][node->coord.r]->coord.c << endl; 
        node->next[ROW]->prev[ROW] = nullptr;
        
    }
    if(node->prev[ROW] != nullptr && node->next[ROW] == nullptr)
    {
        node->prev[ROW]->next[ROW] = nullptr;

    }

    if(node->prev[COL] != nullptr && node->next[COL] != nullptr)
    {
        node->prev[COL]->next[COL] = node->next[COL];

        node->next[COL]->prev[COL] = node->prev[COL];

    }
    if(node->prev[COL] == nullptr && node->next[COL] == nullptr)
    {
        this->lists_[COL][node->coord.c] = nullptr;

        
    }
    if(node->prev[COL] == nullptr && node->next[COL] != nullptr)
    {
        this->lists_[COL][node->coord.c] = node->next[COL];
        node->next[COL]->prev[COL] = nullptr;
        
    }
    if(node->prev[COL] != nullptr && node->next[COL] == nullptr)
    {
        node->prev[COL]->next[COL] = nullptr;

    }


    

    
    



    /* This code should not be altered and should end this function */
#ifdef SPARSE_DEBUG    
    debug.deleteItem(node);
#endif
    delete node;
}

// To be completed - Must adhere it requirements in the .h
void SparseMatrix::set(const Coord& coord, double val)
{
    if((coord.r<0||coord.r>n_-1))
    {
        throw std::out_of_range("Co-ordinates does not comply desired range.");
    }
    if((coord.c<0||coord.c>n_-1))
    {
        throw std::out_of_range("Co-ordinates does not comply desired range.");
    }

    if(val == 0.0)
    {
        // cout<<"322"<<endl;
        if(lowerBound(ROW,coord) != nullptr && lowerBound(ROW,coord)->coord == coord)
        {
            // cout<<"325"<<endl;
            deleteNode(lowerBound(ROW,coord));
            return;
        }
        // if(lowerBound(COL,coord) != nullptr)
        // {
        //     deleteNode(lowerBound(COL,coord));
        // }
        else
        {
            return;
        }
    }
    SparseItem* ptr = createSparseItem(coord,val);
    if(lowerBound(ROW,coord) == nullptr)
    {
        if(this->lists_[ROW][coord.r] != nullptr)
        {
            SparseItem* tempo = this->lists_[ROW][coord.r];
            tempo->prev[ROW] = ptr;
            ptr->next[ROW] = tempo;
            this->lists_[ROW][coord.r] = ptr;
        }
        else
        {
            
            ptr->next[ROW] = nullptr;
            ptr->prev[ROW] = nullptr;
            this->lists_[ROW][coord.r] = ptr;

        }
    }
    else if(lowerBound(ROW,coord) != nullptr)
    {
        SparseItem* nice = lowerBound(ROW,coord);
        SparseItem* tempo = nice->next[ROW];
        ptr->next[ROW] = tempo;
        ptr->prev[ROW] = nice;
        nice->next[ROW] = ptr;
        
        if(tempo != nullptr)
        {
            tempo->prev[ROW] = ptr;
        }



    }
    if(lowerBound(COL,coord) == nullptr)
    {
        if(this->lists_[COL][coord.c] != nullptr)
        {
            SparseItem* tempo = this->lists_[COL][coord.c];
            tempo->prev[COL] = ptr;
            ptr->next[COL] = tempo;
            this->lists_[COL][coord.c] = ptr;
        }
        else
        {
            
            ptr->next[COL] = nullptr;
            ptr->prev[COL] = nullptr;
            this->lists_[COL][coord.c] = ptr;

        }
    }
    else if(lowerBound(COL,coord) != nullptr)
    {
        SparseItem* nice = lowerBound(COL,coord);
        SparseItem* tempo = nice->next[COL];
        ptr->next[COL] = tempo;
        ptr->prev[COL] = nice;
        nice->next[COL] = ptr;
        // tempo->prev[COL] = ptr;

        if(tempo != nullptr)
        {
            tempo->prev[COL] = ptr;
        }



    }
    

    





/* Leave these as the last lines of this function */
#ifdef SPARSE_DEBUG    
    try {
        debug.checkConsistency(this);
    }
    catch (std::logic_error& e) {
        cerr << e.what();
    }
#endif
}

// To be completed - Must adhere it requirements in the .h
//   Be sure to meet the run-time requirements
double SparseMatrix::sumDim(const Coord& coord) const
{
    
    if(coord.r != npos && coord.c != npos)
    {
        throw std::invalid_argument("Expected one of the co-ordinates to be npos");
    }
    if((coord.r < 0 || coord.r > n_-1 ) && coord.c == npos)
    {
        throw std::out_of_range("Co-ordinates does not comply desired range.");
    }
    if((coord.c < 0 || coord.c > n_-1 ) && coord.r == npos)
    {
        throw std::out_of_range("Co-ordinates does not comply desired range.");
    }
    double value = 0.0;
    if(coord.r != npos)
    {
        SparseItem* ptr = this->lists_[ROW][coord.r];

        while(ptr != nullptr)
        {
            value += ptr->val;

            ptr = ptr->next[ROW];
        }

        return value;
    }
    if(coord.c != npos)
    {
        SparseItem* ptr = this->lists_[COL][coord.c];

        while(ptr != nullptr)
        {
            value += ptr->val;

            ptr = ptr->next[COL];
        }

        return value;

    }

    return value;
}

// To be completed - Must adhere it requirements in the .h
//   Be sure to meet the run-time requirements
void SparseMatrix::copyDim(const Coord& srcCoord, const Coord& dstCoord)
{
    // Ignore self-copy - leave these as the first lines of the function 
    if( dstCoord == srcCoord) {
        return;
    }

    // Add code to check for exception cases and, if valid, perform the copy
    // of the indicated dimension

    if(srcCoord.r != npos && srcCoord.c != npos)
    {

        throw std::invalid_argument("Expected one of the co-ordinates to be npos");

    }
    if(dstCoord.r != npos && dstCoord.c != npos)
    {
        throw std::invalid_argument("Expected one of the co-ordinates to be npos");
    }

    if(srcCoord.r == npos && (srcCoord.c < 0 || srcCoord.c > n_ - 1))
    {
        throw std::out_of_range("Co-ordinates does not comply desired range.");

    }

    if(srcCoord.c == npos && (srcCoord.r < 0 || srcCoord.r > n_ - 1))
    {
        throw std::out_of_range("Co-ordinates does not comply desired range.");

    }

    if(dstCoord.r == npos && (dstCoord.c < 0 || dstCoord.c > n_ - 1))
    {
        throw std::out_of_range("Co-ordinates does not comply desired range.");

    }
    if(dstCoord.c == npos && (dstCoord.r < 0 || dstCoord.r > n_ - 1))
    {
        throw std::out_of_range("Co-ordinates does not comply desired range.");

    }

    if(srcCoord.r != npos && dstCoord.r != npos)
    {
        // size_t we = max(srcCoord.r,dstCoord.r);

        SparseItem* ptr = this->lists_[ROW][dstCoord.r];

        while(ptr != nullptr)
        {
            SparseItem* temp = ptr;
            ptr = ptr->next[ROW];

            deleteNode(temp);
            
        }

    
        SparseItem* ptr1 = this->lists_[ROW][srcCoord.r];
        Coord x = dstCoord;
        while(ptr1 != nullptr)
        {
            x.c = ptr1->coord.c;
            set(x,ptr1->val);
            
            ptr1 = ptr1->next[ROW];
            if(ptr1 != nullptr)
            {
             x.c  = ptr1->coord.c;
            }
        }


        return;

    }

    if(srcCoord.c != npos && dstCoord.c != npos)
    {
        // size_t we = max(srcCoord.r,dstCoord.r);

        SparseItem* ptr = this->lists_[COL][dstCoord.c];

        while(ptr != nullptr)
        { 
            SparseItem* temp = ptr;
            ptr = ptr->next[COL];

            deleteNode(temp);
           
        }

    
        SparseItem* ptr1 = this->lists_[COL][srcCoord.c];
        Coord x = dstCoord;
        while(ptr1 != nullptr)
        {
            x.r = ptr1->coord.r;
            set(x,ptr1->val);
            
            ptr1 = ptr1->next[COL];
            if(ptr1 != nullptr)
            {
             x.r  = ptr1->coord.r;
            }
        }


        return;

    }
    if(srcCoord.r != npos && dstCoord.c != npos)
    {
        SparseItem* ptr = this->lists_[COL][dstCoord.c];
        double fix = 0.0;

        while(ptr != nullptr)
        {
            if(ptr->coord.r == srcCoord.r)
            {
                fix = ptr->val;
                
            }
            // cout<<ptr->coord.r<<" "<<ptr->coord.c<<endl;
            // cout<<ptr->val<<endl;
            SparseItem* temp = ptr;
            ptr = ptr->next[COL];
            deleteNode(temp);

            

        }
        // cout<<"done delete"<<endl;
        // print(std::cout);
        SparseItem* ptr1 = this->lists_[ROW][srcCoord.r];
        Coord x = dstCoord;
        // x.r  = ptr1->coord.r;
        while(ptr1 != nullptr)
        {
            x.r  = ptr1->coord.r;
            // cout<<"624 line "<< dstCoord.c<<" "<<ptr1->coord.c <<endl;
             
            // if(dstCoord.c == ptr1->coord.c)
            // {
            //     cout<<fix<<" 625"<<endl;
            //     set(x,fix);
            // }
            
            // cout<<ptr1->val<<endl;
            // cout<<ptr1->coord.r<<" "<<ptr1->coord.c<<endl;
            x.r = ptr1->coord.c;
            x.c = dstCoord.c;
            set(x,ptr1->val);
            // cout<<x.r<<" "<<x.c<<endl;
            
            // print(std::cout);
            
            // if(ptr1 != nullptr)
            // {
            //  x.r  = ptr1->coord.r;
            // }
            
            ptr1 = ptr1->next[ROW];
            
        }
        Coord y;
        y.r = dstCoord.c;
        y.c = dstCoord.c;
        set(y,fix);

        // cout<<endl;

        // print(std::cout);

        // cout<<endl;
        

        return;
    }

    if(srcCoord.c != npos && dstCoord.r != npos)
    {
        SparseItem* ptr = this->lists_[ROW][dstCoord.r];
        double fix = 0.0;

        while(ptr != nullptr)
        {
            if(ptr->coord.c == srcCoord.c)
            {
                fix = ptr->val;
            }

            // cout<<ptr->coord.r<<" "<<ptr->coord.c<<endl;
            // cout<<ptr->val<<endl;
            SparseItem* temp = ptr;
            ptr = ptr->next[ROW];
            deleteNode(temp);
            

        }
        // cout<<endl;
            
        // print(std::cout);

        // cout<<endl;

        SparseItem* ptr1 = this->lists_[COL][srcCoord.c];
        Coord x = dstCoord;
        // x.c  = ptr1->coord.c;
        Coord y;
        y.c = dstCoord.r;
        y.r = dstCoord.r;
        while(ptr1 != nullptr)
        {
            // x.r  = ptr1->coord.r;
            
            // x.c  = ptr1->coord.c;
            
            
            x.c = ptr1->coord.r;
            x.r = dstCoord.r;

            if(x.c != y.c || x.r != y.r)

            {
            
            
                set(x,ptr1->val);
            }

            // cout<<endl;
            
            // print(std::cout);

            // cout<<endl;

            ptr1 = ptr1->next[COL];

            

            // if(ptr1 != nullptr)
            // {
            //  x.c  = ptr1->coord.c;
            // }
            
        }

        
        
        set(y,fix);

        // cout<<endl;
            
        // print(std::cout);

        // cout<<endl;

        return;
    }


    






/* Leave these as the last lines of this function */
#ifdef SPARSE_DEBUG    
    try {
        debug.checkConsistency(this);
    }
    catch (std::logic_error& e) {
        cerr << e.what();
    }
#endif
}

