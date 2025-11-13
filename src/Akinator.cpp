#include "Akinator.h"
#include <string.h>
#include <ctype.h>

#undef FINAL_CODE
#define FINAL_CODE

static size_t const AKINATOR_MESSAGE_MAX_SIZE = 200;

bool check_answer() {
    while (true) {
        char str[AKINATOR_MESSAGE_MAX_SIZE] = {};
        CHECK_FUNC(My_scanf_s, 1, "%s%*1c", str, AKINATOR_MESSAGE_MAX_SIZE);
        size_t cur_len = strnlen_s(str, AKINATOR_MESSAGE_MAX_SIZE);

        if (cur_len == 3 and
            tolower(str[0]) == 'y' and tolower(str[1]) == 'e' and tolower(str[2]) == 's') {
            return true;
        }

        if (cur_len == 2 and
            tolower(str[0]) == 'n' and tolower(str[1]) == 'o') {
            return false;
        }

        printf_s("Please enter \"yes\" or \"no\" in any case\n");
    }
}

errno_t add_node(Bin_tree_node *const cur_node) {
    assert(cur_node);
    ON_DEBUG(
    errno_t verify_err = 0;
    CHECK_FUNC(Bin_tree_node_verify, cur_node, &verify_err);
    if (verify_err) { return verify_err; }
    )

    char str1[AKINATOR_MESSAGE_MAX_SIZE] = {},
         str2[AKINATOR_MESSAGE_MAX_SIZE] = {};
    printf_s("Please enter the criteria by which your person differs from guessed\n");
    CHECK_FUNC(My_scanf_s, 1, "%[^\n]%*1c", str1, AKINATOR_MESSAGE_MAX_SIZE);

    printf_s("Does your person satisfy this criteria?\n");
    if (check_answer()) {
        printf_s("What person are you thinking?\n");
        CHECK_FUNC(My_scanf_s, 1, "%[^\n]%*1c", str2, AKINATOR_MESSAGE_MAX_SIZE);
        printf_s("Thank you. You can try again\n");

        CHECK_FUNC(split_node, cur_node, cur_node->val, str2);
        free((char *)cur_node->val);
        CHECK_FUNC(My_strdup, &cur_node->val, str1);
    }
    else {
        printf_s("What person are you thinking?\n");
        CHECK_FUNC(My_scanf_s, 1, "%[^\n]%*1c", str2, AKINATOR_MESSAGE_MAX_SIZE);
        printf_s("Thank you. You can try again\n");

        CHECK_FUNC(split_node, cur_node, str2, cur_node->val);
        free((char *)cur_node->val);
        CHECK_FUNC(My_strdup, &cur_node->val, str1);
    }

    return 0;
}

errno_t Akinator(Bin_tree_node *const cur_node) {
    assert(cur_node);
    ON_DEBUG(
    errno_t verify_err = 0;
    CHECK_FUNC(Bin_tree_node_verify, cur_node, &verify_err);
    assert(!verify_err);
    )

    char str[AKINATOR_MESSAGE_MAX_SIZE] = {};
    if (cur_node->left == nullptr) {
        if (TREE_ELEM_EQUAL(cur_node->val, INITIAL_VAL)) {
            printf_s("I have no idea who could it be. Please enter someone\n");
            CHECK_FUNC(My_scanf_s, 1, "%[^\n]%*1c", str, AKINATOR_MESSAGE_MAX_SIZE);
            printf_s("Thank you. You can try again\n");

            free((char *)cur_node->val);
            CHECK_FUNC(My_strdup, &cur_node->val, str);

            return 0;
        }

        printf_s("Is it %s?\n", cur_node->val);
        if (check_answer()) {
            printf_s("Great! You can try again\n");
        }
        else {
            printf_s("Do you want to add new person?\n");
            if (check_answer()) {
                CHECK_FUNC(add_node, cur_node);
            }
        }
    }
    else {
        printf_s("%s?\n", cur_node->val);
        if (check_answer()) {
            CHECK_FUNC(Akinator, cur_node->right);
        }
        else {
            CHECK_FUNC(Akinator, cur_node->left);
        }
    }

    return 0;
}
