#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
//#include <Fonts/Unifont.h>

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
  {"lekamen", "redskap", "kropp", "partikel", "gräns", 2}
};

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

  //tft.setFont(&Unifont);

  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int textX = rectX + (rectWidth - w) / 2;
  int textY = rectY + (rectHeight - h) / 2;

  textY += h / 2;

  tft.setCursor(textX, textY);
  tft.print(text);
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
  drawCenteredText(("A: " + questionArr.answerA).c_str(), 15, 170, 220, 70);
  drawCenteredText(("B: " + questionArr.answerB).c_str(), 245, 170, 220, 70);
  drawCenteredText(("C: " + questionArr.answerC).c_str(), 15, 250, 220, 70);
  drawCenteredText(("D: " + questionArr.answerD).c_str(), 245, 250, 220, 70);
}

void checkAnswer(const Question& q, int chosen)
{
  int color = (chosen == q.rightAnswer) ? TFT_GREEN : TFT_RED;

  switch (chosen) {
    case 1: tft.fillRect(15, 170, 220, 70, color); break;
    case 2: tft.fillRect(245, 170, 220, 70, color); break;
    case 3: tft.fillRect(15, 250, 220, 70, color); break;
    case 4: tft.fillRect(245, 250, 220, 70, color); break;
  }

  delay(250);

  if (chosen != q.rightAnswer)
  {
    switch (q.rightAnswer) {
      case 1: tft.fillRect(15, 170, 220, 70, TFT_GREEN); break;
      case 2: tft.fillRect(245, 170, 220, 70, TFT_GREEN); break;
      case 3: tft.fillRect(15, 250, 220, 70, TFT_GREEN); break;
      case 4: tft.fillRect(245, 250, 220, 70, TFT_GREEN); break;
    }
  }

  delay(1000);
}

void shuffleQuestions(Question array[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = random(0, i + 1);
        Question temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}