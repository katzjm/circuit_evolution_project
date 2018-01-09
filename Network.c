/*
* A Network represents a group of reactions that governs how different
* reagents interact with one another. Note that a Network can support
* MAX_NUM_REACTIONS at a time
*
* Author: Josh Katz
*/

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "nvector/nvector_serial.h"

#include "Network.h"
#include "Reaction.h"
#include "Configs.h"

void SetRandomNetwork(Network_Ptr network, Config_Ptr config) {
  int reaction_range = config->max_num_reactions - config->min_num_reactions;
  network->num_reactions = rand() % reaction_range + config->min_num_reactions;
  network->fitness = INFINITY;
  for (int i = 0; i < network->num_reactions; i++) {
    SetRandomReaction(&network->reactions[i], config);
  }
}

// Simple min function. Should not be used when either x or y need to be
// evaluated before comparison
#define min(x, y) (((x) <= (y)) ? (x) : (y))

void SetNetwork(Network_Ptr network,
                Reaction_Ptr reactions,
                double fitness,
                int num_reactions) {
  network->num_reactions = min(num_reactions, MAX_NUM_REACTIONS);
  network->fitness = fitness;
  for (int i = 0; i < network->num_reactions; i++) {
    network->reactions[i] = reactions[i];
  }
}

#undef min

void MutateNetwork(Network_Ptr network, Config_Ptr config) {
  float mutation = (float) rand() / RAND_MAX;
  bool network_changed = false;

  if ((mutation -= config->prob_add_reaction) <= 0) {
    network_changed = AddReaction(network, config);
  } else if ((mutation -= config->prob_remove_reaction) <= 0) {
    network_changed = RemoveReaction(network);
  }

  if (mutation > 0 || network_changed == false) {
    ModifyRateConstant(network, config);
  }
}

bool AddReaction(Network_Ptr network, Config_Ptr config) {
  if (network->num_reactions == MAX_NUM_REACTIONS) {
    return false;
  }

  SetRandomReaction(&network->reactions[network->num_reactions], config);
  network->num_reactions++;
  return true;
}

bool RemoveReaction(Network_Ptr network) {
  if (network->num_reactions <= 0) {
    return false;
  }
  network->num_reactions--;
  return true;
}

void ModifyRateConstant(Network_Ptr network, Config_Ptr config) {
  if (network->num_reactions < 1) {
    return;
  }

  int reaction_to_change = rand() % network->num_reactions;
  MutateRateConstant(&network->reactions[reaction_to_change], config);
}

void SetInitialConcentrations(N_Vector init_concentrations, Config_Ptr c) {
  realtype* init_concentrations_data = NV_DATA_S(init_concentrations);

  for (int i = 0; i < c->num_species; i++) {
    init_concentrations_data[i] = c->initial_concentrations;
  }
}

int EvaluateNetwork(Network_Ptr network,
                    Config_Ptr c,
                    N_Vector init_concentrations) {
  
}
