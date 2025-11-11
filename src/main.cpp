#include "Common.h"
#include "Option_manager.h"
#include "Bin_tree.h"
#include <string.h>
#include "Akinator.h"

int main(int const argc, char const *const *const argv) {
    assert(argc > 0); assert(argv);

    #undef FINAL_CODE
    #define FINAL_CODE

    Config cur_config = {};
    MAIN_CHECK_FUNC(Config_Ctor, &cur_config, argc, argv);
    #undef FINAL_CODE
    #define FINAL_CODE              \
        Config_Dtor(&cur_config);

    BIN_TREE_CTOR(MAIN_CHECK_FUNC, cur_tree);
    #undef FINAL_CODE
    #define FINAL_CODE              \
        Config_Dtor(&cur_config);   \
        Bin_tree_Dtor(&cur_tree);

    size_t const MESSAGE_MAX_SIZE = 10;
    char str[MESSAGE_MAX_SIZE] = {};
    while (true) {
        printf_s("Do you want to start guessing? Enter yes, if you do\n");
        CHECK_FUNC(My_scanf_s, 1, "%s%*1c", str, MESSAGE_MAX_SIZE);
        if (strcmp(str, "yes")) { //TODO -
            break;
        }

        Akinator(cur_tree.root);
    }

    FILE *dump_stream = nullptr;
    MAIN_CHECK_FUNC(fopen_s, &dump_stream, "./Visual_html/Tree_log.html", "w");
    #undef FINAL_CODE
    #define FINAL_CODE              \
        Config_Dtor(&cur_config);   \
        fclose(dump_stream);

    BIN_TREE_VISUAL_DUMP(cur_tree, dump_stream, MAIN_CHECK_FUNC);

    colored_printf(GREEN, BLACK, "\n\n\nCOMMIT GITHUB\n\n");
    CLEAR_RESOURCES();
    return 0;
}
