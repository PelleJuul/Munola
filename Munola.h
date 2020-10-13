#pragma once

#include <stack>
#include <string>
#include <algorithm>
#include <vector>

/// Enumeration of the various types of Munola elements.
///
enum MunolaType
{
    Unknown,
    Command,
    Note,
    Rest,
    End,
    Function
};

/// Enumeration of the various Munola commands.
///
enum MunolaCommand
{
    None,
    Octave,
    Double,
    Halve,
    EndPhrase,
    Sharp,
    Flat,
};

/// The Munola class which represents a single Munola elements, e.g. a note,
/// rest, or function call.
class Munola
{
    public:

    /// Get a string representing the duration of this note --- a combination of
    /// `+`, `-`, and `.`.
    /// @returns    A string representing the duration of this note.
    std::string getDurationString() const;

    /// The the duration as a fractional number in beats. For example the
    /// fractional duration for `.C` will be 1.5.
    /// @returns    The fractional duration in beats.
    float getFractionalDuration() const;

    /// Get the MIDI pitch number of this note.
    /// @returns    The MIDI pitch.
    int getMidiPitch() const;

    /// Print a string representation of this note to std::out.
    /// @param  end     What to print after the generated string.
    void print(std::string end="\n");

    /// Parse a string into a vector of Munola objects.
    /// @param  text    The text to parse.
    /// @returns        A vector of the parsed Munola objects.
    static std::vector<Munola> parse(std::string text);

    /// Set the pitch of this note from another note.
    /// @param  other   The other note whose pitch will be copied.
    void setPitch(const Munola &other);

    /// Get a string representing the duration of this note.
    /// @returns    A string representing the duration of this note.
    operator std::string() const
    {
        return to_string();
    };

    /// Get a string representing the duration of this note.
    /// @returns    A string representing the duration of this note.
    std::string to_string() const;

    private:
    MunolaType type = MunolaType::Unknown;
    MunolaCommand command = MunolaCommand::None;
    std::string function = "";
    std::vector<std::string> args;
    bool isPhraseEnd = false;
    bool isAccented = false;
    int octave = 4;
    int pitch = 0;
    int doubles = 0;
    int halves = 0;
    int dots = 0;
    float duration = 1.0;
    int octaveMod = 0;
};