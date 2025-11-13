#ifndef AKINATOR_H
#define AKINATOR_H

#include "Bin_tree.h"

bool check_answer();

errno_t add_node(Bin_tree_node *cur_node);

errno_t Akinator(Bin_tree_node *cur_node);

#endif
