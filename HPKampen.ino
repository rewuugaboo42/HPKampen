/*
  File: HPKampen.ino
  Author: Simon Olesen
  Date: 2025-02-18
  Description: A quiz program that determines your advanced word vocabulary in swedish
*/

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

constexpr int buttonA{ 53 };
constexpr int buttonB{ 52 };
constexpr int buttonC{ 51 };
constexpr int buttonD{ 50 };

class Question
{
public:
  String question{};
  String answerA{};
  String answerB{};
  String answerC{};
  String answerD{};
  int rightAnswer{};

  Question(String q, String a, String b, String c, String d, int ra)
    : question(q)
    , answerA(a)
    , answerB(b)
    , answerC(c)
    , answerD(d)
    , rightAnswer(ra)
  {
  }
};

Question questionArray[] {
  {"domesticering", "inavel", "uppfostran", "avvänjning", "tämjning", 4},
  {"aktualitet", "information", "åsikt", "principfråga", "nyhet", 4},
  {"trojka", "diktator", "generalstab", "departement", "tremannavälde", 4},
  {"kokett", "behagsjuk", "yvig", "trossvag", "hämmande", 1},
  {"okvädingsord", "slagord", "dialektord", "skällsord", "nonsensord", 3},
  {"ge upphov till", "intyga ", "förändra", "orsaka", "uppmana", 3},
  {"kulmen", "intyga ", "förändra", "orsaka", "uppmana", 3},
  {"kommersiell", "skamsen", "förvirrad", "vinstinriktad", "närsynt", 3},
  {"abrupt", "oklart", "konstigt", "plötsligt", "onormalt", 3},
  {"anmodan", "säterstuga", "lurendrejeri", "åkkärra", "uppmaning", 4},
  {"strandsätta", "överta", "fullborda", "misslyckas", "överge", 4},
  {"aspartam", "blekmedel", "färgämne", "lugnande medel", "sötningsmedel", 4},
  {"uppfordrande", "upprepande", "utvärderande", "uppmanande", "utmärkande", 3},
  {"vanställa", "föreställa", "förfula", "förnedra", "förkasta", 2},
  {"anspråkslös", "utfattig", "förstummad", "obildad", "blygsam", 4},
  {"ypperligt", "uppenbart", "typiskt", "överdrivet", "utmärkt", 4},
  {"illustrera", "försköna", "bevisa", "markera", "belysa", 4},
  {"tunnsått", "svagt", "förminskande", "glest", "intetsägande" , 3},
  {"associera", "jämföra", "förknippa", "göra engelsk", "tala för", 2},
  {"föranleda", "orsaka", "övertyga", "tillföra", "godkänna", 1},
  {"illustrativ", "idealisk", "händelserik", "skenbar", "belysande", 4},
  {"med råge", "framför allt", "i stort sett", "med eftertryck", "väl tilltaget", 4},
  {"florera", "övertäcka", "frodas", "utsmycka", "lyckas", 2},
  {"krum", "böjd", "svag", "grym", "hård", 1},
  {"lekamen", "redskap", "kropp", "partikel", "gräns", 2},
  {"gångbar", "trolig", "stadig", "rörligt", "giltig", 4},
  {"parlör", "rådgivare", "förförare", "liten ordbok", "missöde", 3},
  {"klåpare", "presentatör", "släde", "fuskare", "hemlärarinna", 3},
  {"läckergom", "skämtare", "hedersman", "snygging", "finsmakare", 4},
  {"hieroglyf", "gravsten", "himlakropp", "bönbok", "skrivtecken", 4},
  {"implicera", "medföra", "ställa upp", "försvaga", "hålla fast", 1},
  {"kandelaber", "soppskål", "festtåg", "bakverk", "ljusstake", 4},
  {"vigör", "livskraft", "tapetvävnad", "sammanlöpande", "festmåltid", 1},
  {"röse", "skräp", "milstolpe", "fälla", "stenhög", 4},
  {"överlöpare", "ryttare", "förrädare", "stolt person", "inkräktare", 2},
  {"ordinera", "förmana", "konstatera", "föreskriva", "utskänka", 3},
  {"fradga", "rök", "ånga", "kyla", "skum", 4},
  {"snart sagt", "så gott som", "som väntat", "vanligtvis", "återkommande", 1},
  {"surrogat", "tillsats", "ersättning", "hjälpmedel", "avvikelse", 2},
  {"skälva", "krusa", "darra", "smälta", "närma", 2},
  {"åderlåta", "uppnå", "smyga", "avstå", "tömma", 4},
  /*{"bondsk", "lantlig", "självupptagen", "uppskattad", "besläktad", 1},
  {"således", "dessförinnan", "motsvarande", "visserligen", "följaktligen", 4},
  {"ackumulation", "tillvänjning", "avskiljande", "sammanställning", "anhopning", 4},
  {"bräcka", "utbrista", "avdela", "överträffa", "avbryta", 3},
  {"sparsmakad", "vanlig", "okritisk", "inåtvänd", "kräsen", 4},
  {"anestesi", "bedövning", "frigörelse", "raseriutbrott", "färgblindhet", 1},
  {"veto", "förbud", "fabeldjur", "urledvridning", "sjörövare", 1},
  {"anstötlig", "bristfällig", "hetsig", "upprörande", "ömtålig", 3},
  {"blott", "endast", "nästan", "öppet", "svagt", 1},
  */
};

// Get the size in bytes and get the difference between the whole array and the start of the array to get the length in int
constexpr int numQuestions = sizeof(questionArray) / sizeof(questionArray[0]);

void setup() 
{
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(3);

  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
  pinMode(buttonD, INPUT_PULLUP);

  tft.fillScreen(TFT_BLACK);

  Serial.begin(9600);

  shuffleQuestions(questionArray, numQuestions);
}

void loop() 
{
  for (int i{ 0 }; i < numQuestions; ++i)
  {
    drawQuestion(questionArray[i]);

    bool answered = false;

    int buttonStateA = digitalRead(buttonA);
    Serial.println(buttonStateA);
    int buttonStateB = digitalRead(buttonB);
    Serial.println(buttonStateB);
    int buttonStateC = digitalRead(buttonC);
    Serial.println(buttonStateC);
    int buttonStateD = digitalRead(buttonD);
    Serial.println(buttonStateD);

    // Wait for a question to be answered before exiting and running the main loop again
    while (!answered) {
      if (digitalRead(buttonA) == LOW) { checkAnswer(questionArray[i], 1); answered = true; }
      if (digitalRead(buttonB) == LOW) { checkAnswer(questionArray[i], 2); answered = true; }
      if (digitalRead(buttonC) == LOW) { checkAnswer(questionArray[i], 3); answered = true; }
      if (digitalRead(buttonD) == LOW) { checkAnswer(questionArray[i], 4); answered = true; }
    }

    delay(500);
  }

  shuffleQuestions(questionArray, numQuestions);
}

void drawCenteredText(const char* text, int rectX, int rectY, int rectWidth, int rectHeight) {
  int16_t x1, y1;
  uint16_t w, h;

  // Replacing å, ä and ö because it's not supported by my font a creates weird symbols if not replaced
  String modifiedText = text;
  modifiedText.replace("å", "a");
  modifiedText.replace("ä", "a");
  modifiedText.replace("ö", "o");

  tft.getTextBounds(modifiedText.c_str(), 0, 0, &x1, &y1, &w, &h);

  int textX = rectX + (rectWidth - w) / 2;
  int textY = rectY + (rectHeight - h) / 2;

  textY += h / 2;

  tft.setCursor(textX, textY);
  tft.print(modifiedText);
}

void drawQuestion(const Question& questionArr)
{
  tft.fillRect(90, 10, 300, 140, TFT_WHITE);

  tft.fillRect(15, 170, 220, 70, TFT_WHITE);
  tft.fillRect(15, 250, 220, 70, TFT_WHITE);
  tft.fillRect(245, 170, 220, 70, TFT_WHITE);
  tft.fillRect(245, 250, 220, 70, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);

  drawCenteredText(questionArr.question.c_str(), 90, 10, 300, 140);
  drawWordWithZAboveS(("A: " + questionArr.answerA).c_str(), 15, 170, 220, 70);
  drawWordWithZAboveS(("B: " + questionArr.answerB).c_str(), 245, 170, 220, 70);
  drawWordWithZAboveS(("C: " + questionArr.answerC).c_str(), 15, 250, 220, 70);
  drawWordWithZAboveS(("D: " + questionArr.answerD).c_str(), 245, 250, 220, 70);
}

void checkAnswer(const Question& q, int chosen)
{
  int color = (chosen == q.rightAnswer) ? TFT_GREEN : TFT_RED;

  switch (chosen) 
  {
    case 1: tft.fillRect(15, 170, 220, 70, color); drawCenteredText(("A: " + q.answerA).c_str(), 15, 170, 220, 70); break;
    case 2: tft.fillRect(245, 170, 220, 70, color); drawCenteredText(("B: " + q.answerB).c_str(), 245, 170, 220, 70); break;
    case 3: tft.fillRect(15, 250, 220, 70, color); drawCenteredText(("C: " + q.answerC).c_str(), 15, 250, 220, 70); break;
    case 4: tft.fillRect(245, 250, 220, 70, color); drawCenteredText(("D: " + q.answerD).c_str(), 245, 250, 220, 70); break;
  }

  delay(250);

  if (chosen != q.rightAnswer)
  {
    switch (q.rightAnswer) 
    {
      case 1: tft.fillRect(15, 170, 220, 70, TFT_GREEN); drawCenteredText(("A: " + q.answerA).c_str(), 15, 170, 220, 70); break;
      case 2: tft.fillRect(245, 170, 220, 70, TFT_GREEN); drawCenteredText(("B: " + q.answerB).c_str(), 245, 170, 220, 70); break;
      case 3: tft.fillRect(15, 250, 220, 70, TFT_GREEN); drawCenteredText(("C: " + q.answerC).c_str(), 15, 250, 220, 70); break;
      case 4: tft.fillRect(245, 250, 220, 70, TFT_GREEN); drawCenteredText(("D: " + q.answerD).c_str(), 245, 250, 220, 70); break;
    }
  }

  delay(1000);
}

// Changes the order of the questions each run in order to prevent memorizing the order
void shuffleQuestions(Question array[], int n) 
{
    for (int i = n - 1; i > 0; i--) 
    {
        int j = random(0, i + 1);
        Question temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}