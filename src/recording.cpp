#include "../include/music_header.h"

// Start recording notes
void start_recording(Piano &piano)
{
    piano.recording.clear();
    start_timer(piano.record_timer);
    piano.is_recording = true;
    piano.is_playing = false;
}

// Stop recording notes
void stop_recording(Piano &piano)
{
    stop_timer(piano.record_timer);
    piano.is_recording = false;
}

// Record a note event with timestamp
void handle_recording(Piano &piano, NoteType note)
{
    NoteEvent event;
    event.note = note;
    event.timestamp = timer_ticks(piano.record_timer);
    piano.recording.push_back(event);
}