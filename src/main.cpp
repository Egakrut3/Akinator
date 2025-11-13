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

    MAIN_CHECK_FUNC(clear_file, "./Visual_html/Tree_log.html");

    size_t counter = 0;
    while (true) {
        printf_s("Do you want to start guessing?\n");
        if (!check_answer()) {
            break;
        }

        Akinator(cur_tree.root);

        FILE *dump_stream = nullptr;
        MAIN_CHECK_FUNC(fopen_s, &dump_stream, "./Visual_html/Tree_log.html", "a"); //TODO - possibly uw
        #undef FINAL_CODE
        #define FINAL_CODE              \
            Config_Dtor(&cur_config);   \
            Bin_tree_Dtor(&cur_tree);   \
            fclose(dump_stream);

        BIN_TREE_VISUAL_DUMP(cur_tree, dump_stream, counter, MAIN_CHECK_FUNC);
        ++counter;
        fclose(dump_stream);
        #undef FINAL_CODE
        #define FINAL_CODE              \
            Config_Dtor(&cur_config);   \
            Bin_tree_Dtor(&cur_tree);
    }

    colored_printf(GREEN, BLACK, "\n\n\nCOMMIT GITHUB\n\n");
    CLEAR_RESOURCES();
    return 0;
}
