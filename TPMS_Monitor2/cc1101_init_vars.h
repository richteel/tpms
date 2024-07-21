#ifndef CC1101_INTERFACE_H
#define CC1101_INTERFACE_H

CC1101_Parameters cc1101_parameters;
CC1101_Settings cc1101_settings;

/*****************************************************************************
 *                                 Functions                                 *
 *****************************************************************************/
void cc1101_init_vars() {
  switch (carSettings.freq) {
    case TPMS_Frequencies::UK_433MHz:
      switch (carSettings.tpmsSensorType) {
        case TPMS_Sensors::Citroen:
          cc1101_parameters.expectedbitcount = 88;
          cc1101_parameters.expectedbytecount = 10;
          cc1101_parameters.cdwidth_min = 8000;

          break;
        case TPMS_Sensors::Dacia:
          cc1101_parameters.cdwidth_min = 7000;

          cc1101_settings.cc1101_defval_freq0 = 0x0C;
          cc1101_settings.cc1101_defval_deviatn = 0x41;
          break;
        case TPMS_Sensors::Ford:
          cc1101_parameters.expectedbitcount = 64;
          cc1101_parameters.expectedbytecount = 8;
          cc1101_parameters.cdwidth_max = 10000;
          break;
        case TPMS_Sensors::Hyundai_i35:
          cc1101_parameters.expectedbitcount = 64;
          cc1101_parameters.expectedbytecount = 8;
          cc1101_parameters.cdwidth_max = 9000;
          cc1101_parameters.synctiming_min = 140;
          cc1101_parameters.synctiming_max = 160;
          break;
        case TPMS_Sensors::Jansite:
          cc1101_parameters.expectedbitcount = 56;
          cc1101_parameters.expectedbytecount = 7;
          cc1101_parameters.cdwidth_min = 28500;
          cc1101_parameters.cdwidth_max = 3100;
          break;
        case TPMS_Sensors::JansiteSolar:
          cc1101_parameters.expectedbitcount = 88;
          cc1101_parameters.expectedbytecount = 11;
          cc1101_parameters.syncbits = 24;
          cc1101_parameters.cdwidth_min = 18500;
          cc1101_parameters.cdwidth_max = 25000;
          break;
        case TPMS_Sensors::Mercedes_AMG_GT:
          cc1101_parameters.expectedbytecount = 10;
          cc1101_parameters.shorttiming_min = 20;
          cc1101_parameters.shorttiming_nom = 25;
          cc1101_parameters.shorttiming_max = 39;
          cc1101_parameters.longtiming_min = 40;
          cc1101_parameters.synctiming_min = 88;
          cc1101_parameters.synctiming_max = 600;
          cc1101_parameters.endtiming_max = 0;

          cc1101_settings.cc1101_defval_freq0 = 0x5D;
          cc1101_settings.cc1101_defval_deviatn = 0x41;
          cc1101_settings.cc1101_defval_mdmcfg4 = 0x9A;
          cc1101_settings.cc1101_defval_mdmcfg3 = 0x83;
          cc1101_settings.cc1101_defval_mdmcfg1 = 0x01;
          cc1101_settings.cc1101_defval_agcctrl2 = 0x07;
          cc1101_settings.cc1101_defval_agcctrl0 = 0x82;
          cc1101_settings.cc1101_defval_mcsm0 = 0x08;

          if (USE_FIFO) {
            cc1101_parameters.expectedbitcount = 80;
            cc1101_parameters.cdwidth_min = 3000;
            cc1101_parameters.cdwidth_max = 6500;
            cc1101_parameters.longtiming_max = 60;

            cc1101_settings.cc1101_defval_iocfg2 = 0x0E;
            cc1101_settings.cc1101_defval_iocfg0 = 0x06;
            cc1101_settings.cc1101_defval_fifothr = 0x07;
            cc1101_settings.cc1101_defval_sync1 = 0x59;
            cc1101_settings.cc1101_defval_sync0 = 0x55;
            cc1101_settings.cc1101_defval_pktlen = 0x15;
            cc1101_settings.cc1101_defval_pktctrl1 = 0x01;
            cc1101_settings.cc1101_defval_pktctrl0 = 0x00;
            cc1101_settings.cc1101_defval_addr = 0x5A;
            cc1101_settings.cc1101_defval_mdmcfg2 = 0x16;
            cc1101_settings.cc1101_defval_mcsm1 = 0x30;
          } else {
            cc1101_parameters.expectedbitcount = 160;
            cc1101_parameters.expectedfifobytecount = 20;
            cc1101_parameters.cdwidth_min = 5000;
            cc1101_parameters.cdwidth_max = 7000;
            cc1101_parameters.longtiming_max = 66;

            cc1101_settings.cc1101_defval_mdmcfg2 = 0x00;
          }
          break;
        case TPMS_Sensors::NissanLeaf:
          cc1101_parameters.cdwidth_min = 7000;

          cc1101_settings.cc1101_defval_freq0 = 0x0C;
          cc1101_settings.cc1101_defval_deviatn = 0x41;
          break;
        case TPMS_Sensors::PontiacG82009:
          // US 315 MHz Only
          break;
        case TPMS_Sensors::Renault:
          cc1101_parameters.cdwidth_min = 7000;

          cc1101_settings.cc1101_defval_freq0 = 0x0C;
          cc1101_settings.cc1101_defval_deviatn = 0x41;
          break;
        case TPMS_Sensors::Schrader_A9054100:
          cc1101_parameters.expectedbitcount = 64;
          cc1101_parameters.expectedbytecount = 8;
          cc1101_parameters.syncbits = 4;
          cc1101_parameters.cdwidth_min = 12000;
          cc1101_parameters.cdwidth_max = 30000;
          cc1101_parameters.shorttiming_min = 80;
          cc1101_parameters.shorttiming_nom = 120;
          cc1101_parameters.shorttiming_max = 160;
          cc1101_parameters.longtiming_min = 180;
          cc1101_parameters.longtiming_max = 260;
          cc1101_parameters.synctiming_min = 160;
          cc1101_parameters.synctiming_max = 260;

          cc1101_settings.cc1101_defval_fifothr = 0x47;
          cc1101_settings.cc1101_defval_pktlen = 0x00;
          cc1101_settings.cc1101_defval_fsctrl1 = 0x06;
          cc1101_settings.cc1101_defval_mdmcfg4 = 0xC8;
          cc1101_settings.cc1101_defval_mdmcfg3 = 0x43;
          cc1101_settings.cc1101_defval_mdmcfg2 = 0x34;
          cc1101_settings.cc1101_defval_agcctrl2 = 0x64;
          cc1101_settings.cc1101_defval_agcctrl1 = 0x78;
          cc1101_settings.cc1101_defval_agcctrl0 = 0xB3;
          cc1101_settings.cc1101_defval_foccfg = 0x14;
          cc1101_settings.cc1101_defval_frend1 = 0xB6;
          break;
        case TPMS_Sensors::Schrader_C1100:
          cc1101_parameters.cdwidth_min = 7500;
          cc1101_parameters.cdwidth_max = 11000;
          cc1101_parameters.synctiming_min = 140;
          cc1101_parameters.synctiming_max = 160;
          break;
        case TPMS_Sensors::Subaru:
          cc1101_parameters.syncbits = 24;
          cc1101_parameters.cdwidth_min = 8500;
          cc1101_parameters.cdwidth_max = 20000;
          cc1101_parameters.longtiming_max = 160;
          break;
        case TPMS_Sensors::Toyota_PMV_107J:
          cc1101_parameters.expectedbitcount = 66;
          cc1101_parameters.cdwidth_min = 6000;
          cc1101_parameters.cdwidth_max = 9500;
          cc1101_parameters.shorttiming_min = 40;
          break;
        case TPMS_Sensors::Toyota_PMV_C210:
          cc1101_parameters.syncbits = 11;
          cc1101_parameters.cdwidth_max = 10500;
          cc1101_parameters.shorttiming_min = 40;
          break;
        case TPMS_Sensors::Toyota_TRW_C070:
          cc1101_parameters.expectedbitcount = 64;
          cc1101_parameters.expectedbytecount = 8;
          cc1101_parameters.cdwidth_max = 9000;
          cc1101_parameters.synctiming_min = 140;
          cc1101_parameters.synctiming_max = 160;
          break;
        case TPMS_Sensors::TruckSolar:
          cc1101_parameters.expectedbitcount = 80;
          cc1101_parameters.cdwidth_min = 18500;
          cc1101_parameters.cdwidth_max = 24000;
          cc1101_parameters.shorttiming_min = 40;
          break;
        case TPMS_Sensors::Zoe:
          cc1101_parameters.expectedbitcount = 64;
          cc1101_parameters.expectedbytecount = 8;
          cc1101_parameters.cdwidth_min = 7000;

          cc1101_settings.cc1101_defval_freq0 = 0x0C;
          cc1101_settings.cc1101_defval_deviatn = 0x41;
          break;
        default:
          break;
      }
      break;
    case TPMS_Frequencies::US_315MHz:
      switch (carSettings.tpmsSensorType) {
        case TPMS_Sensors::Citroen:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::Dacia:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::Ford:
          cc1101_parameters.expectedbitcount = 64;
          cc1101_parameters.expectedbytecount = 8;
          cc1101_parameters.cdwidth_max = 10000;

          cc1101_settings.cc1101_defval_freq2 = 0x0C;
          cc1101_settings.cc1101_defval_freq1 = 0x1D;
          cc1101_settings.cc1101_defval_freq0 = 0x57;
          break;
        case TPMS_Sensors::Hyundai_i35:
          cc1101_parameters.expectedbitcount = 64;
          cc1101_parameters.expectedbytecount = 8;
          cc1101_parameters.cdwidth_max = 9000;
          cc1101_parameters.synctiming_min = 140;
          cc1101_parameters.synctiming_max = 160;

          cc1101_settings.cc1101_defval_freq2 = 0x0C;
          cc1101_settings.cc1101_defval_freq1 = 0x1D;
          cc1101_settings.cc1101_defval_freq0 = 0x57;
          break;
        case TPMS_Sensors::Jansite:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::JansiteSolar:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::Mercedes_AMG_GT:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::NissanLeaf:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::PontiacG82009:
          cc1101_parameters.expectedbytecount = 10;
          cc1101_parameters.syncbits = 11;
          cc1101_parameters.shorttiming_min = 40;
          if (USE_HW_CD) {
            cc1101_parameters.cdwidth_min = 15000;
            cc1101_parameters.cdwidth_max = 21500;
          } else {
            cc1101_parameters.cdwidth_min = 26000;
            cc1101_parameters.cdwidth_max = 29500;
          }

          cc1101_settings.cc1101_defval_iocfg2 = 0x16;
          cc1101_settings.cc1101_defval_iocfg0 = 0x06;
          cc1101_settings.cc1101_defval_fifothr = 0x4F;
          cc1101_settings.cc1101_defval_sync1 = 0x65;
          cc1101_settings.cc1101_defval_sync0 = 0xA5;
          cc1101_settings.cc1101_defval_pktlen = 0x12;
          cc1101_settings.cc1101_defval_pktctrl1 = 0xE0;
          cc1101_settings.cc1101_defval_pktctrl0 = 0x00;
          cc1101_settings.cc1101_defval_fsctrl1 = 0x06;
          cc1101_settings.cc1101_defval_freq2 = 0x0C;
          cc1101_settings.cc1101_defval_freq1 = 0x1D;
          cc1101_settings.cc1101_defval_freq0 = 0x57;
          cc1101_settings.cc1101_defval_mdmcfg4 = 0x88;
          cc1101_settings.cc1101_defval_mdmcfg3 = 0x51;
          cc1101_settings.cc1101_defval_mdmcfg2 = 0x36;
          cc1101_settings.cc1101_defval_agcctrl2 = 0xC6;
          cc1101_settings.cc1101_defval_agcctrl1 = 0x50;
          cc1101_settings.cc1101_defval_agcctrl0 = 0x40;
          cc1101_settings.cc1101_defval_frend0 = 0x11;
          break;
        case TPMS_Sensors::Renault:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::Schrader_A9054100:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::Schrader_C1100:
          cc1101_parameters.cdwidth_min = 7500;
          cc1101_parameters.cdwidth_max = 11000;
          cc1101_parameters.synctiming_min = 140;
          cc1101_parameters.synctiming_max = 160;

          cc1101_settings.cc1101_defval_freq2 = 0x0C;
          cc1101_settings.cc1101_defval_freq1 = 0x1D;
          cc1101_settings.cc1101_defval_freq0 = 0x57;
          break;
        case TPMS_Sensors::Subaru:
          cc1101_parameters.expectedbitcount = 42;
          cc1101_parameters.expectedbytecount = 5;
          cc1101_parameters.syncbits = 24;
          cc1101_parameters.cdwidth_min = 10000;
          cc1101_parameters.cdwidth_max = 23000;
          cc1101_parameters.shorttiming_min = 70;
          cc1101_parameters.shorttiming_nom = 100;
          cc1101_parameters.shorttiming_max = 159;
          cc1101_parameters.longtiming_min = 160;
          cc1101_parameters.longtiming_max = 300;

          cc1101_settings.cc1101_defval_fifothr = 0x4F;
          cc1101_settings.cc1101_defval_freq2 = 0x0C;
          cc1101_settings.cc1101_defval_freq1 = 0x1D;
          cc1101_settings.cc1101_defval_freq0 = 0x57;
          cc1101_settings.cc1101_defval_mdmcfg4 = 0x58;
          cc1101_settings.cc1101_defval_mdmcfg3 = 0x43;
          cc1101_settings.cc1101_defval_mdmcfg2 = 0x34;
          cc1101_settings.cc1101_defval_agcctrl2 = 0x64;
          cc1101_settings.cc1101_defval_agcctrl1 = 0x78;
          cc1101_settings.cc1101_defval_agcctrl0 = 0xB3;
          cc1101_settings.cc1101_defval_foccfg = 0x14;
          cc1101_settings.cc1101_defval_frend1 = 0xB6;
          break;
        case TPMS_Sensors::Toyota_PMV_107J:
          cc1101_parameters.expectedbitcount = 66;
          cc1101_parameters.cdwidth_min = 12000;
          cc1101_parameters.cdwidth_max = 17500;
          cc1101_parameters.shorttiming_min = 80;
          cc1101_parameters.shorttiming_max = 139;
          cc1101_parameters.longtiming_min = 166;
          cc1101_parameters.longtiming_max = 250;
          cc1101_parameters.synctiming_min = 350;
          cc1101_parameters.synctiming_max = 1500;
          cc1101_parameters.endtiming_min = 140;

          cc1101_settings.cc1101_defval_freq2 = 0x0C;
          cc1101_settings.cc1101_defval_freq1 = 0x1D;
          cc1101_settings.cc1101_defval_freq0 = 0x57;
          cc1101_settings.cc1101_defval_deviatn = 0x44;
          cc1101_settings.cc1101_defval_mdmcfg4 = 0x78;
          cc1101_settings.cc1101_defval_mdmcfg3 = 0x94;
          cc1101_settings.cc1101_defval_agcctrl2 = 0x43;
          cc1101_settings.cc1101_defval_agcctrl1 = 0x40;
          cc1101_settings.cc1101_defval_agcctrl0 = 0x81;
          break;
        case TPMS_Sensors::Toyota_PMV_C210:
          cc1101_parameters.syncbits = 11;
          cc1101_parameters.cdwidth_max = 10500;
          cc1101_parameters.shorttiming_min = 40;

          cc1101_settings.cc1101_defval_freq2 = 0x0C;
          cc1101_settings.cc1101_defval_freq1 = 0x1D;
          cc1101_settings.cc1101_defval_freq0 = 0x57;
          break;
        case TPMS_Sensors::Toyota_TRW_C070:
          cc1101_parameters.expectedbitcount = 64;
          cc1101_parameters.expectedbytecount = 8;
          cc1101_parameters.cdwidth_max = 9000;
          cc1101_parameters.synctiming_min = 140;
          cc1101_parameters.synctiming_max = 160;

          cc1101_settings.cc1101_defval_freq2 = 0x0C;
          cc1101_settings.cc1101_defval_freq1 = 0x1D;
          cc1101_settings.cc1101_defval_freq0 = 0x57;
          break;
        case TPMS_Sensors::TruckSolar:
          // UK 433 MHz Only
          break;
        case TPMS_Sensors::Zoe:
          // UK 433 MHz Only
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

#endif  // CC1101_INTERFACE_H