  LCD_Init(LCD_ADDR); // 0x4e or 0x27<<1

  LCD_GotoXY(2,0);
  LCD_SendString(LCD_ADDR, "OXYETb!");
  LCD_GotoXY(1,1);
  LCD_SendString(LCD_ADDR, "PA6OTAET!");
