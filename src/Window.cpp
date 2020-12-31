#include "Window.h"

Window::Window() {
    window = SDL_CreateWindow("juice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_window.w, g_window.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_UpdateWindowSurface(window);
    g_window.rdr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    gameplay_texture = SDL_CreateTexture(g_window.rdr, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, 768, 768);
    other_texture = SDL_CreateTexture(g_window.rdr, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, 1000, 1000);
    SDL_SetTextureBlendMode(other_texture, SDL_BLENDMODE_BLEND);

    icon = IMG_Load("assets/player/red.png");
    if (!icon) SDL_Log("icon.png not loaded");
    SDL_SetWindowIcon(window, icon);
}

void Window::Clear() {

    SDL_SetRenderDrawColor(g_window.rdr, 100, 100, 0, 0);
    SDL_RenderClear(g_window.rdr);

    SDL_SetRenderTarget(g_window.rdr, other_texture);
    SDL_RenderClear(g_window.rdr);

    SDL_SetRenderDrawColor(g_window.rdr, 255, 255, 255, 255);
}

void Window::SetDrawGameplay() {
    SDL_SetRenderTarget(g_window.rdr, gameplay_texture);
}

void Window::SetDrawOther() {
    SDL_SetRenderTarget(g_window.rdr, other_texture);
}

void Window::Present(SDL_Rect* gameplay_viewport) {
    SDL_SetRenderTarget(g_window.rdr, NULL);
    SDL_RenderCopy(g_window.rdr, gameplay_texture, gameplay_viewport, NULL);
    other_texture_rect = {0, 0, g_window.w / g_window.scale, g_window.h / g_window.scale};
    SDL_RenderCopy(g_window.rdr, other_texture, & other_texture_rect, NULL);
    SDL_RenderPresent(g_window.rdr);
}


void Window::Shutdown() {
    SDL_Log("Shutting down window");
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(g_window.rdr);
    SDL_DestroyWindow(window);
}