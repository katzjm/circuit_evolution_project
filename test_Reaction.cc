/*
 * Test that Reaction has the intended functionality
 *
 * Author: Josh Katz
 */

extern "C" {
  #include "Reaction.h"
  #include "Configs.h"
}

namespace evolvertest {

TEST_F(Test_Reaction, TestRandomReaction) {
  int num_uni_uni = 0;
  int num_uni_bi = 0;
  int num_bi_uni = 0;
  int num_bi_bi = 0;

  for (int i = 0; i < 1000; i++) {
    SetRandomReaction(&reaction, &c);
    EXPECT_GE(reaction.reactant_1, 0);
    EXPECT_LT(reaction.reactant_1, c.num_species);
    EXPECT_GE(reaction.product_1, 0);
    EXPECT_LT(reaction.product_1, c.num_species);
    EXPECT_GE(reaction.reactant_2, -1);
    EXPECT_LT(reaction.reactant_2, c.num_species);
    EXPECT_GE(reaction.product_2, -1);
    EXPECT_LT(reaction.product_2, c.num_species);

    if (reaction.reactant_2 == -1 && reaction.product_2 == -1) {
      num_uni_uni++;
    } else if (reaction.reactant_2 == -1 && reaction.product_2 != -1) {
      num_uni_bi++;
    } else if (reaction.reactant_2 != -1 && reaction.product_2 == -1) {
      num_bi_uni++;
    } else {
      num_bi_bi++;
    }
  }

  EXPECT_GT(num_uni_uni, 100);
  EXPECT_GT(num_uni_bi, 100);
  EXPECT_GT(num_bi_uni, 100);
  EXPECT_GT(num_bi_bi, 100);
}

}  // evolvertest
