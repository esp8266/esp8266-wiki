// From TheSeven on IRC.

#define PAGESIZE 4096
  
void main()
{
  struct __attribute__((packed))
  {
    uint8_t unknown0;
    uint8_t unknown1;
        enum
        {
	  MODE_QIO = 0,
	  MODE_QOUT = 1,
	  MODE_DIO = 2,
	  MODE_DOUT = 15,
        } mode : 8;
        enum
        {
	  SPEED_40MHZ = 0,
	  SPEED_26MHZ = 1,
	  SPEED_20MHZ = 2,
	  SPEED_80MHZ = 15,
        } speed : 4;
        enum
        {
	  SIZE_4MBIT = 0,
	  SIZE_2MBIT = 1,
	  SIZE_8MBIT = 2,
	  SIZE_16MBIT = 3,
	  SIZE_32MBIT = 4,
        } size : 4;
  } flashHeader;
    
  struct __attribute__((packed))
  {
    uint8_t useSecondImageInfo;
    uint8_t unknown1;
    uint8_t unknown2;
    uint8_t unknown3;
  } fwInfo;
    
  struct __attribute__((packed))
  {
    uint8_t activeImageNumber;
    uint8_t unknown1;
    uint8_t unknown2;
    uint8_t unknown3;
    uint8_t unknown4;
    uint8_t unknown5;
    uint8_t unknown6;
    uint8_t unknown7;
  } imageInfo;
    
  ets_printf("\n2nd boot version : 1.1\n");
  SPIRead(0, &flashHeader, sizeof(flashHeader));
  ets_printf("  SPI Speed      : ");
  switch (spiInfo.speed)
    {
    case SPEED_40MHZ: ets_printf("40MHz\n"); break;
    case SPEED_26MHZ: ets_printf("26.7MHz\n"); break;
    case SPEED_20MHZ: ets_printf("20MHz\n"); break;
    case SPEED_80MHZ: ets_printf("80MHz\n"); break;
    }
  ets_printf("  SPI Mode       : ");
  switch (spiInfo.mode)
    {
    case MODE_QIO: ets_printf("QIO\n"); break;
    case MODE_QOUT: ets_printf("QOUT\n"); break;
    case MODE_DIO: ets_printf("DIO\n"); break;
    case MODE_DOUT: ets_printf("DOUT\n"); break;
    }
  ets_printf("  SPI Flash Size : ");
  int offset;
  switch (spiInfo.size)
    {
    case SIZE_2MBIT: ets_printf("2Mbit\n"); offset = 60; break;
    case SIZE_4MBIT: ets_printf("4Mbit\n"); offset = 124; break;
    case SIZE_8MBIT: ets_printf("8Mbit\n"); offset = 252; break;
    case SIZE_16MBIT: ets_printf("16Mbit\n"); offset = 508; break;
    case SIZE_32MBIT: ets_printf("32Mbit\n"); offset = 1020; break;
    default: ets_printf("1\n\n"); offset = 124; break;
    }

  spiRead((offset + 3) * PAGESIZE, &fwInfo, sizeof(fwInfo));
  if (!fwInfo.useSecondImageInfo) spiRead((offset + 1) * PAGESIZE, &imageInfo, sizeof(imageInfo));
  else spiRead((offset + 2) * PAGESIZE, &imageInfo, sizeof(imageInfo));

  ets_memcpy(0x40108000, 0x3ffe8010, 0x304);
  ets_printf("jump to run user");
  if (imageInfo.activeImageNumber == 255) imageInfo.activeImageNumber = 0;
  int useImage = imageInfo.activeImageNumber & 0xf;
  switch (useImage)
    {
    case 0:
      ets_printf("1\n\n");
      0x4010800c(0x100);
      break;
    case 1:
      ets_printf("2\n\n");
      if (offset == 508 || offset == 1020) offset = 252;
      0x4010800c((((offset + 4) >> 1) << 12) + 0x1000);
      break;
    default:
      ets_printf("error user bin flag, flag = %x\n", useImage);
      break;
    }
}
