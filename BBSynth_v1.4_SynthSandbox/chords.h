#define NOTE_C1   32.7
#define NOTE_Cs1  34.64
#define NOTE_D1   36.70
#define NOTE_Ds1  38.89

#define NOTE_E1   41.20
#define NOTE_F1   43.65
#define NOTE_Fs1  46.25
#define NOTE_G1   49.00
#define NOTE_Gs1  51.91
#define NOTE_A1   55.00
#define NOTE_As1  58.27
#define NOTE_B1   61.73
#define NOTE_C2   65.40
#define NOTE_Cs2  69.29
#define NOTE_D2   73.41
#define NOTE_Ds2  77.78

#define NOTE_E2   82.41
#define NOTE_F2   87.31
#define NOTE_Fs2  92.50
#define NOTE_G2   98.00
#define NOTE_Gs2 103.82
#define NOTE_A2  110.00
#define NOTE_As2 116.54
#define NOTE_B2  123.47
#define NOTE_C3  130.81
#define NOTE_Cs3 138.59
#define NOTE_D3  146.83
#define NOTE_Ds3 155.56
#define NOTE_E3  164.81
#define NOTE_F3  174.61
#define NOTE_Fs3 185.00
#define NOTE_G3  196.00
#define NOTE_Gs3 207.65
#define NOTE_A3  220.00
#define NOTE_As3 233.08
#define NOTE_B3  246.94
#define NOTE_C4  261.63
#define NOTE_Cs4 277.18
#define NOTE_D4  293.66
#define NOTE_Ds4 311.13
#define NOTE_E4  329.63
#define NOTE_F4  349.23
#define NOTE_Fs4 369.99
#define NOTE_G4  392.00
#define NOTE_Gs4 415.30
#define NOTE_A4  440.00
#define NOTE_As4 466.16
#define NOTE_B4  493.88

#define NOTE_C5  523.26
#define NOTE_Cs5 554.36
#define NOTE_D5  587.32
#define NOTE_Ds5 622.26
#define NOTE_E5  659.26
#define NOTE_F5  698.46
#define NOTE_Fs5 739.98
#define NOTE_G5  784.0
#define NOTE_Gs5 830.6
#define NOTE_A5  880.00
#define NOTE_As5 932.32
#define NOTE_B5  987.76

// The equation for note to frequency is:
// float freq = 440.0f * exp2f((float)(note - 69) * 0.0833333f);

// Map of MIDI note nunbers to frequencies:

const float NoteFreqMap[88][2] = {
  {24,  32.7},
  {25,  34.65},
  {26,  36.71},
  {27,  38.89},
  {28,  41.2},
  {29,  43.65},
  {30,  46.25},
  {31,  49},
  {32,  51.91},
  {33,  55},
  {34,  58.27},
  {35,  61.74},
  {36,  65.41},
  {37,  69.3},
  {38,  73.42},
  {39,  77.78},
  {40,  82.41},
  {41,  87.31},
  {42,  92.5},
  {43,  98},
  {44,  103.83},
  {45,  110},
  {46,  116.54},
  {47,  123.47},
  {48,  130.81},
  {49,  138.59},
  {50,  146.83},
  {51,  155.56},
  {52,  164.81},
  {53,  174.61},
  {54,  185},
  {55,  196},
  {56,  207.65},
  {57,  220},
  {58,  233.08},
  {59,  246.94},
  {60,  261.63},
  {62,  293.66},
  {63,  311.13},
  {64,  329.63},
  {65,  349.23},
  {66,  369.99},
  {67,  392},
  {68,  415.3},
  {69,  440},
  {70,  466.16},
  {71,  493.88},
  {72,  523.25},
  {73,  554.37},
  {74,  587.33},
  {75,  622.25},
  {76,  659.26},
  {77,  698.46},
  {78,  739.99},
  {79,  783.99},
  {80,  830.61},
  {81,  880},
  {82,  932.33},
  {83,  987.77},
  {84,  1046.5},
  {85,  1108.73},
  {86,  1174.66},
  {87,  1244.51},
  {88,  1318.51},
  {89,  1396.91},
  {90,  1479.98},
  {91,  1567.98},
  {92,  1661.22},
  {93,  1760},
  {94,  1864.66},
  {95,  1975.53},
  {96,  2093},
  {97,  2217.46},
  {98,  2349.32},
  {99,  2489.02},
  {100, 2637.02},
  {101, 2793.83},
  {102, 2959.96},
  {103, 3135.96},
  {104, 3322.44},
  {105, 3520},
  {106, 3729.31},
  {107, 3951.07}
};

// Map of MIDI note numbers to names:
// TODO: resolve int char conversion issue
const char noteNameMap[88][4] = {
  {'21', 'A', ' ', '0'},
  {'22', 'A', '#', '0'},
  {'23', 'B', ' ', '0'},
  {'24', 'C', ' ', '1'},
  {'25', 'C', '#', '1'},
  {'26', 'D', ' ', '1'},
  {'27', 'D', '#', '1'},
  {'28', 'E', ' ', '1'},
  {'29', 'F', ' ', '1'},
  {'30', 'F', '#', '1'},
  {'31', 'G', ' ', '1'},
  {'32', 'G', '#', '1'},
  {'33', 'A', ' ', '1'},
  {'34', 'A', '#', '1'},
  {'35', 'B', ' ', '1'},
  {'36', 'C', ' ', '2'},
  {'37', 'C', '#', '2'},
  {'38', 'D', ' ', '2'},
  {'39', 'D', '#', '2'},
  {'40', 'E', ' ', '2'},
  {'41', 'F', ' ', '2'},
  {'42', 'F', '#', '2'},
  {'43', 'G', ' ', '2'},
  {'44', 'G', '#', '2'},
  {'45', 'A', ' ', '2'},
  {'46', 'A', '#', '2'},
  {'47', 'B', ' ', '2'},
  {'48', 'C', ' ', '3'},
  {'49', 'C', '#', '3'},
  {'50', 'D', ' ', '3'},
  {'51', 'D', '#', '3'},
  {'52', 'E', ' ', '3'},
  {'53', 'F', ' ', '3'},
  {'54', 'F', '#', '3'},
  {'55', 'G', ' ', '3'},
  {'56', 'G', '#', '3'},
  {'57', 'A', ' ', '3'},
  {'58', 'A', '#', '3'},
  {'59', 'B', ' ', '3'},
  {'60', 'C', ' ', '4'},
  {'61', 'C', '#', '4'},
  {'62', 'D', ' ', '4'},
  {'63', 'D', '#', '4'},
  {'64', 'E', ' ', '4'},
  {'65', 'F', ' ', '4'},
  {'66', 'F', '#', '4'},
  {'67', 'G', ' ', '4'},
  {'68', 'G', '#', '4'},
  {'69', 'A', ' ', '4'},
  {'70', 'A', '#', '4'},
  {'71', 'B', ' ', '4'},
  {'72', 'C', ' ', '5'},
  {'73', 'C', '#', '5'},
  {'74', 'D', ' ', '5'},
  {'75', 'D', '#', '5'},
  {'76', 'E', ' ', '5'},
  {'77', 'F', ' ', '5'},
  {'78', 'F', '#', '5'},
  {'79', 'G', ' ', '5'},
  {'80', 'G', '#', '5'},
  {'81', 'A', ' ', '5'},
  {'82', 'A', '#', '5'},
  {'83', 'B', ' ', '5'},
  {'84', 'C', ' ', '6'},
  {'85', 'C', '#', '6'},
  {'86', 'D', ' ', '6'},
  {'87', 'D', '#', '6'},
  {'88', 'E', ' ', '6'},
  {'89', 'F', ' ', '6'},
  {'90', 'F', '#', '6'},
  {'91', 'G', ' ', '6'},
  {'92', 'G', '#', '6'},
  {'93', 'A', ' ', '6'},
  {'94', 'A', '#', '6'},
  {'95', 'B', ' ', '6'},
  {'96', 'C', ' ', '7'},
  {'97', 'C', '#', '7'},
  {'98', 'D', ' ', '7'},
  {'99', 'D', '#', '7'},
  {'100','E', ' ', '7'},
  {'101','F', ' ', '7'},
  {'102','F', '#', '7'},
  {'103','G', ' ', '7'},
  {'104','G', '#', '7'},
  {'105','A', ' ', '7'},
  {'106','A', '#', '7'},
  {'107','B', ' ', '7'}
};

/*
// according to http://www.guitar-chords.org.uk/
// and http://www.8notes.com/guitar_chord_chart/c.asp
//
              // open =  NOTE_E2  NOTE_A2  NOTE_D3  NOTE_G3  NOTE_B3  NOTE_E4
const float Cmajor[6] = {      0, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4, NOTE_E4};  // C - E - G
const float Dmajor[6] = {      0,       0, NOTE_D3, NOTE_A3, NOTE_D4, NOTE_Fs4}; // D - F# - A
const float Emajor[6] = {NOTE_E2, NOTE_B2, NOTE_E3, NOTE_Gs3,NOTE_B3, NOTE_E4};  // E - G# - B
const float Fmajor[6] = {      0, NOTE_A2, NOTE_F3, NOTE_A3, NOTE_C4, NOTE_F4};  // F - A - C
const float Gmajor[6] = {NOTE_G2, NOTE_B2, NOTE_D3, NOTE_G3, NOTE_B3, NOTE_E4};  // G - B - D
const float Amajor[6] = {      0, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_Cs4,NOTE_E4};  // A - C# - E
const float Bmajor[6] = {      0, NOTE_B2, NOTE_Fs3,NOTE_B3, NOTE_Ds4,NOTE_Fs4}; // B - D# - F#
const float Cminor[6] = {      0, NOTE_C3, NOTE_G3, NOTE_C4, NOTE_Ds4,NOTE_G4};  // C - D# - G
const float Dminor[6] = {      0,       0, NOTE_D3, NOTE_A3, NOTE_D4, NOTE_F4};  // D - F - A
const float Eminor[6] = {NOTE_E2, NOTE_B2, NOTE_E3, NOTE_G3, NOTE_B3, NOTE_E4};  // E - G - B
const float Fminor[6] = {NOTE_F2, NOTE_C3, NOTE_F3, NOTE_Gs3,NOTE_C4, NOTE_F4};  // F - G# - C
const float Gminor[6] = {NOTE_G2, NOTE_D3, NOTE_G3, NOTE_As3,NOTE_D3, NOTE_G4};  // G - A# - D
const float Aminor[6] = {      0, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_C4, NOTE_E4};  // A - C - E
const float Bminor[6] = {      0, NOTE_B2, NOTE_Fs3,NOTE_B3, NOTE_D4, NOTE_Fs4}; // B - D - F#

//                   E2, F2, F2#, G2, G2#, A2, A2#, B2
// C3, C3#, D3, D3#, E3, F3, F3#, G3, G3#, A3, A3#, B3
// C4, C4#, D4, D4#, E4, F4, F4#, G4, G4#, A4, A4#, B4
*/
