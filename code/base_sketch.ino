#include <Adafruit_NeoPixel.h>

// ============================================================
//                    SELECT YOUR BOARD HERE
// ============================================================
// 1 = Board 1 (Sefton + Liverpool)
// 2 = Board 2 (Knowsley + Halton)
// 3 = Board 3 (St Helens + Wirral)
#define BOARD_ID 2
// ============================================================

#define NUM_LEDS 300
#define PIN_5 5
#define PIN_6 6

Adafruit_NeoPixel strip5(NUM_LEDS, PIN_5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6(NUM_LEDS, PIN_6, NEO_GRB + NEO_KHZ800);

// -------------------- Brightness --------------------
// const uint8_t BRIGHTNESS = 128; // ~50%
const uint8_t BRIGHTNESS = 255; // 100%
// -------------------- Pattern Rules --------------------
const uint8_t DIGIT_BLOCK = 10;
const uint8_t DIGITS = 4;
const uint8_t END_MARKERS = 2;   // 2 yellow lights at end

const uint16_t PATTERN_LENGTH =
  (DIGITS * (1 + DIGIT_BLOCK)) + END_MARKERS; // 46

// -------------------- Layout Rules --------------------
// Normal layout
const uint16_t MOVE_START_NORMAL = 0;
const uint16_t MOVE_LEN_NORMAL   = 119;

const uint16_t STATIC_START_NORMAL = 180;
const uint16_t STATIC_LEN_NORMAL   = 120;

// Special layout (Halton broken pixels)
const uint16_t MOVE_START_SPECIAL = 0;
const uint16_t MOVE_LEN_SPECIAL   = 145;

const uint16_t STATIC_START_SPECIAL = 145;
const uint16_t STATIC_LEN_SPECIAL   = 121;

// -------------------- Moving copies --------------------
const uint8_t MOVING_COPIES = 2;

// -------------------- Speed --------------------
const uint16_t FRAME_DELAY_MS = 140;

// -------------------- Movement offsets --------------------
uint16_t movingOffset5 = 0;
uint16_t movingOffset6 = 0;

// -------------------- Separator colour --------------------
uint32_t MARKER;  // bright yellow

// ============================================================
//                 DRAW PATTERN (BACKWARDS)
// ============================================================
void drawPercentageBackwardsInRegion(Adafruit_NeoPixel &strip,
                                     float percentage,
                                     uint32_t colour,
                                     uint16_t regionStart,
                                     uint16_t regionLen,
                                     int16_t endOffsetFromRegionEnd) {
  uint8_t tens  = ((int)(percentage / 10)) % 10;
  uint8_t units = ((int)(percentage)) % 10;
  uint8_t dec1  = ((int)(percentage * 10)) % 10;
  uint8_t dec2  = ((int)(percentage * 100)) % 10;

  uint8_t digits[4] = {tens, units, dec1, dec2};

  int32_t regionEnd = regionStart + regionLen - 1;
  int32_t idx = regionEnd - endOffsetFromRegionEnd;

  auto setInRegion = [&](int32_t absolutePixel, uint32_t c) {
    if (absolutePixel < (int32_t)regionStart) return;
    if (absolutePixel > (int32_t)regionEnd) return;
    strip.setPixelColor((uint16_t)absolutePixel, c);
  };

  // 2 yellow lights at end
  for (uint8_t i = 0; i < END_MARKERS; i++) {
    setInRegion(idx--, MARKER);
  }

  // digits reversed so it reads correctly from the end upward
  for (int d = 3; d >= 0; d--) {
    for (uint8_t i = 0; i < DIGIT_BLOCK; i++) {
      setInRegion(idx--, (i < digits[d]) ? colour : 0);
    }
    setInRegion(idx--, MARKER); // separator
  }
}

// ============================================================
//              DRAW MOVING PATTERN (FORWARDS)
// ============================================================
void drawPercentageMovingInRegion(Adafruit_NeoPixel &strip,
                                  float percentage,
                                  uint32_t colour,
                                  uint16_t regionStart,
                                  uint16_t regionLen,
                                  uint16_t offset) {
  uint8_t tens  = ((int)(percentage / 10)) % 10;
  uint8_t units = ((int)(percentage)) % 10;
  uint8_t dec1  = ((int)(percentage * 10)) % 10;
  uint8_t dec2  = ((int)(percentage * 100)) % 10;

  uint8_t digits[4] = {tens, units, dec1, dec2};

  uint16_t idx = offset % regionLen;

  auto setWrapped = [&](uint16_t localIndex, uint32_t c) {
    strip.setPixelColor(regionStart + (localIndex % regionLen), c);
  };

  for (uint8_t d = 0; d < 4; d++) {
    setWrapped(idx++, MARKER);

    for (uint8_t i = 0; i < DIGIT_BLOCK; i++) {
      setWrapped(idx++, (i < digits[d]) ? colour : 0);
    }
  }

  // 2 yellow lights at end
  setWrapped(idx++, MARKER);
  setWrapped(idx++, MARKER);
}

// ============================================================
//                DRAW WHOLE STRIP (ONE AREA)
// ============================================================
void drawArea(Adafruit_NeoPixel &strip,
              float percentage,
              uint32_t colour,
              bool useSpecialMap,
              uint16_t movingOffset) {
  strip.clear();

  uint16_t moveStart, moveLen, staticStart, staticLen;

  if (useSpecialMap) {
    moveStart = MOVE_START_SPECIAL;
    moveLen   = MOVE_LEN_SPECIAL;
    staticStart = STATIC_START_SPECIAL;
    staticLen   = STATIC_LEN_SPECIAL;
  } else {
    moveStart = MOVE_START_NORMAL;
    moveLen   = MOVE_LEN_NORMAL;
    staticStart = STATIC_START_NORMAL;
    staticLen   = STATIC_LEN_NORMAL;
  }

  // ---- Moving pattern (2 copies) ----
  uint16_t spacing = moveLen / MOVING_COPIES;

  for (uint8_t i = 0; i < MOVING_COPIES; i++) {
    drawPercentageMovingInRegion(strip, percentage, colour,
                                 moveStart, moveLen,
                                 movingOffset + (i * spacing));
  }

  // ---- Stationary centered pattern ----
  int16_t endOffset = 0;
  if (staticLen > PATTERN_LENGTH) {
    endOffset = (staticLen - PATTERN_LENGTH) / 2;
  }

  drawPercentageBackwardsInRegion(strip, percentage, colour,
                                  staticStart, staticLen, endOffset);
}

// ============================================================
//                           SETUP
// ============================================================
void setup() {
  strip5.begin();
  strip6.begin();

  strip5.setBrightness(BRIGHTNESS);
  strip6.setBrightness(BRIGHTNESS);

  strip5.clear();
  strip6.clear();

  strip5.show();
  strip6.show();

  // Bright yellow markers (instead of white)
  MARKER = strip5.Color(255, 255, 0);
}

// ============================================================
//                            LOOP
// ============================================================
void loop() {

  float pct5 = 0.0, pct6 = 0.0;
  uint32_t col5 = 0, col6 = 0;

  bool specialMapPin5 = false;
  bool specialMapPin6 = false;

#if BOARD_ID == 1
  // Board 1
  // Pin 5: Sefton (bright sky blue)
  // Pin 6: Liverpool (purple)
  pct5 = 39.68; col5 = strip5.Color(0, 180, 255);     // Sefton
  pct6 = 38.93; col6 = strip6.Color(150, 0, 255);     // Liverpool

#elif BOARD_ID == 2
  // Board 2
  // Pin 5: Knowsley (bright red)
  // Pin 6: Halton (light grey, special mapping)
  pct5 = 40.55; col5 = strip5.Color(255, 0, 0);       // Knowsley
  pct6 = 40.63; col6 = strip6.Color(200, 200, 200);   // Halton (light grey)

  specialMapPin6 = true;

#elif BOARD_ID == 3
  // Board 3
  // Pin 5: St Helens (dusky rose)
  // Pin 6: Wirral (bottle green)
  pct5 = 39.98; col5 = strip5.Color(200, 90, 110);    // St Helens
  pct6 = 39.98; col6 = strip6.Color(0, 90, 30);       // Wirral

#else
#error "Invalid BOARD_ID - set it to 1, 2, or 3"
#endif

  // Draw both strips
  drawArea(strip5, pct5, col5, specialMapPin5, movingOffset5);
  drawArea(strip6, pct6, col6, specialMapPin6, movingOffset6);

  strip5.show();
  strip6.show();

  // Update offsets
  uint16_t len5 = specialMapPin5 ? MOVE_LEN_SPECIAL : MOVE_LEN_NORMAL;
  uint16_t len6 = specialMapPin6 ? MOVE_LEN_SPECIAL : MOVE_LEN_NORMAL;

  movingOffset5 = (movingOffset5 + 1) % len5;
  movingOffset6 = (movingOffset6 + 1) % len6;

  delay(FRAME_DELAY_MS);
}
