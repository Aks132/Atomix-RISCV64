#pragma once
typedef void (*command_handler_t)(); 

typedef struct {
    const char *name;               
    command_handler_t command_handler; 
} shell_command_t;

