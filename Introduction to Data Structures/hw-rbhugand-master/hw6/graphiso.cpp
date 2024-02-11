#include <iostream>
#include <sstream>
#include "graphiso.h"

using namespace std;

// ================= Complete - Begin Graph class implementation ===================
Graph::Graph(std::istream& istr)
{
    string aline;
    while(getline(istr,aline))
    {
        istringstream iss(aline);
        string u, v;
        if(iss >> u){
            VERTEX_SET_T neighbors;
            while(iss >> v)
            {
                neighbors.insert(v);
            }
            adj_.insert(std::make_pair(u,neighbors));
        }
    }
}


bool Graph::edgeExists(const VERTEX_T& u, const VERTEX_T& v) const
{
    if((adj_.find(u) != adj_.end()) && (adj_.at(u).find(v) != adj_.at(u).end()))
    {
        return true;
    }
    return false;
}
const VERTEX_SET_T& Graph::neighbors(const VERTEX_T& v) const
{
    if(adj_.find(v) == adj_.end()){
        throw std::invalid_argument("Neighbors: invalid vertex - not in  map");
    }
    return adj_.at(v);
}
VERTEX_LIST_T Graph::vertices() const
{
    VERTEX_LIST_T verts;
    for(const auto& p : adj_)
    {
        verts.push_back(p.first);
    }
    return verts;
}
// ================= Complete - End Graph class implementation ===================

// Prototype and helper functions here
bool graphIsoHelper(size_t ctr, VERTEX_LIST_T G1, VERTEX_LIST_T G2, VERTEX_ID_MAP_T& mapped);
bool alreadyMapped(const Graph&g1, VERTEX_T g2_loc,VERTEX_ID_MAP_T& mapped);
// To be completed
bool isConsistent(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    // Feel free to change or remove this starter code
    VERTEX_LIST_T g1verts = g1.vertices();
    for(const auto& g1u : g1verts)
    {
        // Check mappings for necessary vertices to see if there is any violation
        // and return false
        if(mapping.find(g1u) != nullptr)
        {
            VERTEX_T loc = mapping.at(g1u);
            // cout<<g2.neighbors(loc).size() << " "<<g1.neighbors(g1u).size()<<endl;
            if(g2.neighbors(loc).size() != g1.neighbors(g1u).size())
            {

                return false;
            }
            else
            {
                for(const auto& it: g1.neighbors(g1u))
                {
                    if(mapping.find(it) != nullptr)
                    {
                        if(g2.edgeExists(loc,mapping.at(it)) == false)
                        {
                            return false;
                        }
                    }
                }
            }
            
        }

    }
    return true;
}

// Add any helper functions you deem useful

bool graphIsoHelper(size_t ctr, VERTEX_LIST_T G1, VERTEX_LIST_T G2, const Graph& g1, const Graph& g2,VERTEX_ID_MAP_T& mapped)
{
    if(ctr == G1.size())
    {
        return true;
    }
    else
    {
        for(unsigned int i = 0; i<G2.size(); i++)
        {
            // cout<<"G1: "<<G1[ctr]<<" "<<G2[i]<<endl;
            if(!alreadyMapped(g1,G2[i],mapped))
            {
            

                mapped.insert(make_pair(G1[ctr],G2[i]));

                if(isConsistent(g1,g2,mapped))
                {
                    
                    
                    bool res = graphIsoHelper(ctr+1,G1,G2,g1,g2,mapped);

                    if(res == false)
                    {
                        continue;
                    }
                    else
                    {
                        return res;
                    }

                }
                else
                {
                    mapped.remove(G1[ctr]);

                }
            }
        }

        return false;
    }

}
bool alreadyMapped(const Graph&g1, VERTEX_T g2_loc,VERTEX_ID_MAP_T& mapped)
{
    for(const auto& i: g1.vertices())
    {
        if(mapped.find(i) != nullptr)
        {
            if(mapped.at(i)==g2_loc)
            {
                return true;
            }
        }
        
    }

    return false;
}

// To be completed
bool graphIso(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    VERTEX_LIST_T g1verts = g1.vertices();
    if(g1verts.size() != g2.vertices().size())
    {
        return false;
    }
    // Add code here
    bool result = graphIsoHelper(0,g1.vertices(),g2.vertices(),g1,g2,mapping);
    // Delete this and return the correct value...
    // This is just placeholder to allow compilation
    return result;
}

