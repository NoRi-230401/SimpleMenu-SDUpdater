/*
Cardputer Simple Launcher
@shikarunochi
*/
// -----------------------------------------
// Cardputer Simple Launcher
//      Extends to Core2 and CoreS3
// -----------------------------------------
//   SimpleMenu for SD_Updater
//              by NoRi   2025-05-14
// -----------------------------------------

#include <Arduino.h>
#include <SD.h>
#include <M5GFX.h>
#include <M5StackUpdater.h>

#if defined(CARDPUTER)
#include <M5Cardputer.h>
M5Canvas canvas(&M5Cardputer.Display);
SPIClass SPI2;
#define X_WIDTH 240
#define Y_HEIGHT 135
#define N_COLS 20      // colums : 列
#define N_ROWS 8       // rows   : 行
int dispfileCount = 7; // dispfileCount+1 が画面file表示数

#else
#include <M5Unified.h>
M5Canvas canvas(&M5.Display);
#define X_WIDTH 320
#define Y_HEIGHT 240
#define N_COLS 26 // colums : 列
#define N_ROWS 15 // rows   : 行
int dispfileCount = 12; // dispfileCount+1 が画面file表示数
#endif

#define COLS1 X_WIDTH / N_COLS
#define ROWS1 Y_HEIGHT / N_ROWS
#define Y_MAX Y_HEIGHT - 1
#define X_MAX X_WIDTH - 1

void sortList(String fileList[], int fileListCount);
bool SD_begin();
void UPDATE();

#define MAX_FILES 256
File fileRoot;
String fileList[MAX_FILES];
String fileDir = "/";

int fileListCount; // (number_of_bin-files - 1)
int startIndex;    // disp start index
int endIndex;      // disp end index
int selectIndex;   // file select index
boolean needRedraw;

void setup()
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;

#if defined(CARDPUTER)
  // ------------- CARDPUTER -------------
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setColorDepth(8);
  M5Cardputer.Display.setRotation(1);
#else
  // ---- Core2 CoreS3 -------------
  M5.begin(cfg);
  M5.Display.setColorDepth(8);
  M5.Display.setRotation(1);
#endif
  // ---end of CARDPUTER ---------------

  // ちらつき防止のため Canvasに描画してpushSpriteする
  canvas.setTextSize(2);
  canvas.setColorDepth(8);
  canvas.createSprite(X_WIDTH, Y_HEIGHT);
  canvas.fillSprite(BLACK);

  SD_begin();
  fileRoot = SD.open(fileDir);
  fileListCount = 0;

  while (1)
  {
    File entry = fileRoot.openNextFile();
    if (!entry)
    { // no more files
      break;
    }
    // ファイルのみ取得
    if (!entry.isDirectory())
    {
      String fullFileName = entry.name();
      String fileName = fullFileName.substring(fullFileName.lastIndexOf("/") + 1);
      String ext = fileName.substring(fileName.lastIndexOf(".") + 1);
      ext.toUpperCase();
      if (ext.equals("BIN") == false)
      {
        continue;
      }
      fileList[fileListCount] = fileName;
      fileListCount++;
    }
    entry.close();
  }

  if (fileListCount > 0)
  {
    fileListCount--;
  }

  fileRoot.close();
  sortList(fileList, fileListCount);

  startIndex = 0;
  endIndex = startIndex + dispfileCount;
  if (endIndex > fileListCount)
  {
    endIndex = fileListCount;
  }

  needRedraw = true;
  selectIndex = 0;
}

void loop()
{
  if (needRedraw == true)
  {
    if (selectIndex < 0)
      selectIndex = fileListCount;
    if (selectIndex > fileListCount)
      selectIndex = 0;

    if (dispfileCount > fileListCount) // bin-file数が画面表示行より少ないとき
    {
      startIndex = 0;
      endIndex = fileListCount;
    }
    else
    {
      startIndex = selectIndex - 5;
      if (startIndex < 0)
        startIndex = 0;

      endIndex = startIndex + dispfileCount;
      if (endIndex > fileListCount)
        endIndex = fileListCount;
    }

    canvas.setCursor(0, 0);
    canvas.fillScreen(BLACK);
    for (int index = startIndex; index <= endIndex; index++)
    {
      if (index == selectIndex)
      {
        canvas.setTextColor(GREEN);
      }
      else
      {
        canvas.setTextColor(WHITE);
      }
      canvas.println(fileList[index].substring(0, N_COLS));
    }

#ifndef CARDPUTER
    // --- Core2 and CoreS3 --- help message
    canvas.setCursor(0, Y_MAX - ROWS1);
    canvas.setTextColor(YELLOW);
    canvas.print("    up     select    down ");
#endif

    canvas.pushSprite(0, 0);
    needRedraw = false;
  }

#ifdef CARDPUTER
  // ---- CardPuter ----------
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isChange())
  {
    if (M5Cardputer.Keyboard.isPressed())
    {
      Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
      if (status.enter)
      {
        UPDATE();
      }
      for (auto i : status.hid_keys)
      {
        switch (i)
        {
        case 0x33: //";" UpArrow
          selectIndex--;
          needRedraw = true;
          break; //;

        case 0x37: //"." DownArrow
          selectIndex++;
          needRedraw = true;
          break;
        }
      }
    }
  }

#else
  // ---- Core2 and CoreS3 ----------
  M5.update();

  if (M5.BtnB.wasHold())
  { // BtnB -- Select
    UPDATE();
  }
  else if (M5.BtnA.wasPressed())
  { // BtnA -- Up
    selectIndex--;
    needRedraw = true;
  }
  else if (M5.BtnC.wasPressed())
  { // BtnC -- Down
    selectIndex++;
    needRedraw = true;
  }

#endif
  delay(10);
}

void UPDATE()
{
  canvas.setTextColor(GREEN);
  String msg = " Loading ...";
  canvas.fillRect(0, 0, X_MAX, Y_MAX, BLACK);
  canvas.setCursor(0, (Y_HEIGHT / 2) - 3 * ROWS1);
  canvas.print(msg);

  String flname = fileList[selectIndex];
  canvas.setCursor(0, (Y_HEIGHT / 2) + 0 * ROWS1);
  canvas.print(flname.substring(0, N_COLS));

  canvas.pushSprite(0, 0);
  delay(100);

  updateFromFS(SD, "/" + flname);
  ESP.restart();

  while (true)
    ;
}

// fileListCount の定義修正した、0 ～ index 最後とする
void sortList(String fileList[], int fileListCount)
{
  if (fileListCount < 1)
    return;

  bool swapped;
  String temp;
  String name1, name2;
  do
  {
    swapped = false;
    for (int i = 0; i <= fileListCount - 1; i++)
    {
      name1 = fileList[i];
      name1.toUpperCase();
      name2 = fileList[i + 1];
      name2.toUpperCase();
      if (name1.compareTo(name2) > 0)
      {
        temp = fileList[i];
        fileList[i] = fileList[i + 1];
        fileList[i + 1] = temp;
        swapped = true;
      }
    }
  } while (swapped);
}

bool SD_begin()
{
  int i = 0;
#if defined(CARDPUTER)
  // ------------- CARDPUTER -------------
  SPI2.begin(
      M5.getPin(m5::pin_name_t::sd_spi_sclk),
      M5.getPin(m5::pin_name_t::sd_spi_miso),
      M5.getPin(m5::pin_name_t::sd_spi_mosi),
      M5.getPin(m5::pin_name_t::sd_spi_ss));

  while (!SD.begin(M5.getPin(m5::pin_name_t::sd_spi_ss), SPI2) && i < 10)
#else
  // ----------- Core2 and CoreS3 ----------
  while (!SD.begin(GPIO_NUM_4, SPI, 25000000) && i < 10)
#endif
  {
    delay(500);
    i++;
  }

  if (i >= 10)
  {
    Serial.println("ERR: SD begin erro...");
    return false;
  }
  return true;
}
