#include "Munola.h"
#include <stack>
#include <string>
#include <algorithm>
#include <vector>

float Munola::getFractionalDuration() const
{
    float d = 1.0;

    for (int i = 0; i < doubles; i++)
    {
        d *= 2.0;
    }

    for (int i = 0; i < halves; i++)
    {
        d *= 0.5;
    }

    for (int i = 0; i < dots; i++)
    {
        d *= 1.5;
    }

    return d;
}

int Munola::getMidiPitch()
{
    return 12 * (octave + 1 + octaveMod) + pitch;
}

void Munola::setPitch(const Munola &other)
{
    pitch = other.pitch;
    octave = other.octave;
    octaveMod = other.octaveMod;
}

std::string Munola::getDurationString() const
{
    std::string res = "";

    for (int i = 0; i < doubles; i++)
    {
        res += "+";
    }

    for (int i = 0; i < halves; i++)
    {
        res += "-";
    }

    for (int i = 0; i < dots; i++)
    {
        res += ".";
    }

    return res;
}

std::string Munola::to_string() const
{
    if (type == MunolaType::Note)
    {
        std::string res = "";

        // res += std::to_string(duration);
        res += getDurationString();

        int o = octaveMod;

        while (o > 0)
        {
            res += "^";
            o--;
        }

        while (o < 0)
        {
            res += "_";
            o++;
        }

        switch (pitch % 12)
        {
            case 0:   res += "C";  break; 
            case 1:   res += "#C"; break; 
            case 2:   res += "D";  break; 
            case 3:   res += "#D"; break; 
            case 4:   res += "E";  break; 
            case 5:   res += "F";  break; 
            case 6:   res += "#F"; break; 
            case 7:   res += "G";  break; 
            case 8:   res += "#G"; break; 
            case 9:   res += "A";  break; 
            case 10:  res += "#A"; break; 
            case 11:  res += "B";  break; 
        }

        return res;
    }

    if (type == MunolaType::Rest)
    {
        return getDurationString() + "r";
    }

    if (type == MunolaType::Command)
    {
        if (command == MunolaCommand::Octave)
        {
            return std::to_string(octave);
        }
    }

    if (type == MunolaType::Function)
    {
        std::string res = "";

        res += function + "(";

        for (int i = 0; i < args.size(); i++)
        {
            res += args[i];

            if (i < args.size() - 1)
            {
                res += ", ";
            }
        }

        res += ")";

        return res;
    }

    if (type == MunolaType::End)
    {
        return "";
    }

    return "?";
}

void Munola::print(std::string end)
{
    printf("%s%s", to_string().c_str(), end.c_str());
}

void split(const Munola &m, Munola *a, Munola *b)
{
    *a = m;
    a->duration *= 0.5;

    if (a->doubles > 0)
    {
        a->doubles -= 1;
    }
    else
    {
        a->halves += 1;
    }

    *b = *a;
}

bool isWhitespace(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

bool isLowerCaseLetter(char c)
{
    return c >= 'a' && c <= 'z';
}

int computeIntensity(const MunolaSequence &s)
{
    int intensity = 0;

    for (auto n : s)
    {
        intensity += n.halves - n.doubles;
    }

    return intensity;
}

float getSequenceDuration(std::vector<Munola> &vec)
{
    float duration = 0.0;

    for (int i = 0; i < vec.size(); i++)
    {
        Munola &m = vec[i];

        if (m.type == MunolaType::Note || m.type == MunolaType::Rest)
        {
            duration += m.getFractionalDuration();
        }
    }

    return duration;
}

std::vector<Munola> parseMunola(std::string text)
{
    std::vector<Munola> stack;

    Munola m;

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (text[i] >= 'A' && text[i] <= 'G')
        {
            m.type = MunolaType::Note;

            switch (text[i])
            {
            case 'C': m.pitch += 0; break;
            case 'D': m.pitch += 2; break;
            case 'E': m.pitch += 4; break;
            case 'F': m.pitch += 5; break;
            case 'G': m.pitch += 7; break;
            case 'A': m.pitch += 9; break;
            case 'B': m.pitch += 11; break;
            default:
                break;
            }

            stack.push_back(m);

            Munola newM;
            m = newM;
        }
        else if (c == 'R')
        {
            m.type = MunolaType::Rest;
            stack.push_back(m);
            Munola newM;
            m = newM;
        }
        else if (text[i] >= '0' && text[i] <= '9')
        {
            int octave = text[i] - '0';

            m.type = MunolaType::Command;
            m.command = MunolaCommand::Octave;
            m.octave = octave;
            stack.push_back(m);
            Munola newM;
            m = newM;
        }
        else if (text[i] == '^')
        {
            m.octaveMod++;
        }
        else if (text[i] == '_')
        {
            m.octaveMod--;
        }
        else if (text[i] == '+')
        {
            m.doubles++;
        }
        else if (text[i] == '-')
        {
            m.halves--;
        }
        else if (text[i] == '~')
        {
            m.isPhraseEnd = true;
        }
        else if (text[i] == '#')
        {
            m.pitch++;
        }
        else if (c == '.')
        {
            // dot = true;
        }
        else if (c == '!')
        {
            m.isAccented = true;
        }
        // we interpret a b as a flat if the following text does not look like
        // a function call.
        else if (text[i] == 'b' && i < text.length() - 1 && text[i+1] >= 'A' && text[i+1] <= 'Z')
        {
            m.pitch--;
        }
        else if (isWhitespace(c))
        {
            continue;
        }
        else if (isLowerCaseLetter(c))
        {
            // Parse function call.
            std::string name;

            while (text[i] >= 'a' && text[i] <= 'z')
            {
                name += text[i];
                i++;
            }

            // i will be incremented again by the outer for loop, so we need to
            // decrement it here.

            while (isWhitespace(text[i])) i++;

            if (text[i] != '(') printf("Expected '('\n");
            i++;

            std::vector<std::string> args;
            
            while (text[i] != ')')
            {
                std::string arg;
                while (text[i] != ',' && text[i] != ')')
                {
                    arg += text[i];
                    i++;
                }

                if (text[i] == ',') i++;

                args.push_back(arg);
            }

            m.type = MunolaType::Function;
            m.function = name;
            m.args = args;
            stack.push_back(m);
            Munola newM;
            m = newM;
        }
        else
        {
            printf("Warning, unexpected character '%c'\n", c);
        }
        
    }

    return stack;
}
