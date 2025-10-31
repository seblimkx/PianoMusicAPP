#include "splashkit.h"
#include "../include/music_header.h"

int main()
{
    open_window("Piano App", 800, 600);

    // Initialize recordings directory
    initialize_recordings_directory();

    Piano piano;
    initialize_piano(piano); // Initialize logic (notes, colors, sounds, recording state)
    layout_piano(piano);     // Calculate GUI positions

    while (!quit_requested())
    {
        process_events();
        clear_screen(COLOR_ALICE_BLUE);

        // Handle state-specific logic
        switch (piano.current_state)
        {
        case PLAYING_PIANO:
            handle_playing_state(piano);
            draw_piano(piano);
            break;

        case GETTING_SAVE_FILENAME:
            handle_save_state(piano);
            draw_piano(piano);
            draw_save_gui(piano);
            break;

        case SHOWING_LOAD_MENU:
            handle_load_state(piano);
            draw_piano(piano);
            draw_load_gui(piano);
            break;
            
        case SHOWING_GUIDE:
            handle_guide_state(piano);
            draw_piano(piano);
            draw_guide_menu(piano);
            break;
            
        case SHOWING_KEYBINDS:
            handle_keybinds_state(piano);
            draw_piano(piano);
            draw_keybinds_menu(piano);
            break;
        }

        refresh_screen(60);
    }

    return 0;
}