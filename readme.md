# Munola

Munola is a simple, extensible, textual language for writing western music.

This repository contains the specification of Munola, as seen in the next section,
and a reference C++ implementation.

## Specification

White-key pitches of the equal-tempered scale are notated with upper case letters

```
C D E F G A B
```

The default octave is 4. A pitch can be raised or lowered one semitone by
pre-pending `#` or `b`, multiple accidentals can be applied to the same note, e.g.

```
#C bC ##C bbC #bC
```

which evaluates to C#, Cb, Cbb, and just C. Accidentals are not persistent as in
traditional western notation.

The octave of a note can be raised and lowered by ^ and _ e.g.

```
^C _C _#C
```

which evaluates to C5, C3, and C#3. The general octave can be selected by
writing the octave number

```
3 C D E 5 F G A
```

which evaluates to C3, D3, E3, F5, G5, and A5.

The default duration of a note is one beat. The duration can be doubled
using `+`, halved using `-`, and multiplied by 3/2 (dotted) using `.`, e.g.

```
+C ++C -C --C .+C
```

which evaluates to a two (2/4) beat, four (4/4) beat, 1/2 (1/8) beat, 1/4 (1/16)
beat, and a three beat note.

Rests are notated using R. All modifiers apply to rests, but pitch modifiers have no effect.

A note can be marked as the end of a phrase using ~, e.g.

```
C D ~E R F G ~A
```

which are two phrases, the first ending on E and the second on A. The first note
of the second phrase is a rest. Notes can be accented by prepending `!`.

Munola supports functions which are notated by

```
function(arg1, arg2, arg3)
```

the function name cane be any string of lower-case characters. A function may
have any number of arguments, including zero.

## C++ Implementation

The C++ implementation of the above specification is implemented in *Munola.h/.cpp*.
It is dependency free (apart from the STL) and ready to be included in your project.

Examples are provided in the *examples* folder. Take a look at *Munola.h* for
documentation of the implementation.

## License

Munola is provided uder the MIT license:

```
Copyright (c) Pelle Juul Christensen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## TODO

Munola and the C++ implementation contained here is still in early stages. This
is some of the stuff I would like to add

- Add support for nested function calls.
- Move code into a `Munola` namespace, such that `parseMunola` becomes `Munola::parse`.
- Add more examples.
- Add support for chords.
- Make a C implementation that can be used on embedded platforms.

