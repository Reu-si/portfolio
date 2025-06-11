import 'package:flutter/material.dart';

/*
- Beinhaltet Variablen für das responsive Festlegen von Textgrößen, Abständen, Icons und Rundungen
- Muss innerhalb der Build-Methode eines Stateful-Widgets mit Sizes.initialize(context); initialisiert werden
- Man kann die einzelnen Variablen anschließend mit Sizes.variablenName, bspw. Sizes.paddingRegular
  im Code verwenden.
- Werte können bei Bedarf angepasst werden
*/

class Sizes {
  static double width = 1, height = 1;                                      // Bildschirmbreite und -höhe
  static double widthPercent = 1, heightPercent = 1;                        // 1% der Bildschirmbreite und -höhe
  static double bottomNavigationHeight = 1;                                 // Höhe einer Navigationleiste

  static double paddingBig = 1, paddingRegular = 1, paddingSmall = 1;       // Variablen für große, mittlere und kleine Abstände
  static double textSizeBig = 1, textSizeRegular = 1, textSizeSmall = 1;    // Variablen für große. mittlere und kleine Texte
  static double iconSize = 1;                                               // Größe für Icons
  static double borderRadius = 1, borderRadiusBig = 1;                      // Variablen für große und kleine Rundungen

  static void initialize(BuildContext context) {
    MediaQueryData m = MediaQuery.of(context);
    width = m.size.width;
    height = m.size.height;
    widthPercent = width / 100;
    heightPercent = height / 100;
    paddingSmall = width / 31.25;
    paddingRegular = paddingSmall * 2;
    paddingBig = paddingRegular * 2;
    textSizeSmall = width / 25;
    textSizeRegular = width / 18.75;
    textSizeBig = width / 15;
    borderRadius = widthPercent * 3;
    borderRadiusBig = borderRadius * 2;
    bottomNavigationHeight = heightPercent * 7;
    //topNavigationHeight = heightPercent * 7;
    iconSize = widthPercent * 7.5;
  }
}

