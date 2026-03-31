#pragma once
#include <3ds.h>

typedef struct {
    const char *chk_name;
    bool *var;
} Setting;

extern bool particlesDisabled;
extern bool wideEnabled;
extern bool glowEnabled; 
extern bool yJump;

void settings_init();
int settings_loop();