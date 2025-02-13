
# Flappy Bird på ChipKIT uC32
Detta projekt är ett Mini Project för kursen IS1200 Computer Hardware Engineering vid KTH, implementerat på ChipKIT uC32-utvecklingskortet med Basic I/O Shield. Projektet uppfyller kraven för ett **Avancerat Projekt (Advanced Project)**.

---

## Projektöversikt
Vi har implementerat Flappy Birds kärnlogik med följande utökade funktioner för att uppfylla avancerade projektkrav:
- **Pixelbaserad grafikrendering**: Dynamisk rendering av fågel, hinder och bakgrund på OLED-displayen
- **Rörelse i både X- och Y-axlarna**:
  - Fågeln styrs vertikalt (Y-axel) via BTN1
  - Hinder rör sig horisontellt (X-axel) med accelererande hastighet
- **Dynamisk svårighetsgrad**: Hinderavstånd minskar över tid
- **Highscore-lista**: Lagrar högsta poäng i EEPROM via I2C-protokollet
- **Interaktivt menusystem**: Stöder paus/återuppta/omstart

---

## Bidrag och Arbetsfördelning

| Medlem         | Huvudbidrag                   | 
|:---------------|:------------------------------|
| Zhenagn Chen       | Fysikmotor, Grafikrenderare, Inputhantering |      
| Benjamin     | EEPROM-integration | 
