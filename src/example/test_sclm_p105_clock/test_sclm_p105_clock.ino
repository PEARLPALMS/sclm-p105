 /**
 * SCLM-P105
 * 2021/03/09 Tue pearlpalms@gmail.com
 * $Id:$
 *
 * SCLM-P105 <-> Arduino
 *  (VSS)  1 <-> GND
 *  (VDD)  2 <-> +5V
 *   (NC)  3 <-> ---
 * (BUSY)  4 <-> D2
 *  (CLK)  5 <-> D3
 *  (/CS)  6 <-> D4
 *  (DB0)  7 <-> D5
 *  (DB1)  8 <-> D6
 *  (DB2)  9 <-> D7
 *  (DB3) 10 <-> D8
 *  (DB4) 11 <-> D9
 *  (DB5) 12 <-> D10
 *  (DB6) 13 <-> D11
 *  (DB7) 14 <-> D12
 */

// SCLM_P105ライブラリ
#include <sclm_p105.h>

// デバッグ
#define DEBUG
#undef DEBUG
#define DEBUG_BPS 115200

// 時刻ライブラリ
#include <Time.h>
#include <TimeLib.h>

// 秒間フレーム数
#define FPS 60

// コンパイルから転送までの秒数
#define DELAY 7

// 秒間フレーム数
#define FPS 60

// 時刻オブジェクト
tmElements_t tm;

// 退避秒
int oldSecond = 0;

// ピン定義
#define BUSY 2
#define  CLK 3
#define   CS 4
#define  DB0 5
#define  DB1 6
#define  DB2 7
#define  DB3 8
#define  DB4 9
#define  DB5 10
#define  DB6 11
#define  DB7 12

// SCLM_P105クラス
SCLM_P105 sclm(BUSY, CLK, CS, DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7);

/**
 * 初期化処理
 */
void setup(){

  // シリアルポート初期化
#ifdef DEBUG
  Serial.begin(DEBUG_BPS);
  while(!Serial);
  Serial.sclm.println(F("SCLM-P105 Test $Id:$ " __FILE__));
#endif // DEBUG

  // SCLM初期化
  sclm.begin();

  // LEDピン設定
  pinMode(LED_BUILTIN, OUTPUT);

  // コンパイルから転送までの時間修正
  int i = String(__TIME__).lastIndexOf(":") + 1;
  int j = String(__TIME__).substring(i).toInt();
  if(j > 60 - DELAY)
    Serial.println("ERROR!! Try next run");
  j += DELAY;
  String s = String(__TIME__).substring(0, i);
  s.concat(j);

  // 時刻パース
  if(getDate(__DATE__) && getTime(s.c_str()))
    setTime(makeTime(tm));
}

/**
 * ループ処理
 */
void loop(){

  // 秒が更新されると表示更新
  if(oldSecond != second()){
    oldSecond = second();
    for(int i = 0; i < 10; i++){
      digitalWrite(LED_BUILTIN, LOW);
      delay(16 - i);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(i);
    }
    // 時
    sclm.data[22] = hour() / 10 + LED_WHITE;
    sclm.data[23] = hour() % 10 + LED_WHITE;
    // 分
    sclm.data[24] = minute() / 10 + LED_WHITE;
    sclm.data[25] = minute() % 10 + LED_WHITE;
    // 秒
    sclm.data[17] = second() / 10 + LED_WHITE;
    sclm.data[18] = second() % 10 + LED_WHITE;
    sclm.update();

#ifdef DEBUG
    char s[30];
    sprintf(s, "%04d/%02d/%02d %02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());
    Serial.println(s);
#endif // DEBUG
    for(int i = 10; i > 0; i--){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(i);
      digitalWrite(LED_BUILTIN, LOW);
      delay(16 - i);
    }
  }

  // 待機
  delay(1000 / FPS);
}

/**
 * __TIME__ から構造体へ値を設定
 * s: __TIME__ 文字列
 * return: true 正常 false エラー
 */
bool getTime(const char *s){

  int hh, mm, ss;

  // __TIME__ から文字列を取得
  if(sscanf(s, "%d:%d:%d", &hh, &mm, &ss) != 3)
    return(false);

  // 構造体へ格納
  tm.Hour   = hh;
  tm.Minute = mm;
  tm.Second = ss;

  return(true);
}

/**
 * __DATE__ から構造体へ値を設定
 * s: __DATE__ 文字列
 * return: true 正常 false エラー
 */
bool getDate(const char *s){

  char *monthList[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  char mm[12];
  int dd, yy;
  int i;

  // __DATE__ から文字列を取得
  if(sscanf(s, "%s %d %d", mm, &dd, &yy) != 3)
    return(false);

  // 月名から数字を取得
  for(i = 0; i < 12; i++)
    if(strcmp(mm, monthList[i]) == 0)
      break;
  if(i >= 12)
    return(false);

  // 構造体へ格納
  tm.Day = dd;
  tm.Month = i + 1;
  tm.Year = CalendarYrToTm(yy);

  return(true);
}
