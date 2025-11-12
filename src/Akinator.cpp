#include "Akinator.h"
#include <string.h>

#undef FINAL_CODE
#define FINAL_CODE

errno_t add_node(Bin_tree_node *const cur_node) {
    assert(cur_node);
    ON_DEBUG(
    errno_t verify_err = 0;
    CHECK_FUNC(Bin_tree_node_verify, cur_node, &verify_err);
    assert(!verify_err);
    )

    size_t const MESSAGE_MAX_SIZE = 200;
    char str1[MESSAGE_MAX_SIZE] = {},
         str2[MESSAGE_MAX_SIZE] = {};

    printf_s("Please enter the criteria by which your person differs from guessed in the question form\n");
    CHECK_FUNC(My_scanf_s, 1, "%[^\n]%*1c", str1, MESSAGE_MAX_SIZE);

    printf_s("Does your person satisfy this criteria?\n");
    CHECK_FUNC(My_scanf_s, 1, "%s%*1c", str2, MESSAGE_MAX_SIZE);
    if (strcmp(str2, "yes")) {
        printf_s("What person are you thinking?\n");
        CHECK_FUNC(My_scanf_s, 1, "%[^\n]%*1c", str2, MESSAGE_MAX_SIZE);
        printf_s("Thank you. You can try again\n");

        CHECK_FUNC(Split_node, cur_node, str2, cur_node->val);
        free(cur_node->val);
        CHECK_FUNC(My_strdup, &cur_node->val, str1);
    }
    else {
        printf_s("What person are you thinking?\n");
        CHECK_FUNC(My_scanf_s, 1, "%[^\n]%*1c", str2, MESSAGE_MAX_SIZE);
        printf_s("Thank you. You can try again\n");

        CHECK_FUNC(Split_node, cur_node, cur_node->val, str2);
        free(cur_node->val);
        CHECK_FUNC(My_strdup, &cur_node->val, str1);
    }

    return 0;
}

errno_t Akinator(Bin_tree_node *const cur_node) { //TODO - add handling invalid answers
    assert(cur_node);
    ON_DEBUG(
    errno_t verify_err = 0;
    CHECK_FUNC(Bin_tree_node_verify, cur_node, &verify_err);
    assert(!verify_err);
    )

    size_t const MESSAGE_MAX_SIZE = 200;
    char str[MESSAGE_MAX_SIZE] = {};
    if (cur_node->left == nullptr) {
        if (!strcmp(INITIAL_VAL, cur_node->val)) {
            printf_s("I have no idea who could it be. Please enter someone\n", cur_node->val);
            CHECK_FUNC(My_scanf_s, 1, "%[^\n]%*1c", str, MESSAGE_MAX_SIZE);
            printf_s("Thank you. You can try again\n");

            free(cur_node->val);
            CHECK_FUNC(My_strdup, &cur_node->val, str);

            return 0;
        }

        printf_s("Is it %s?\n", cur_node->val);
        CHECK_FUNC(My_scanf_s, 1, "%s%*1c", str, MESSAGE_MAX_SIZE);
        if (strcmp(str, "yes")) {
            printf_s("Do you want to add new person?\n");
            CHECK_FUNC(My_scanf_s, 1, "%s%*1c", str, MESSAGE_MAX_SIZE);
            if (!strcmp(str, "yes")) {
                CHECK_FUNC(add_node, cur_node);
            }
        }
        else {
            printf_s("Great! You can try again\n");
        }
    }
    else {
        printf_s("%s\n", cur_node->val);
        CHECK_FUNC(My_scanf_s, 1, "%s%*1c", str, MESSAGE_MAX_SIZE);
        if (strcmp(str, "yes")) {
            CHECK_FUNC(Akinator, cur_node->left);
        }
        else {
            CHECK_FUNC(Akinator, cur_node->right);
        }
    }

    return 0;
}
