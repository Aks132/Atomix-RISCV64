#include "shell.h"
    int x = 48;      
    int y = 16;      
    int count = 1;   

    char input_buffer[128];  
    int input_index = 0;    

void help_command(){
    x = 48;
    y += 16;
    draw_string(x, y, "Atomix shell Supported commands : ", 0xFFFFFF);
    x = 48;
    y += 16;
    draw_string(x,y ,"shutdown, ls & ps " , 0xFFFFFF);
}
void shutdown_command(){
    x = 48;
    y += 16;
    draw_string(x,y ,"Shutting down the machine ......" , 0xFFFFFF);
    while(1);
    }
void ls_command(){}
void ps_command(){
    x = 48;
    y += 16;
    draw_string(x,y ,"Shell is running" , 0xFFFFFF);
};
shell_command_t commands[] = {
    {"help" , help_command},
    {"shutdown" , shutdown_command},
    {"ls", ls_command},
    {"ps" , ps_command}
};

void shellInit() {
    draw_string(10, 0, "Welcome to Atomix", 0xFFFFFF); 
    draw_string(2, 16, "root: ", 0xFFFFFF);            

 

    while (1) {
        char ch = lib_getc();  
        if (ch) {
            if (ch == '\r') {  
                input_buffer[input_index] = '\0';  
                input_index = 0;
                int command_found = 0;  // Flag to indicate if command was found

                // Check for command match
                for (int command = 0; command < 4 && !command_found; command++) {
                    if (commands[command].name && !my_strcmp(commands[command].name, input_buffer)) {
                        commands[command].command_handler(); // Call the command handler
                        command_found = 1;  // Mark that we found and executed a command
                    }
                }

                x = 48;
                y += 16;
                
                if (y >= 200) {  
                    makeWhite();  
                    y = 16;          
                    draw_string(10, 0, "Welcome to Atomix", 0xFFFFFF); 
                }
                draw_string(2, y, "root: ", 0xFFFFFF);  
                count++;
            } else if (input_index < sizeof(input_buffer) - 1) { 
                input_buffer[input_index++] = ch;  
                draw_char(x, y, ch, 0xFFFFFF);     
                x += 8;                            
                
                if (x >= 300) {
                    x = 48;
                    y += 16;

                    if (y >= 200) {  
                        makeWhite();
                        y = 16;
                        draw_string(10, 0, "Welcome to Atomix", 0xFFFFFF); 
                    }
                    draw_string(2, y, "root: ", 0xFFFFFF);
                    count++;
                }
            }
        }
    }
}


