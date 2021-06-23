/* 

(c) fossbay
s2_window.h 1.0 
< apart of the s2_libs library >
information: window abstraction layer.
licence : unlicence 
for more information, scroll down to the the bottom.
____________________________________________
Examples;

``` Creating a generic window. 
#define S2_WINDOW_IMPL
#include "s2_window.h"

int main(int argc, char* argv[])
{

s2w_window window;
    s2w_attributes attributes;
    attributes.gl_samples = 4;
        
    attributes.gl_major_version = 4;
    attributes.gl_minor_version = 5;
    attributes.gl_profile = S2W_GL_COMPATIBILITY_PROFILE;
    window = s2w_CreateWindow("s2w_window ", S2W_WINDOW_DEFAULT,S2W_WINDOW_DEFAULT,S2W_WINDOW_DEFAULT,S2W_WINDOW_DEFAULT, S2W_STYLE_DEFAULT , &attributes);
        
    s2w_MakeCurrent(&window); 
    // Load OpenGL 
s2w_event ev;

while (window.open)
{
    s2w_PollEvents(&window, &ev);
    if (ev.type == S2W_WINDOW_QUIT)
    {
        s2w_CloseWindow(&window);
    }

// drawing

    s2w_SwapBuffers(&window);
}
s2w_FreeWindow(&window);
}
```
_______________________
``` Mouse, Cursor, and flags.

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
        
        
        s2w_SwapBuffers(&window);
    }
    
    s2w_FreeWindow(&window);
}
```
_________________________

*/


#ifndef S2_WINDOW_H
#define S2_WINDOW_H


#ifndef S2W_MALLOC 
#include <malloc.h>
#define S2W_MALLOC malloc
#endif 



#ifndef S2W_FREE 
#include <malloc.h>
#define S2W_FREE free
#endif 


#ifndef S2W_PRINTF 
#include <io.h>
#define S2W_PRINTF printf
#endif 


typedef enum 
{
    S2W_STYLE_CLOSE = 1 << 1,
    S2W_STYLE_RESIZEABLE = 1 << 2,
    S2W_STYLE_MINIMIZE = 1 << 3,
    S2W_STYLE_MAXIMIZE = 1 << 4,
    S2W_STYLE_HIDDEN    = 1 << 5,
    S2W_STYLE_LEGACYGL = 1 << 6,
    S2W_STYLE_DEFAULT = (S2W_STYLE_CLOSE |S2W_STYLE_MINIMIZE |S2W_STYLE_MAXIMIZE |S2W_STYLE_RESIZEABLE)
} s2w_window_style_flags;


typedef enum
{
    S2W_WINDOW_QUIT = 1 << 1,
    S2W_WINDOW_RESIZE = 1<< 2
        
} s2w_window_events;

typedef struct
{
    double start;
    double end;
    int freq;
} s2w_time;

typedef struct
{
    
    char *title;
    float x;
    float y;
    float w;
    float h;
    unsigned int open;
    
    struct 
    {
        void *handle;
    } os;
    
    struct 
    {
        void *handle;
    } graphics;
    
    s2w_time time;
    
} s2w_window;

typedef enum
{
    
    S2W_MOUSE_LEFT_UP     = 1<<1 ,
    S2W_MOUSE_RIGHT_UP    = 1<<2,
    S2W_MOUSE_MIDDLE_UP   = 1<<3,
    
    S2W_MOUSE_LEFT_DOWN   = 1<<4, 
    S2W_MOUSE_RIGHT_DOWN  = 1<<5,
    S2W_MOUSE_MIDDLE_DOWN = 1<<6,
    S2W_MOUSE_NONE =        1<<7,
    S2W_MOUSE_MIDDLE_MOVED = 1 << 8,
    
}s2w_click_state ;


typedef enum
{
    S2W_KEY_DOWN = 1 << 1,
    S2W_KEY_UP   = 1 << 2,
    /* NOTE(rxx): S2W_SYS prefix is for ALT keys. refer to MSDN documentation */ 
    S2W_SYS_KEY_DOWN = 1 << 3,
    S2W_SYS_KEY_UP   = 1 << 4,
    S2W_KEY_NONE = 1 << 5
        
}s2w_key_state ;

typedef struct
{
    int gl_samples;
    int gl_major_version;
    int gl_minor_version;
    enum {S2W_GL_CORE_PROFILE = 1<<1,S2W_GL_COMPATIBILITY_PROFILE = 1<<2} gl_profile;
    
    
} s2w_attributes;

typedef struct 
{
    float x;
    float y;
    s2w_click_state state;
} s2w_mouse;

typedef struct 
{
    wchar_t key;
    s2w_key_state state;
} s2w_keyboard;



typedef struct
{
    s2w_mouse mouse;
    s2w_keyboard key;
    s2w_window_events type;
    
} s2w_event;
s2w_window s2w_CreateWindow(char* title, float x, float y, float w, float h, s2w_window_style_flags window_flags, s2w_attributes* attributes );

void s2w_CloseWindow(s2w_window* window);

void s2w_FreeWindow(s2w_window* window);

void s2w_PollEvents(s2w_window* window, s2w_event* event);

void s2w_SwapBuffers(s2w_window* window);

void s2w_MakeCurrent(s2w_window* window);

void s2w_StartTime(s2w_time* time);
double s2w_GetTime(s2w_time* time);


#if defined(_WIN32) | defined(_WIN64) && defined(S2_WINDOW_IMPL)
/* NOTE(rxx): CW_USEDEFAULT is a function that calculate the screen size and the monitor size and creates a appropriate window releative to the screen. For more information refer to MSDN */
#define S2W_WINDOW_DEFAULT CW_USEDEFAULT
/* NOTE(rxx):  WIN32_LEAN_AND_MEAN just provides a skimmed down version of windows.h */
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Windowsx.h>


#include <gl/gl.h>
#include "GL/glext.h"
#include "GL/wglext.h"





static s2w_mouse    s2wp_global_mouse;
static s2w_keyboard s2wp_key_data;
static s2w_window_events s2wp_window_events;

typedef struct
{
    
    HWND window;
    
} s2wp_win32_handle;

typedef struct
{
    
    HDC device_context;
    HGLRC render_context;
    
} s2wp_win32_opengl;

#include <stdio.h>

static LRESULT CALLBACK  sw2pWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    
    
    switch (message)
    {
        case WM_CLOSE : 
        {
            PostQuitMessage(0);
            return 0;
        } break;
        
        case WM_MOUSEMOVE : 
        {
            
            s2wp_global_mouse.x = GET_X_LPARAM(lParam);
            s2wp_global_mouse.y = GET_Y_LPARAM(lParam);
            
        } break;
        
        case WM_LBUTTONDOWN :
        {
            
            s2wp_global_mouse.state = S2W_MOUSE_LEFT_DOWN;
        } break;
        case WM_LBUTTONUP :
        {
            
            s2wp_global_mouse.state = S2W_MOUSE_LEFT_UP;
        } break;
        
        
        case WM_MOUSEWHEEL :
        {
            
            s2wp_global_mouse.state = S2W_MOUSE_MIDDLE_MOVED;
        } break;
        case WM_RBUTTONDOWN :
        {
            
            s2wp_global_mouse.state = S2W_MOUSE_RIGHT_DOWN;
        } break;
        case WM_RBUTTONUP :
        {
            
            s2wp_global_mouse.state = S2W_MOUSE_RIGHT_UP;
        } break;
        case WM_SYSKEYDOWN:
        {
            s2wp_key_data.state = S2W_SYS_KEY_DOWN;
            s2wp_key_data.key = wParam;
        }
        break;
        
        case WM_SYSCHAR:
        {
            s2wp_key_data.key = (wchar_t)wParam;
        }
        break;
        
        case WM_SYSKEYUP:
        {
            s2wp_key_data.key = wParam;
            s2wp_key_data.state = S2W_SYS_KEY_UP;
        }
        break;
        
        case WM_KEYDOWN:
        {
            s2wp_key_data.key = wParam;
            s2wp_key_data.state = S2W_KEY_DOWN;
        }
        break;
        
        case WM_KEYUP:
        {
            s2wp_key_data.key = wParam;
            s2wp_key_data.state = S2W_KEY_UP;
        }
        break;
        
        case WM_CHAR:
        {
            s2wp_key_data.key = wParam;
            
        }
        break;
        
        
        
        case WM_MBUTTONDOWN :
        {
            
            s2wp_global_mouse.state = S2W_MOUSE_MIDDLE_DOWN;
        } break;
        case WM_MBUTTONUP :
        {
            
            s2wp_global_mouse.state = S2W_MOUSE_MIDDLE_UP;
        } break;
        
        
        case WM_SIZE :
        {
            s2wp_window_events = S2W_WINDOW_RESIZE;
        } break;
        
        case WM_DESTROY: 
        {
            PostQuitMessage(0);
            return 0;
        } break;
        
        default : 
        {
            s2wp_key_data.state = S2W_KEY_NONE;
            s2wp_global_mouse.state = S2W_MOUSE_NONE;
            
            result = DefWindowProc(window, message , wParam , lParam);
            return result;
        };
    };
    
    return result;
    
    
}



void s2w_StartTime(s2w_time* time)
{
    LARGE_INTEGER freq_time;
    QueryPerformanceFrequency(&freq_time);
    time->freq = freq_time.QuadPart;
    
    LARGE_INTEGER start;
    QueryPerformanceCounter(&start);
    time->start = start.QuadPart;
    
    
}
double s2w_GetTime(s2w_time* time)
{
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    time->end = end.QuadPart;
    
    return (time->end - time->start) / time->freq;
}
static s2wp_win32_handle* s2wp_GetWindowHandle(s2w_window* window)
{
    s2wp_win32_handle* handler = (s2wp_win32_handle*)window->os.handle;
    return handler;
    
}


static s2wp_win32_opengl* s2wp_GetGraphicsHandle(s2w_window* window)
{
    s2wp_win32_opengl* handler = (s2wp_win32_opengl*)window->graphics.handle;
    return handler;
    
}



void s2w_MakeCurrent(s2w_window* window)
{
    s2wp_win32_opengl* gfx = s2wp_GetGraphicsHandle(window);
    if (wglMakeCurrent(gfx->device_context, gfx-> render_context) == 0){
        S2W_PRINTF("s2w.Error: Failed to set OpenGL render-context current. \n");
    }
    
    
    
    
    
}

s2w_window s2w_CreateWindow(char* title, float x, float y, float w, float h, s2w_window_style_flags window_flags,s2w_attributes* attributes )
{
    
    
    s2w_window window;
    s2w_StartTime(&window.time);
    if (attributes == (void*)0)
    {
        s2w_attributes attributes1;
        attributes1.gl_samples = 4;
        attributes1.gl_major_version = 3;
        attributes1.gl_minor_version = 4;
        attributes1.gl_profile = S2W_GL_COMPATIBILITY_PROFILE;
        attributes = &attributes1;
    }
    window.os.handle = S2W_MALLOC(sizeof(s2wp_win32_handle));
    window.graphics.handle = S2W_MALLOC(sizeof(s2wp_win32_opengl));
    s2wp_win32_handle* handle = s2wp_GetWindowHandle(&window);
    s2wp_win32_opengl* handle_gl = s2wp_GetGraphicsHandle(&window);
    HINSTANCE instance = GetModuleHandle(0);
    WNDCLASS window_class = {0};
    window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = sw2pWindowProc;
    window_class.lpszClassName = title;
    window_class.hInstance= instance;
    window_class.hCursor = LoadCursor(0, IDC_ARROW);
    RegisterClass(&window_class);
    HINSTANCE hInstance= GetModuleHandle(0);
    
    
    
    HWND window_hwnd;
    
    
    DWORD styles = 0;
    
    if (window_flags& S2W_STYLE_CLOSE)
        styles += WS_SYSMENU;
    if (window_flags & S2W_STYLE_RESIZEABLE)
        styles += WS_THICKFRAME;
    if (window_flags & S2W_STYLE_MINIMIZE)
        styles += WS_MINIMIZEBOX;
    if (window_flags & S2W_STYLE_MAXIMIZE)
        styles += WS_MAXIMIZEBOX;
    if (!(window_flags & S2W_STYLE_HIDDEN))
        styles += WS_VISIBLE;
    
    if (window_hwnd = CreateWindowEx(WS_EX_APPWINDOW,window_class.lpszClassName,window_class.lpszClassName,styles,x,y,w,h,0,0,instance,0))
    {
        window.open =1;
        RECT client_rect;
        GetWindowRect(window_hwnd, &client_rect);
        /* NOTE: We aren't really passing the parameter directly as using default flags such as CW_USE_DEFAULT for the sizing will not return the proper values. */
        window.x = client_rect.left;
        window.y = client_rect.top;
        window.w = client_rect.right - client_rect.left;
        window.h = client_rect.bottom - client_rect.top;
        
        
        if ((window_flags & S2W_STYLE_LEGACYGL)){
            
            PIXELFORMATDESCRIPTOR pixel_format = {0};
            pixel_format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
            pixel_format.nVersion = 1;
            pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
            pixel_format.iPixelType = PFD_TYPE_RGBA;
            pixel_format.cColorBits = 32;
            pixel_format.cDepthBits = 24;
            pixel_format.cAlphaBits = 8;
            pixel_format.iLayerType = PFD_MAIN_PLANE;
            
            
            HDC device_context = GetDC(window_hwnd);
            
            
            int pixel_format_int= ChoosePixelFormat(device_context, &pixel_format);
            if (pixel_format_int == 0)
                S2W_PRINTF("s2w.Error: Failed to get pixel format \n");
            
            
            if (SetPixelFormat(device_context, pixel_format_int, &pixel_format ) == 0)
            {
                S2W_PRINTF("s2w.Error: Failed to set pixel format \nMore information:\nPlatform: Win32\nLocated at: (function)( s2w_CreateWindow)\nError:  SetPixelFormat");
            }
            
            HGLRC opengl_rendercontext;
            
            opengl_rendercontext = wglCreateContext(device_context);
            if (!(opengl_rendercontext))
            {
                S2W_PRINTF("s2w.Error: Failed loading OpenGL rendering context\n");
            }
            
            handle_gl->device_context = device_context;
            handle_gl->render_context = opengl_rendercontext;
            
        } else 
        {
            
            
            HDC tDC = GetDC(window_hwnd);
            PIXELFORMATDESCRIPTOR tformat = {0};
            tformat.nSize = sizeof(tformat);
            tformat.nVersion = 1;
            tformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
            tformat.iPixelType = PFD_TYPE_RGBA;
            tformat.cColorBits = 32;
            tformat.cAlphaBits = 8;
            tformat.cDepthBits = 24;
            
            int tSuggestedPixelFormatID  = ChoosePixelFormat(tDC, &tformat);
            if ((tSuggestedPixelFormatID )== 0)
                S2W_PRINTF("s2w.Error: Failed to find a suitable pixel format.\n");
            
            if (SetPixelFormat(tDC, tSuggestedPixelFormatID, &tformat) == 0)
                S2W_PRINTF("s2w.Error: Couldn't set a pixel format.\n");
            
            HGLRC tRC  = wglCreateContext(tDC);
            if ((tRC) == 0)
                S2W_PRINTF("s2w.Error: WGL : Couldn't generate a valid rendering context for OpenGL.\n");
            
            
            
            if (wglMakeCurrent(tDC, tRC) == 0)
                S2W_PRINTF("s2w.Error: WGL : Failed to set OpenGL render-context current. \n");
            
            PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB  = 0;
            PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB  = 0;
            
            wglChoosePixelFormatARB =  (PFNWGLCHOOSEPIXELFORMATARBPROC)(wglGetProcAddress("wglChoosePixelFormatARB"));
            if (wglChoosePixelFormatARB  ==  0)
            {
                S2W_PRINTF("s2w.Error: WGL: Failed to fetch wglChoosePixelFormatARB  \n");
            };
            
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)(wglGetProcAddress("wglCreateContextAttribsARB"));
            if ( wglCreateContextAttribsARB == 0) {
                
                S2W_PRINTF("s2w.Error: WGL:  Failed to fetch wglCreateContextAttribsARB  \n");
            }
            
            
            HDC MainContext = GetDC(window_hwnd);
            
            const int OpenGLAttributes[] = {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
                WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
                WGL_COLOR_BITS_ARB, 32,
                WGL_ALPHA_BITS_ARB, 8,
                WGL_DEPTH_BITS_ARB, 24,
                WGL_STENCIL_BITS_ARB, 8,
                WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
                WGL_SAMPLES_ARB, attributes->gl_samples,
                0
            };
            
            int MainSuggestedPixelFormatID;
            
            unsigned int Formats;
            
            
            if (wglChoosePixelFormatARB(MainContext, OpenGLAttributes, 0, 1, &MainSuggestedPixelFormatID, &Formats) == 0 || Formats == 0)
                S2W_PRINTF("s2w.Error: WGL: Couldn't find a good pixel format. \n");
            
            
            int profile = attributes->gl_profile == S2W_GL_CORE_PROFILE ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB   : WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
            int  GLContextAttributes[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, attributes->gl_major_version,
                WGL_CONTEXT_MINOR_VERSION_ARB, attributes->gl_minor_version,
                WGL_CONTEXT_PROFILE_MASK_ARB, profile ,
                0
            };
            
            HGLRC RenderContext = wglCreateContextAttribsARB(MainContext, 0, GLContextAttributes);
            if (!RenderContext )
                S2W_PRINTF("s2w.Error: WGL: failed on creating a render context. \n");
            
            if (!wglMakeCurrent(0,0))
                S2W_PRINTF("s2w.Error: WGL: Failed to get a default current.. \n");
            
            handle_gl->device_context = MainContext;
            handle_gl->render_context = RenderContext;
            
            
            
            
            
        };
        
        
        
        
        
        
        
        
        
    } 
    else 
    {
        
        S2W_PRINTF("s2w.Fatal: Failed creating a window.");
        
    }
    handle->window = window_hwnd;
    return window;
}
void s2w_CloseWindow(s2w_window* window)
{
    window->open = 0;
    
}


void s2w_PollEvents(s2w_window* window,  s2w_event* event)
{
    
    s2wp_win32_handle* handle = s2wp_GetWindowHandle(window);
    event->key = s2wp_key_data;
    event->mouse.x = s2wp_global_mouse.x; 
    event->mouse.y = s2wp_global_mouse.y; 
    event->mouse.state  = s2wp_global_mouse.state;
    event->type = s2wp_window_events;
    MSG message;
    while(PeekMessage(&message , 0 ,0 ,0 ,PM_REMOVE))
    {
        
        if (message.message == WM_QUIT)
        {
            s2wp_window_events = S2W_WINDOW_QUIT;
            
        }
        
        TranslateMessage(&message);
        DispatchMessage(&message);
        
    }
}

void s2w_FreeWindow(s2w_window* window)
{
    
    s2wp_win32_handle* handle = s2wp_GetWindowHandle(window);
    s2wp_win32_opengl* gfx = s2wp_GetGraphicsHandle(window);
    ReleaseDC(handle->window, gfx->device_context);
    wglDeleteContext(gfx->render_context);
    DestroyWindow(handle->window);
    S2W_FREE(window->os.handle);
    S2W_FREE(window->graphics.handle);
}


void s2w_SwapBuffers(s2w_window* window)
{
    
    
    s2wp_win32_opengl* gfx = s2wp_GetGraphicsHandle(window);
    SwapBuffers(gfx->device_context);
}



#endif



#else

#error s2w doesn't support this OS.  

#endif
/*

developed by fossbay.
apart of the s2_libaries package.
 s2_window.h

Brief: Do whatever you want. 

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/> 
*/