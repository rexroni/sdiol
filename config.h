#ifndef CONFIG_H
#define CONFIG_H

#include <regex.h>
#include <lua.h>

struct key_action_t;
typedef struct key_action_t key_action_t;

typedef struct {
    // members must not be addtional key_dual_t's
    key_action_t *tap;
    key_action_t *hold;
} key_dual_t;

enum key_type {
    KT_NONE,
    KT_SIMPLE,
    KT_DUAL,
    KT_MAP,
};

union key_union {
    int simple;
    key_dual_t dual;
    key_action_t *map; // always allocated to length of 256
    key_action_t *ref; // non-root keymaps with KT_NONE will have this filled
};

struct key_action_t {
    enum key_type type;
    union key_union key;
};

// a linked list of keyboard grabs or ignores passed by the user
typedef struct grab_t {
    // a compliled regex pattern
    regex_t regex;
    bool ignore;
    // except when ignore==true, map will always have type == KT_MAP:
    key_action_t map;
    struct grab_t *next;
} grab_t;

typedef struct {
    lua_State *L;
    grab_t *grabs;
} config_t;

config_t *config_new(const char* config_file);
void config_free(config_t *config);

#endif // CONFIG_H
