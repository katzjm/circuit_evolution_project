/*
 * A Network represents a group of reactions that governs how different
 * reagents interact with one another. Note that a Network can support
 * MAX_NUM_REACTIONS at a time
 *
 * Author: Josh Katz
 */

#include "Reaction.h"

#define MAX_NUM_REACTIONS 30

// Memory block for maintaining a network of Reactions
typedef struct network_str {
    Reaction reactions[MAX_NUM_REACTIONS];
    int num_reactions;
} Network, *Network_Ptr;

// Fills the given network with a random number of random reactions with
// constraints outlined in the other parameters
//
// Parameters:
//      network - Pointer to the network to fill with reactions
//      max_num_reactions - The maximum number of reactions that can be
//                          in this network. If this number is greater
//                          than MAX_NUM_REACTIONS then MAX_NUM_REACTIONS
//                          is used
//      min_num_reactions - The minimum number of reactions that can be
//                          in this network. If this number is greater
//                          than MAX_NUM_REACTIONS then MAX_NUM_REACTIONS
//                          is used
//      num_reagents - The number of reagents that can be in this network
//      max_rate_constant - The largest rate constant any reaction can have
//      min_rate_constant - The smallest rate constant any reaction can have
void SetRandomNetwork(Network_Ptr network,
                      int max_num_reactions,
                      int min_num_reactions,
                      int num_reagents,
                      float max_rate_constant,
                      float min_rate_constant);

// Fills the given Network with copies of the Reactions in reactions
//
// Parameters:
//      network - Pointer to the network to fill with reactions
//      reactions - Pointer to an array of reactions copy to network
//      num_reactions - The number of reactions in the given reaction array.
//                      Note that if this is greater than MAX_NUM_REACTIONS than
//                      only the first MAX_NUM_REACTIONS are copied into network
void SetNetwork(Network_Ptr network, Reaction_Ptr reactions, int num_reactions);
