#pragma once

#include <stack>
#include <string>
#include <algorithm>
#include <vector>

enum MunolaType
{
    Unknown,
    Command,
    Note,
    Rest,
    End,
    Function
};

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

struct Munola
{
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

    float getFractionalDuration() const;
    int getMidiPitch();

    std::string getDurationString() const;

    std::string to_string() const;

    void setPitch(const Munola &other);

    void print(std::string end="\n");

    operator std::string() const
    {
        return to_string();
    };
};

using MunolaSequence = std::vector<Munola>;
using SequenceCollection = std::vector<MunolaSequence>;

void split(const Munola &m, Munola *a, Munola *b);

void evalMunola(std::vector<Munola> &stack);

int computeIntensity(const MunolaSequence &s);

float getSequenceDuration(std::vector<Munola> &vec);

std::vector<Munola> parseMunola(std::string text);