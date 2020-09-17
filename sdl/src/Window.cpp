#include "Window.hpp"

Window::Window() {
    window = SDL_CreateWindow("juice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, global_window_data.w, global_window_data.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_UpdateWindowSurface(window);
    global_window_data.rdr = SDL_CreateRenderer(window, -1, NULL);

    gameplay_texture = SDL_CreateTexture(global_window_data.rdr, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, 768, 768);
    other_texture = SDL_CreateTexture(global_window_data.rdr, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, 1000, 1000);
    SDL_SetTextureBlendMode(other_texture, SDL_BLENDMODE_BLEND);

    icon = IMG_Load("assets/player/red.png");
    if (!icon) SDL_Log("icon.png not loaded");
    SDL_SetWindowIcon(window, icon);
}

void Window::Clear() {

    SDL_SetRenderDrawColor(global_window_data.rdr, 100, 100, 0, 0);
    SDL_RenderClear(global_window_data.rdr);

    SDL_SetRenderTarget(global_window_data.rdr, other_texture);
    SDL_RenderClear(global_window_data.rdr);

    SDL_SetRenderDrawColor(global_window_data.rdr, 255, 255, 255, 255);
}

void Window::SetDrawGameplay() {
    SDL_SetRenderTarget(global_window_data.rdr, gameplay_texture);
}

void Window::SetDrawOther() {
    SDL_SetRenderTarget(global_window_data.rdr, other_texture);
}

void Window::Present(SDL_Rect* gameplay_viewport) {
    SDL_SetRenderTarget(global_window_data.rdr, NULL);
    SDL_RenderCopy(global_window_data.rdr, gameplay_texture, gameplay_viewport, NULL);
    other_texture_rect = {0, 0, global_window_data.w / global_window_data.scale, global_window_data.h / global_window_data.scale};
    SDL_RenderCopy(global_window_data.rdr, other_texture, & other_texture_rect, NULL);
    SDL_RenderPresent(global_window_data.rdr);
}


void Window::Shutdown() {
    SDL_Log("Shutting down window");
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(global_window_data.rdr);
    SDL_DestroyWindow(window);
}