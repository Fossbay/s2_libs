
#define S2_WINDOW_IMPL
#include "s2_window.h"

int main(int argc, char* argv[])
{
    s2w_window window;
    s2w_attributes attributes;
    attributes.gl_samples = 4;
    attributes.gl_major_version = 3;
    attributes.gl_minor_version = 2;
    attributes.gl_profile = S2W_GL_COMPATIBILITY_PROFILE;
    window = s2w_CreateWindow("s2w_window ", S2W_WINDOW_DEFAULT,S2W_WINDOW_DEFAULT,S2W_WINDOW_DEFAULT,S2W_WINDOW_DEFAULT,  S2W_STYLE_DEFAULT, &attributes); 
    s2w_MakeCurrent(&window);
    s2w_event ev;
    while (window.open)
    {
        s2w_PollEvents(&window, &ev);
        
        switch (ev.type)
        {
            case S2W_WINDOW_QUIT:
            {
                s2w_CloseWindow(&window);
            } break;
            
            
            default : break;
        }
        
        switch (ev.mouse.state)
        {
            case (S2W_MOUSE_MIDDLE_MOVED) : 
            {
            } break;
            
            
            case (S2W_MOUSE_LEFT_UP) : 
            {
            } break;
            
            
            case (S2W_MOUSE_LEFT_DOWN) : 
            {
            } break;
            
            
            
            case (S2W_MOUSE_RIGHT_DOWN) :
            {
                
            } break;
            
            case (S2W_MOUSE_RIGHT_UP) :
            {
                
            } break;
            
            
            case (S2W_MOUSE_MIDDLE_DOWN): 
            {
                
            } break;
            
            case (S2W_MOUSE_MIDDLE_UP): {
                
            }; break;
            
            default : break;
            
        }
        printf("Time Elapsed : %lf\n", s2w_GetTime(&window.time));
        
        s2w_SwapBuffers(&window);
    }
    
    s2w_FreeWindow(&window);
}